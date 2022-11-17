#include "fruitbox.hpp"
#include <errno.h>

using namespace std;

constexpr uint32_t mp3_buffer_size_fraction { 4 };
constexpr uint32_t audio_stream_fragments { 4 };

mpg123_handle *AudioClass::mp3 {};
unsigned char *AudioClass::mp3_buffer {};
size_t AudioClass::mp3_buffer_size {};
CURL *AudioClass::curl {};
curl_buffer_t AudioClass::curl_buffer {};
ALLEGRO_MIXER *AudioClass::songs_mixer {};
ALLEGRO_MIXER *AudioClass::output_mixer {};
ALLEGRO_VOICE *AudioClass::voice;

curl_icy_t AudioClass::curl_icy {};
bool AudioClass::paused { false };
bool GetCURLDataBusy { false };
atomic<bool>AudioClass::play_song {};
ALLEGRO_AUDIO_STREAM *AudioClass::mp3_stream {};
atomic<int32_t>AudioClass::GetCURLDataThread_status_event {};
mutex AudioClass::icy_buffer_mtx {};

extern "C" void clear_equalizer(void); // src/libmpg123/equalizer.c
extern "C" void init_equalizer(void); // src/libmpg123/equalizer.c

struct ioh { int fd; };

ioh *iohandle;

// #define DUMP_STREAM_DATA

#ifdef DUMP_STREAM_DATA
DUMP_STREAM_DATA
  FILE *stream_data;
#endif

void AudioClass::SleepFrameTicks(uint32_t frames)
// sleep for specified number of frames , or until Engine_finished
{
  uint32_t frame_ms { 1000 / static_cast<uint32_t>(display_refresh_rate) };

  for (uint32_t t = 0; t < frames; ++t)
  {
    if (Engine_finished == true) break;
    this_thread::sleep_for(chrono::milliseconds(frame_ms));
  }
}

void AudioClass::RemoveSong
(
  bool skipped
)
{
  AudioClass::play_song = false;
  PlayQueue->Remove();
  if (!skipped && Config->ini_general->loop_playqueue && !Config->skin_general->instant_play && (status.now_playing->play_type != play_type_e::AttractMode))
  // add (non-attract) song back to playqueue if in loop mode and it's not been stopped (skipped) by the user, and we're not in instant mode
  {
    PlayQueue->Add(status.now_playing, play_type_e::CreditPlay);
  }

  #if 0
  // this causes double free at program exit!!!!
  // destroy any artwork bitmap associated with now playing song...
  if (status.now_playing->artwork.handle)
  {
    al_destroy_bitmap(status.now_playing->artwork.handle);
    status.now_playing->artwork.handle = nullptr;
    status.now_playing->artwork.destroy_needed = false;
  }
  #endif
  // close(iohandle->fd);
  status.last_played = status.now_playing;
  status.last_played->artwork.handle = nullptr;
  status.last_played_length_str = status.now_playing_length_str;

  status.now_playing = &no_song;
  status.now_playing_length_str = invalidTimeMS;
  status.now_playing_elapsed_time_str = invalidTimeMS;
  status.now_playing_time_remaining_str = invalidTimeMS;
  // status.now_playing_time_remaining_scale = 0.0;

  song_play_state = song_play_state_e::stopped;

  if (Config->ini_attract->enable && !PlayQueue->NumSongsTotal())
  {
    SongPlayThread_status_event |= StatusEvent_StartAttractModeTimer;
  }
  SongPlayThread_status_event |= StatusEvent_SongStop | StatusEvent_SongVideoStop;
}

void AudioClass::LoadFolderArtwork(const song_t *song, ALLEGRO_BITMAP **bitmap)
{
  string folder_artwork { song->filename.substr(0, song->filename.find_last_of("/")) + "/folder.jpg" };
  *bitmap = al_load_bitmap(folder_artwork.c_str());

  if (*bitmap == nullptr) // folder.jpg not found, so look for Folder.jpg...
  {
    folder_artwork = song->filename.substr(0, song->filename.find_last_of("/")) + "/Folder.jpg";
    *bitmap = al_load_bitmap(folder_artwork.c_str());
  }
}

void AudioClass::LoadAlbumArtwork(const song_t *song, bitmap_t *bitmap)
{

  if (bitmap->destroy_needed) {
    al_destroy_bitmap(bitmap->handle);
    bitmap->destroy_needed = false;
  }

  bitmap->handle = nullptr;

  switch (Config->skin_general->album_mode_artwork_mode) {

    case artwork_mode_e::None :
      break; // keep as nullptr

    case artwork_mode_e::Specified :
      bitmap->handle = Config->skin_general->album_mode_missing_artwork.handle;
      break;

    case artwork_mode_e::Logo :
      bitmap->handle = Display->fruitbox_logo_bm;
      break;

    case artwork_mode_e::Folder :
      {
        // try and load artwork from song->filename (path excluding filename)
        LoadFolderArtwork(song, &bitmap->handle);
        if (bitmap->handle)
        {
          bitmap->destroy_needed = true;
        }
        break;
      }

    case artwork_mode_e::Auto :
      {
        LoadFolderArtwork(song, &bitmap->handle);
        if (bitmap->handle)
        {
          bitmap->destroy_needed = true;
        }
        else if (Config->skin_general->album_mode_missing_artwork.handle != nullptr) // none available so use the bitmap specified in the config file
        {
          bitmap->handle = Config->skin_general->album_mode_missing_artwork.handle;
        }
        else // none specified, so use the fruitbox logo
        {
          bitmap->handle = Display->fruitbox_logo_bm;
        }
        break;
      }

  }
}

void AudioClass::LoadArtworkThread(void)
{
  unique_lock<mutex> artwork_guard(artwork_mtx);

  while (Engine_finished == false)
  {
    get_artwork.wait(artwork_guard);

    if (Engine_finished == true) break;
    
    int err { MPG123_OK };
    mpg123_id3v1 *v1 {};
    mpg123_id3v2 *v2 {};
    mpg123_handle *mp {};
    int meta {};

    artwork_song->artwork.handle = nullptr;

    if (artwork_song->artwork.destroy_needed) {
      al_destroy_bitmap(artwork_song->artwork.handle);
      artwork_song->artwork.handle = nullptr;
      artwork_song->artwork.destroy_needed = false;
    }

    switch (Config->skin_general->now_playing_artwork_mode) {

      case artwork_mode_e::None :
        break; // keep as nullptr

      case artwork_mode_e::Specified :
        artwork_song->artwork.handle = Config->skin_general->now_playing_missing_artwork.handle;
        break;

      case artwork_mode_e::Logo :
        artwork_song->artwork.handle = Display->fruitbox_logo_bm;
        break;

      case artwork_mode_e::Folder :
        {
          LoadFolderArtwork(artwork_song, &artwork_song->artwork.handle);
          if (artwork_song->artwork.handle)
          {
            artwork_song->artwork.destroy_needed = true;
          }
        }
        break;

      case artwork_mode_e::Auto :
      case artwork_mode_e::Embedded :
        if ((mp = mpg123_new(nullptr, &err)) == nullptr) return;
        mpg123_param(mp, MPG123_FLAGS, MPG123_QUIET | MPG123_PICTURE, 0);
        if (mpg123_open(mp, artwork_song->filename.c_str()) != MPG123_OK) return;
        mpg123_scan(mp); // SLOW!
        meta = mpg123_meta_check(mp);
        if (meta & MPG123_ID3 && mpg123_id3(mp, &v1, &v2) == MPG123_OK)
        {
          if (v2 != nullptr)
          {
            uint32_t type_sel { 0 };

            // look for type = 3 (cover art); if not found just use first one

            if (v2->pictures)
            {
              for (size_t i=0;i<v2->pictures; ++i)
              {
                if (static_cast<uint32_t>(v2->picture[i].type) == mpg123_id3_pic_back_cover) type_sel = i;
              }
              ALLEGRO_FILE *cover_artwork_f = al_open_memfile(v2->picture[type_sel].data, v2->picture[type_sel].size, "rb");
              if (cover_artwork_f) // use artwork from MP3 file...
              {
                artwork_song->artwork.handle = al_load_bitmap_f(cover_artwork_f, ".jpg");
                al_fclose(cover_artwork_f);
                artwork_song->artwork.destroy_needed = true;
              }
            }
          }
        }

        if ((Config->skin_general->now_playing_artwork_mode == artwork_mode_e::Auto) && (artwork_song->artwork.destroy_needed == false)) // auto mode, and no embedded image found, so use missing artwork image or fruitbox logo...
        {
          // try and load artwork from artwork_song->filename (path excluding filename)
         LoadFolderArtwork(artwork_song, &artwork_song->artwork.handle);
          if (artwork_song->artwork.handle)
          {
            artwork_song->artwork.destroy_needed = true;
          }
          else if (Config->skin_general->now_playing_missing_artwork.handle != nullptr) // none available so use the bitmap specified in the config file
          {
            artwork_song->artwork.handle = Config->skin_general->now_playing_missing_artwork.handle;
          }
          else // none specified, so use the fruitbox logo
          {
            artwork_song->artwork.handle = Display->fruitbox_logo_bm;
          }
        }

        mpg123_close(mp);
        mpg123_delete(mp);

        break;
    }

    LoadArtworkThread_status_event |= StatusEvent_NewArtwork;
  }
  LoadArtworkThread_finished = true;
}

bool AudioClass::AttachMP3ToMixer
(
  const string &filename
)
{
  int32_t channels, encoding;
  long rate;
  uint32_t samples;
  ALLEGRO_CHANNEL_CONF allegro_channels;

  size_t err = mpg123_getformat(AudioClass::mp3, &rate, &channels, &encoding);
  if (err != MPG123_OK)
  {
    log_file << WARNING << "Couldn't get audio format for file '" << filename << "'" << endl;
    // RemoveSong(false); // NEED TO THINK ABOUT THIS AS WITH STREAMING REMOVESONG() WILL CLEAR AUIOCLASS::PLAY_SONG WHICH WILL TERMINATE CURLOPT_WRITEFUNCTION
    return false;
  }

  if (rate == 0)
  {
    log_file << WARNING << "Audio Rate zero! for file '" << filename << "'" << endl;
    // RemoveSong(false);
    return false;
  }

  int32_t divisor { channels*mpg123_encsize(encoding) };

  if (divisor == 0) {
    log_file << WARNING << "Invalid audio format for file '" << filename << "'" << endl;
    // RemoveSong(false);
    return false;
  }

  if (channels == MPG123_MONO)
  {
    stereo = false;
    allegro_channels = ALLEGRO_CHANNEL_CONF_1;
  }
  else
  {
    stereo = true;
    allegro_channels = ALLEGRO_CHANNEL_CONF_2;
  }

  samples = AudioClass::mp3_buffer_size/(divisor);

  // detach audio stream if previously attached...
  if (AudioClass::mp3_stream != nullptr)
  {
    al_detach_audio_stream(AudioClass::mp3_stream);
    al_destroy_audio_stream(AudioClass::mp3_stream);
    AudioClass::mp3_stream = nullptr;
  }

  AudioClass::mp3_stream = al_create_audio_stream(audio_stream_fragments, samples, rate, ALLEGRO_AUDIO_DEPTH_INT16, allegro_channels);
  if (!AudioClass::mp3_stream) error("Couldn't create mp3_stream");
  if (al_get_audio_stream_attached(AudioClass::mp3_stream))
  {
    al_detach_audio_stream(AudioClass::mp3_stream);
  }
  if (!al_attach_audio_stream_to_mixer(AudioClass::mp3_stream, AudioClass::songs_mixer)) error("Couldn't attach mp3_stream");

  return true;
}

bool AudioClass::LoadSong(bool delay)
{
  SongPlayThread_status_event |= StatusEvent_StopAttractModeTimer;
  if (delay) SleepFrameTicks(Config->skin_general->song_load_time.ticks);
  status.now_playing_start_time = time(nullptr);
  if (status.now_playing->play_type == play_type_e::AttractMode)
  {
    status.now_playing_start_time -= Config->ini_attract->fade_in_position.ticks / display_refresh_rate;
    if (Config->ini_attract->fade_in.ticks)
    {
      uint32_t silent { 0 };
      SetVolume(silent); // start fade in from silent
    }
  }
  else
  {
    SetVolume(Config->ini_general->song_volume, true);
  }

  PlayQueue->AddToHistory(0);
  AudioClass::paused = false;
  song_play_state = song_play_state_e::playing;

  // if (AudioClass::mp3_stream)
  // {
    // al_detach_audio_stream(AudioClass::mp3_stream);
    // al_destroy_audio_stream(AudioClass::mp3_stream);
    // AudioClass::mp3_stream = nullptr;
    // AudioClass::mp3_buffer = nullptr;
  // }

  SongPlayThread_status_event |= StatusEvent_SongStart | StatusEvent_SongPauseChange;

  switch (status.now_playing->type)
  {
    case song_type_e::ogv :
      SongPlayThread_status_event |= StatusEvent_SongVideoStart;
      break;
      
    case song_type_e::url :
      start_url_read.notify_all(); // tell GetCURLDataThread to start
      if (Audio->AttachMP3ToMixer(status.now_playing->filename) == false)
      {
        RemoveSong(false);
        return false;
      }
      break;

    case song_type_e::mp3 :
      if (Audio->AttachMP3ToMixer(status.now_playing->filename) == false)
      {
        RemoveSong(false);
        return false;
      }
      break;

    default : // song_type_e::unknown
      return false;
      break;
  }
  return true;
}

void AudioClass::PlaySongThread(void)
{
  size_t decoded_bytes {};

  while (Engine_finished == false)
  {
    switch (song_play_state)
    {
      case song_play_state_e::playing :
        switch (status.now_playing->type)
        {
          ///////////////////////////////////////////////
          // Playback of MP3 or URL files...
          case song_type_e::mp3 :
          case song_type_e::url :
            do
            {
              if (AudioClass::paused == false)
              {
                AudioClass::mp3_buffer = (unsigned char *)al_get_audio_stream_fragment(AudioClass::mp3_stream); // get ptr to a free fragment

                if (AudioClass::mp3_buffer != nullptr) // audio stream (output) ready for new data
                {
                  int err = mpg123_read(AudioClass::mp3, AudioClass::mp3_buffer, AudioClass::mp3_buffer_size, &decoded_bytes); // ...if fragment available, decode mp3 data into it
                  switch (err)
                  {
                    case MPG123_NEW_FORMAT :
                      Audio->AttachMP3ToMixer(status.now_playing->filename);
                      decoded_bytes = 1; // ensure we don't exit while loop
                      break;

                    case MPG123_OK :
                      al_set_audio_stream_fragment(AudioClass::mp3_stream, AudioClass::mp3_buffer); // ready to play out
                      break;

                    case MPG123_NEED_MORE :
                      break;
                  }
                }
              }
            } while (decoded_bytes && AudioClass::play_song);

            if (status.now_playing->type == song_type_e::url)
            { // ensure CurlGetData has finished
              while (GetCURLDataBusy) this_thread::sleep_for(chrono::milliseconds(1)); // wait here
            }

            // song finished naturally or play_song set false (song skipped)...
            al_detach_audio_stream(AudioClass::mp3_stream);
            al_destroy_audio_stream(AudioClass::mp3_stream);
            AudioClass::mp3_stream = nullptr;
            mpg123_close(AudioClass::mp3);

            break;

          ///////////////////////////////////////////////
          // Playback of OGV files...
          case song_type_e::ogv :
            do
            {
            }
            while (AudioClass::play_song);

            break;

          default : // song_type_e::unknown
            break;
        }

        song_play_state = song_play_state_e::unloading;
        clear_equalizer(); // clear out spectrum analyser pipeline...

        // update number of songs played status (and total length)
        ++num_songs_played;
        status.num_songs_played_str = to_string(num_songs_played);

        songs_played_total_time += status.now_playing->length;
        status.songs_played_total_time_str = StrHrMinSec(songs_played_total_time);

        if (status.now_playing->play_type == play_type_e::AttractMode && Config->ini_attract->skip_load)
        { // don't execute unload sequence
          // song_play_state = song_play_state_e::stopped;
          RemoveSong(skipped);
        }
        else
        {
          SongPlayThread_status_event |= StatusEvent_SongUnload;
        }
        break;

      case song_play_state_e::unloading :
        // NEED THE NEXT DELAY OTHERWISE SONG VIDEO HAS STUTTER AFTER MP3 PLAY !!!???!?! (SEEMS TO NEEDS TO BE MORE THAN ONE VIDEO FRAME PERIOD, SO MAKE IT TWO TO BE SURE)
        {
          SleepFrameTicks(2);
          SleepFrameTicks(Config->skin_general->song_unload_time.ticks);
        }
        RemoveSong(skipped); // also clears status.now_playing information
        break;

      case song_play_state_e::stopped :
        if (PlayQueue->NumSongsTotal())
        { // a song in the queue ready to be played...
          song_t *next_up { PlayQueue->QuerySong(0) };
          if (next_up != nullptr)
          {

            switch (next_up->type)
            {
              ///////////////////////////////////////////////
              // Load MP3 file...
              case song_type_e::mp3 :
                if ((iohandle->fd = open(next_up->filename.c_str(), O_RDONLY)) < 0)
                {
                  RemoveSong(false);
                  continue;
                }

                if (mpg123_replace_reader_handle(AudioClass::mp3, AudioClass::file_read_cb, AudioClass::file_lseek_cb, AudioClass::file_cleanup_cb) != MPG123_OK)
                {
                  error("mpg123_replace_reader_handle failed");
                }

                if (mpg123_open_handle(AudioClass::mp3, iohandle) != MPG123_OK)
                {
                  RemoveSong(false);
                  continue;
                }

                if (next_up->play_type == play_type_e::AttractMode)
                {
                  off_t frame_offset = mpg123_timeframe(AudioClass::mp3, Config->ini_attract->fade_in_position.ticks / display_refresh_rate);
                  if (mpg123_seek_frame(AudioClass::mp3, frame_offset, SEEK_SET) < 0)
                  {
                    RemoveSong(false);
                    continue;
                  }
                }
                GetSongCoverArt(next_up);
                status.now_playing = next_up;
                AudioClass::play_song = true;
                break;

              ///////////////////////////////////////////////
              // Load MP3 URL file...
              case song_type_e::url :
                if (mpg123_replace_reader_handle(AudioClass::mp3, AudioClass::stream_read_cb, AudioClass::stream_lseek_cb, AudioClass::stream_cleanup_cb) != MPG123_OK)
                {
                  error("mpg123_replace_reader_handle failed");
                }

                if (mpg123_open_handle(AudioClass::mp3, iohandle) != MPG123_OK)
                {
                  RemoveSong(false);
                  continue;
                }
                status.now_playing = next_up;
                AudioClass::play_song = true;
                break;

              ///////////////////////////////////////////////
              // Load OGV file...
              case song_type_e::ogv :
                status.now_playing = next_up;
                AudioClass::play_song = true;
                break;

              default : // song_type_e::unknown
                log_file << WARNING << "Unknown file type '" << next_up->filename << "'" << endl;
                RemoveSong(false);
                continue;
                break;
            }

            if (status.now_playing->play_type == play_type_e::AttractMode && Config->ini_attract->skip_load)
            { // don't execute load sequence
              if (LoadSong(false) == false) // song didn't load (invalid url or invalid/missing format)
              {
                song_play_state = song_play_state_e::unloading;
              }
            }
            else
            {
              song_play_state = song_play_state_e::loading;
              SongPlayThread_status_event |= StatusEvent_SongLoad;
            }

          }
        }
        else
        {
          this_thread::sleep_for(chrono::milliseconds(100));
        }
        break;

        case song_play_state_e::loading :
          if (LoadSong(true) == false) // song didn't load (invalid url or invalid/missing format)
          {
            song_play_state = song_play_state_e::unloading;
          }
          break;

    }
  }

  // ensure any waiting threads get released so they can check Engine_finished flag
  start_url_read.notify_all();
  get_artwork.notify_all();

  PlaySongThread_finished = true;
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


ssize_t AudioClass::file_read_cb(void *handle, void *buf, size_t sz)
// attempt to read sz bytes into buf from handle device
{
  ssize_t ret;
  ioh *h = static_cast<ioh *>(handle);

  errno = 0;
  ret = read(h->fd, buf, sz);
  if(ret < 0) fprintf(stderr, "read error: %s\n", strerror(errno));
  return ret;
}

off_t AudioClass::file_lseek_cb(void *handle, off_t offset, int whence)
{
  off_t ret;
  ioh *h = static_cast<ioh *>(handle);
  ret = lseek(h->fd, offset, whence);
  if(ret < 0) fprintf(stderr, "seek error (%d, %d): %s\n", ret, errno, strerror(errno));

  return ret;
}

/* The cleanup handler is called on mpg123_close(), it can cleanup your part of the mess... */
void AudioClass::file_cleanup_cb(void *handle)
{
  ioh *h = static_cast<ioh *>(handle);
  close(h->fd);
  h->fd = -1;
}

ssize_t AudioClass::stream_read_cb(void *handle, void *buf, size_t sz)
// attempt to read sz bytes into buf from handle device
{
  ssize_t ret;
  ioh *h = static_cast<ioh *>(handle);

  if (AudioClass::curl_buffer.occ > CURL_BUFFER_SIZE) // too much data in buffer, so reset read side...
  {
    AudioClass::icy_buffer_mtx.lock();
    AudioClass::curl_buffer.occ = 0;
    AudioClass::curl_buffer.rptr = AudioClass::curl_buffer.wptr;
    AudioClass::icy_buffer_mtx.unlock();
  }
  
  while (sz > AudioClass::curl_buffer.occ) // wait here until enough data is available
  {
    if (AudioClass::play_song == false) return 0; // user abort
    this_thread::sleep_for(chrono::milliseconds(1));
  }
  // copy data from curl_buffer to mpg123 buffer...

  unsigned char *src_buffer { static_cast<unsigned char *>(AudioClass::curl_buffer.data) };
  unsigned char *dst_buffer { static_cast<unsigned char *>(buf) };

  for (size_t cnt = 0; cnt < sz; ++cnt)
  {
    *dst_buffer++ = src_buffer[AudioClass::curl_buffer.rptr++];
    AudioClass::curl_buffer.rptr &= CURL_BUFFER_PTR_MASK;
    AudioClass::curl_buffer.occ.fetch_sub(1);
  }
  return sz;
}

off_t AudioClass::stream_lseek_cb(void *handle, off_t offset, int whence)
{
  return -1;
}

/* The cleanup handler is called on mpg123_close(), it can cleanup your part of the mess... */
void AudioClass::stream_cleanup_cb(void *handle)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

AudioClass::AudioClass(void)
{
  int err { MPG123_OK };

  log_file << "Initialising audio ..." << endl;

  skipped = false;
  AudioClass::play_song = false;
  song_play_state = song_play_state_e::stopped;

  err = mpg123_init();
  if (err != MPG123_OK || (AudioClass::mp3 = mpg123_new(nullptr, &err)) == nullptr) error("Failed to initialise audio decoder: %s", mpg123_plain_strerror(err));

  iohandle = static_cast<ioh *>(malloc(sizeof(ioh)));

  AudioClass::mp3_buffer_size = mpg123_outblock(AudioClass::mp3) / mp3_buffer_size_fraction;

  // make sure we don't get messy error messages on the console...
  mpg123_param(AudioClass::mp3, MPG123_FLAGS, MPG123_QUIET, 0);
  status.now_playing = &no_song;

  // set ReplayGain mode depending upon ini file setting...  
  switch (Config->ini_general->replay_gain)
  {
    case replay_gain_e::Track :
      mpg123_param(AudioClass::mp3, MPG123_RVA, MPG123_RVA_MIX, 0.0);
      break;

    case replay_gain_e::Album :
      mpg123_param(AudioClass::mp3, MPG123_RVA, MPG123_RVA_ALBUM, 0.0);
      break;
   
    default :
      mpg123_param(AudioClass::mp3, MPG123_RVA, MPG123_RVA_OFF, 0.0);
      break;
 }
 
  // sound effects connected to output_mixer (which is connected to the voice)
  // songs played through songs_mixer which allows their volume to be changed without affecting the
  // sound effect (output_mixer) volume.  songs_mixer connects to sound_effects_mixer
  
  if (AudioClass::voice == nullptr)
  {
    AudioClass::voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    if (!AudioClass::voice) error("Couldn't create audio voice");
  }
  
  if (AudioClass::output_mixer == nullptr)
  {
    AudioClass::output_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    if (!AudioClass::output_mixer) error("Couldn't create audio output_mixer");
    if (!al_attach_mixer_to_voice(AudioClass::output_mixer, AudioClass::voice)) error("Couldn't attach output_mixer to audio voice");
  }

  if (AudioClass::songs_mixer == nullptr)
  {
    AudioClass::songs_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    if (!AudioClass::songs_mixer) error("Couldn't create audio songs_mixer");
    if (!al_attach_mixer_to_mixer(AudioClass::songs_mixer, AudioClass::output_mixer)) error("Couldn't attach songs_mixer to output_mixer");
  }

  // load gain_db steps for log volume...
  gain_db.push_back(0); // first entry is mute
  for (uint32_t i = MinSongVolume + 1; i <= MaxSongVolume; ++i) // 1.100
  {
    uint32_t percent { (i - MinSongVolume) * (MaxSongVolume - MinSongVolume) / MaxSongVolume};
    double factor {static_cast<double>(percent) / 100.0};
    double g { pow(factor, 2)};
    gain_db.push_back(g);
  }

  // for (size_t i=0;i<gain_db.size();++i) cout << i << " " << gain_db.at(i) << endl;

  log_file << endl;

#ifdef DUMP_STREAM_DATA
   stream_data = fopen("./stream_data.bin", "wb");
   if (stream_data == NULL)  /* If an error occurs during the file creation */
   {
     error("Couldn't open stream data file for writing");
   }
#endif
}

bool isNullOrWhitespace(const std::string& str) {
  return str.empty()
      || std::all_of(str.begin(), str.end(), [](char c) {
      return std::isspace(static_cast<unsigned char>(c));
  });
}

size_t AudioClass::GetCURLICYHeader
(
  char *buffer,
  size_t size,
  size_t nitems,
  void *userdata
)
{
  size_t pos;
  size_t numbytes = size * nitems;
  buffer[numbytes-1] = '\0';
  string str { buffer };

  str.erase(std::remove(str.begin(), str.end(), 13), str.end()); // remove CR (for non-linux text file)
  str.erase(std::remove(str.begin(), str.end(), 10), str.end()); // remove LF (for non-linux text file)

  // first check the content type is mpeg audio...

  if (str.find("200 OK") != string::npos) // acknowledge received
  {
    AudioClass::curl_icy.header_ok = true;
    // cout << "-----> 200 OK received from ICY header request" << endl;
  }

  if (str.find("audio/mpeg") != string::npos) // find Content-Type "audio/mpeg "
  {
    AudioClass::curl_icy.is_audio_mpeg = true;
    // cout << "-----> It's an mpeg audio stream" << endl;
  }

  pos = str.find("icy-description:");
  if (pos != string::npos)
  {
    string ss { str.substr(pos+16, string::npos) }; // jump over "icy-description:"
    getline(istringstream(ss), AudioClass::curl_icy.description);
    // cout << "-----> icy-description is " << AudioClass::curl_icy.description << endl;
    if (isNullOrWhitespace(AudioClass::curl_icy.description)) AudioClass::curl_icy.description.clear(); // make it actually empty
  }

  pos = str.find("icy-name:");
  if (pos != string::npos)
  {
    string ss { str.substr(pos+9, string::npos) }; // jump over "icy-name:"
    getline(istringstream(ss), AudioClass::curl_icy.name);
    // cout << "-----> icy-name is " << AudioClass::curl_icy.name << endl;
    if (isNullOrWhitespace(AudioClass::curl_icy.name)) AudioClass::curl_icy.name.clear(); // make it actually empty
  }

  pos = str.find("icy-genre:");
  if (pos != string::npos)
  {
    string ss { str.substr(pos+10, string::npos) }; // jump over "icy-genre:"
    getline(istringstream(ss), AudioClass::curl_icy.genre);
    // cout << "-----> icy-genre is " << AudioClass::curl_icy.genre << endl;
    if (isNullOrWhitespace(AudioClass::curl_icy.genre)) AudioClass::curl_icy.genre.clear(); // make it actually empty
  }

  pos = str.find("icy-metaint:");
  if (pos != string::npos)
  {
    string ss { str.substr(pos+12, string::npos) }; // jump over "icy-metaint:"
    istringstream(ss) >> AudioClass::curl_icy.metadata_interval;
    // cout << "-----> icy-metaint is " << AudioClass::curl_icy.metadata_interval << endl;
    AudioClass::curl_icy.metadata_valid = true;
  }

  return numbytes;
}

size_t AudioClass::GetCURLData_EmptyWriteFunction
(
  void *buffer,
  size_t size,
  size_t nmemb,
  void *userp
)
{
  return 0; // only interested in headers
};

size_t AudioClass::GetCURLData_WriteFunction
(
  void *buffer,
  size_t size,
  size_t nmemb,
  void *userp
)
{
  static unsigned char *icy_metadata_ptr {};

  if (AudioClass::play_song && AudioClass::curl_icy.header_ok && AudioClass::curl_icy.is_audio_mpeg)
  {
#ifdef DUMP_STREAM_DATA
    size_t elements_written = fwrite((unsigned char*)buffer, size, nmemb, stream_data); // write to file for post run analysis debug
#endif
    // copy data (size * nmemb bytes) from *buffer to *userp (note userp points to CURLOPT_WRITEDATA, curl_buffer in our case)
    unsigned char *src_buffer { static_cast<unsigned char *>(buffer) };
    unsigned char *dst_buffer { static_cast<unsigned char *>(userp) };
    size_t cnt_max { size * nmemb };

    if (AudioClass::paused) return size * nmemb; // don't store data

    // every AudioClass::curl_icy.metadata_interval bytes, extract ICY metadata
    AudioClass::icy_buffer_mtx.lock();
    for (size_t cnt = 0; cnt < cnt_max; ++cnt)
    {
      unsigned char src_data { *src_buffer++ };
      if (AudioClass::curl_icy.metadata_cnt) // within metadata
      {
        *icy_metadata_ptr++ = src_data; // store icy_metadata
        // log_file << " " << offset << " " << AudioClass::curl_buffer.AudioClass::curl_icy.metadata_cnt << " metadata " << src_data << endl;
        if (--AudioClass::curl_icy.metadata_cnt == 0) // end of metadata chunk
        {
          *icy_metadata_ptr = '\0'; // terminate string
          GetCURLDataThread_status_event |= StatusEvent_ICYDataReady; // signal to engine that metadata is available
        }
      }
      else if ((AudioClass::curl_icy.metadata_interval_cnt == AudioClass::curl_icy.metadata_interval) && AudioClass::curl_icy.metadata_valid)
      { // start of icy_metadata
        AudioClass::curl_icy.metadata_interval_cnt = 0; // reset metaint count for incrementing during next data section
        AudioClass::curl_icy.metadata_cnt = static_cast<uint32_t>(src_data) * 16;
        icy_metadata_ptr = AudioClass::curl_icy.metadata;
      }
      else // not icy_metadata, so forward data from src_buffer to dst_buffer...
      {
        dst_buffer[AudioClass::curl_buffer.wptr++] = src_data;
        AudioClass::curl_buffer.wptr &= CURL_BUFFER_PTR_MASK;
        AudioClass::curl_buffer.occ.fetch_add(1);
        AudioClass::curl_icy.metadata_interval_cnt++;
      }
      AudioClass::icy_buffer_mtx.unlock();
    }
    return size * nmemb;
  }

  return 0; // finish the transfer
};

void AudioClass::GetCURLDataThread(void)
{
  unique_lock<mutex> start_url_read_guard(start_url_read_mtx);
  while (Engine_finished == false)
  {
    start_url_read.wait(start_url_read_guard); // wait until main state machine needs url data

    if (Engine_finished == true) break;
    
    GetCURLDataBusy = true;
    
    // reset data buffer and metadata flags...
    AudioClass::icy_buffer_mtx.lock();
    AudioClass::curl_buffer.wptr = AudioClass::curl_buffer.rptr = AudioClass::curl_buffer.occ = 0;
    AudioClass::icy_buffer_mtx.unlock();

    AudioClass::curl_icy.metadata_interval_cnt = AudioClass::curl_icy.metadata_cnt = 0;
    AudioClass::curl_icy.header_ok = false;
    AudioClass::curl_icy.is_audio_mpeg = false;
    AudioClass::curl_icy.metadata_valid = false;
    AudioClass::curl_icy.name.clear();
    AudioClass::curl_icy.description.clear();
    AudioClass::curl_icy.genre = UnknownGenreStr;

    struct curl_slist *headers { nullptr };
    headers = curl_slist_append(headers, "Icy-MetaData:1");
    AudioClass::curl = curl_easy_init();

    if (AudioClass::curl)
    {
      curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, CURL_MAX_WRITE_SIZE);
      curl_easy_setopt(AudioClass::curl, CURLOPT_HEADERFUNCTION, GetCURLICYHeader);
      curl_easy_setopt(AudioClass::curl, CURLOPT_WRITEDATA, static_cast<void*>(AudioClass::curl_buffer.data));
      curl_easy_setopt(AudioClass::curl, CURLOPT_WRITEFUNCTION, AudioClass::GetCURLData_WriteFunction);
      curl_easy_setopt(AudioClass::curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(AudioClass::curl, CURLOPT_URL, status.now_playing->filename.c_str());
      curl_easy_perform(AudioClass::curl);
      curl_slist_free_all(headers);
    }
    curl_easy_cleanup(AudioClass::curl);
    GetCURLDataBusy = false;
  }
  GetCURLDataThread_finished = true;
}

void AudioClass::Run(void)
{
  if (spectrum_analyser)
  {
    // load equaliser with 1.0's in all sub-bands to activate the equaliser (for our spectrum values to be refreshed)
    for (int i = 0;i < 32; ++i)
    {
      mpg123_eq(mp3, MPG123_LEFT,  i, 1.0);
      mpg123_eq(mp3, MPG123_RIGHT, i, 1.0);
    }
    init_equalizer(); // initialise the log gain lut
  }

  // al_set_mixer_gain(al_get_default_mixer(), 1.0);
  // al_set_mixer_gain(AudioClass::songs_mixer, 1.0);
  // al_set_mixer_gain(AudioClass::output_mixer, 1.0);

  thread GetCURLDataThread { &AudioClass::GetCURLDataThread, this };
  GetCURLDataThread.detach();

  thread PlaySongThread { &AudioClass::PlaySongThread, this };
  PlaySongThread.detach();

  thread LoadArtworkThread { &AudioClass::LoadArtworkThread, this };
  LoadArtworkThread.detach();
}

AudioClass::~AudioClass()
{
#ifdef DUMP_STREAM_DATA
  fclose(stream_data);
#endif
  song_play_state = song_play_state_e::stopped;
  free(iohandle);
  mpg123_close(AudioClass::mp3);
  mpg123_delete(AudioClass::mp3);
  mpg123_exit();
}

void AudioClass::PlaySound
(
  sound_t &sound
)
{
  if (sound.handle == nullptr) return;

  float master_vol { Config->ini_general->song_volume / 100.0 };

  al_stop_sample(&sound.id);
  al_play_sample(sound.handle, master_vol * static_cast<float>(sound.volume) / static_cast<float>(MaxSongVolume), 0.0, 1.0, (sound.loop == true) ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, &sound.id);
}

void AudioClass::StopSound
(
  sound_t &sound
)
{
  if (sound.handle == nullptr) return;
  al_stop_sample(&sound.id);
}

void AudioClass::GetSongCoverArt
(
  song_t *song
)
{
  artwork_song = song;
  get_artwork.notify_all();
}

void AudioClass::GetID3Metadata
// for extracting (one time) metadata during database creation
(
  const char *filename,
  vector<song_t> &song
)
{
  song_t s {};
  s.type = song_type_e::mp3;

  mpg123_handle *mp {};
  int meta {};
  int ch {}, enc {};
  long rt {};
  mpg123_id3v1 *v1 {};
  mpg123_id3v2 *v2 {};
  int err { MPG123_OK };

  if ((mp = mpg123_new(nullptr, &err)) == nullptr)
  {
    error("Failed to initialise mpg123: %s", mpg123_plain_strerror(err));
  }
  
  mpg123_param(mp, MPG123_FLAGS, MPG123_QUIET, 0);
  if (mpg123_open(mp, filename) != MPG123_OK)
  {
    error("Cannot open '%s'", filename);
  }
  
  mpg123_getformat(mp, &rt, &ch, &enc);
  if (rt == 0) {
    log_file << WARNING << "Audio Rate zero! (" << filename << ")" << endl;
    // song.push_back(s);
    return;
  }

  mpg123_scan(mp);
  meta = mpg123_meta_check(mp);

  s.length = mpg123_length(mp) / rt;
  s.lengthStr = StrMinSec(s.length);

  if (meta & MPG123_ID3)
  {
    if (mpg123_id3(mp, &v1, &v2) == MPG123_OK)
    {
      if (v1 != nullptr)
      {
        s.title  = v1->title;
        s.artist = v1->artist;
        s.album  = v1->album;
        s.year   = v1->year;

        uint32_t genre {static_cast<uint32_t>(v1->genre)};
        if (genre < NUM_GENRES)
        {
          s.genre = GenreStr.at(genre);
        }
      }

      if (v2 != nullptr)
      {
        for (size_t i {0}; i<v2->texts; ++i)
        {
          if (!strncmp("TALB", v2->text[i].id, 4))      s.album = v2->text[i].text.p;
          else if (!strncmp("TIT2", v2->text[i].id, 4)) s.title = v2->text[i].text.p;
          else if (!strncmp("TRCK", v2->text[i].id, 4)) s.trackNumber = atoi(v2->text[i].text.p);
          else if (!strncmp("TYER", v2->text[i].id, 4)) s.year = v2->text[i].text.p;
          else if (!strncmp("TPE1", v2->text[i].id, 4)) s.artist = v2->text[i].text.p;
          else if (!strncmp("TPE2", v2->text[i].id, 4)) s.albumArtist = v2->text[i].text.p;
          else if (!strncmp("TPUB", v2->text[i].id, 4)) s.publisher = v2->text[i].text.p;
          else if (!strncmp("TSRC", v2->text[i].id, 4)) s.isrc = v2->text[i].text.p;
          else if (!strncmp("TCON", v2->text[i].id, 4))
          {
            // half-hearted effort at parsing tags...
            // Can replace first bracketed number (X) with ID3v1 Genre(X) (as long as it starts at the beginning of the string)
            // If first character is not a '(' then it just copies the tag string into the song's genre string.
            // Can't support multiple (X) ID3v1 tag references.
            // Can't retain other user characters in presence of ID3v1 reference.
            string tag { v2->text[i].text.p };
            if (tag.size())
            {
              s.genre = tag;
              if (tag.at(0) == '(') // ID3v1 reference (NUM)
              {
                if (tag.size() > 1)
                {
                  istringstream ss { &tag.at(1) }; // skip first '('
                  uint32_t genre { NUM_GENRES };
                  ss >> genre;
                  if ((ss.fail() == false) && genre < NUM_GENRES)
                  {
                    s.genre = GenreStr.at(genre);
                  }
                }
              }
            }

          }
          if (Config->ini_general->custom_mp3_tag.size())
          {
            if (!strncmp(Config->ini_general->custom_mp3_tag.c_str(), v2->text[i].id, Config->ini_general->custom_mp3_tag.size())) s.custom_tag = v2->text[i].text.p;
          }
        }
      }
    }

    if ((v1 == nullptr) && (v2 == nullptr))
    {
      error("'%s' has no MP3 ID3v1 or ID3v2 tag information", filename);
    }
  }

  mpg123_close(mp);
  mpg123_delete(mp);
  song.push_back(s);
}

void AudioClass::ExtractArtistAndTitle(song_t &song, string line)
{
  try {
    line.erase(0, line.find_first_of(",") + 1); // remove characters upto first comma, leaving "Artist - Title"
  }
  catch (const std::out_of_range &err) {
    return;
  }
  string title { line };
  size_t pos { title.find(" - ") };
  if (pos != string::npos)
  try {
    title.erase(0, pos+3);
  }
  catch (const std::out_of_range &err) {
    return;
  }
  song.title = title;
  try {
    line.erase(pos); // leaves "Artist"
  }
  catch (const std::out_of_range &err) {
    return;
  }
  song.artist = line;
}

bool AudioClass::GetICYMetadata(song_t &song)
{
  // ask for details about the stream from the server, and return true if it's an audio/mpeg ...
  AudioClass::curl_icy.header_ok = false;
  AudioClass::curl_icy.is_audio_mpeg = false;
  AudioClass::curl_icy.metadata_valid = false;
  AudioClass::curl_icy.name.clear();
  AudioClass::curl_icy.description.clear();
  AudioClass::curl_icy.genre = UnknownGenreStr;

  AudioClass::curl = curl_easy_init();
  if (AudioClass::curl)
  {
    curl_easy_setopt(AudioClass::curl, CURLOPT_HEADERFUNCTION, GetCURLICYHeader);
    curl_easy_setopt(AudioClass::curl, CURLOPT_WRITEDATA, static_cast<void*>(AudioClass::curl_buffer.data));
    curl_easy_setopt(AudioClass::curl, CURLOPT_WRITEFUNCTION, AudioClass::GetCURLData_EmptyWriteFunction); // need this else output goes to stdout
    curl_easy_setopt(AudioClass::curl, CURLOPT_URL, song.filename.c_str());
    curl_easy_setopt(AudioClass::curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_perform(AudioClass::curl);
  }
  curl_easy_cleanup(AudioClass::curl);
  if (AudioClass::curl_icy.header_ok && AudioClass::curl_icy.is_audio_mpeg)
  {
    if (AudioClass::curl_icy.name.size())
    {
      song.title = AudioClass::curl_icy.name;
    }

    if (AudioClass::curl_icy.description.size())
    {
      song.artist = AudioClass::curl_icy.description;
    }

    if (AudioClass::curl_icy.genre.size())
    {
      song.genre = AudioClass::curl_icy.genre;
    }

    return true;
  }
  else
  {
    log_file << WARNING << song.filename << " (" << song.title << ") is not an active or valid mpeg audio stream" << endl;
  }
  return false;
}


void AudioClass::GetOGVMetadata
(
  const char *filename,
  vector<song_t> &song
)
{
  // no metadata in OGV files, so assume filename is of format "Artist - Title" and extract metadata from the filename
  // all other tag data will need to be manually added to the database by the user :(
  song_t s {};
  s.type = song_type_e::ogv;

  string line { string(filename) };
  line.erase(0, line.find_last_of("/")+1); // remove path
  line.erase(line.find_last_of("."), string::npos); // remove extension

  ExtractArtistAndTitle(s, line);
  song.push_back(s);
}


void AudioClass::GetPLSMetadata
(
  const char *filename,
  vector<song_t> &song
)
{
  // string str;
  PLSConfigClass *plsConfig = new PLSConfigClass();

  ifstream plsFile;
  string line;

  // plsFile.open(filename.c_str(), ios::in);
  plsFile.open(filename, ios::in);

  if (plsFile.is_open())
  {
    song_t s {};
    s.type = song_type_e::url;

    uint32_t current_file_num {1};

    while (1) // Look for FileX and its TitleX entry (X = current_file_num starting at 1, and finishing when next X is not found)
    {
      string FileX { plsFile_File + to_string(current_file_num) };
      string TitleX { plsFile_Title + to_string(current_file_num) };
      s.title = UnknownTitleStr;
      bool found_entry { false };
      // start at beginning of file to look for next FileX
      plsFile.clear();
      plsFile.seekg(0, plsFile.beg);
      while (getline(plsFile, line)) // look in each line of the file for FileX entry
      {
        if (plsConfig->GetParam(true, line, FileX.c_str(), s.filename)) // found FileX= (X=1,2,3, etc.)
        {
          found_entry = true;
          // start at beginning of file again, to search for corresponding TitleX
          plsFile.clear();
          plsFile.seekg(0, plsFile.beg);
          while (getline(plsFile, line)) // look in each line of the file for TitleX entry
          {
            if (plsConfig->GetParam(true, line, TitleX.c_str(), s.title))
            {
              break; // found TitleX
            }
          }

          if (GetICYMetadata(s))
          {
            song.push_back(s);
          }

          ++current_file_num;
          break; // move onto next X
        }
      }
      if (found_entry == false) break; // didn't found FileX, so stop looking for more
    }
    delete(plsConfig);
    plsFile.close();
  }
}


void AudioClass::GetM3UMetadata
(
  const char *filename,
  vector<song_t> &song
)
{

  ifstream m3uFile;
  string line;

  m3uFile.open(filename, ios::in);

  if (m3uFile.is_open())
  {
    song_t s {};
    s.type = song_type_e::url;

    while (getline(m3uFile, line))
    {
      if (line.empty()) continue;

      s.title = UnknownTitleStr;
      s.artist = UnknownArtistStr;
      
      line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
      line.erase(std::remove(line.begin(), line.end(), 13), line.end()); // remove CR (for non-linux text file)
      line.erase(std::remove(line.begin(), line.end(), 10), line.end()); // remove LF (for non-linux text file)

      if (line.find(m3uFile_ExtInf) != string::npos)
      {
        ExtractArtistAndTitle(s, line);
      }
      else if (line.find(URLPrefix) != string::npos) // string contains "http"
      {
        s.filename = line;
        if (GetICYMetadata(s))
        {
          song.push_back(s);
        }
      }
    }
    m3uFile.close();
  }

}

void AudioClass::Mute(void)
{
  uint32_t mute { 0 };
  SetVolume(mute, true);
  muted = true;
  Engine->status_event |= StatusEvent_MuteChange;
}

void AudioClass::UnMute(void)
{
  SetVolume(Config->ini_general->song_volume, true);
  muted = false;
  Engine->status_event |= StatusEvent_MuteChange;
}

void AudioClass::SetVolume
(
  uint32_t &vol
)
{
  // mpg123_volume(AudioClass::mp3, static_cast<double>(vol) / MaxSongVolume);
  // al_set_mixer_gain(al_get_default_mixer(), static_cast<double>(vol) / MaxSongVolume);
  SetVolume(vol, false);
}

void AudioClass::SetVolume
(
  uint32_t &vol,
  bool is_status_volume
)
{
  int32_t v { static_cast<int32_t>(vol) };
  if (v < MinSongVolume) vol = MinSongVolume;
  else if (v > MaxSongVolume) vol = MaxSongVolume;

  // al_set_mixer_gain(AudioClass::songs_mixer, static_cast<double>(vol) / MaxSongVolume);
  al_set_mixer_gain(AudioClass::songs_mixer, gain_db.at(vol));

  if (is_status_volume)
  {
    stringstream s {};
    s << vol;
    status.volume_str = s.str();
    muted = false;
    Engine->status_event |= StatusEvent_VolumeChange | StatusEvent_MuteChange;
  }
}

void AudioClass::VolumeUp
(
  uint32_t &vol
)
{
  vol += Config->ini_general->song_volume_step;
  SetVolume(vol, true);
}

void AudioClass::VolumeDown
(
  uint32_t &vol
)
{
  vol -= Config->ini_general->song_volume_step;
  SetVolume(vol, true);
}

void AudioClass::StopSong(bool skip)
{
  skipped = skip;
  AudioClass::play_song = false;
}

void AudioClass::PauseSong(void)
{
  if (AudioClass::paused)
  {
    AudioClass::paused = false;
  }
  else if (status.now_playing->type != song_type_e::url) // can't pause mp3 streams
  {
    AudioClass::paused = true;
  }
  Engine->status_event |= StatusEvent_SongPauseChange;
}
