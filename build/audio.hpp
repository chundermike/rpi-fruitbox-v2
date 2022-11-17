#pragma once

#include "fruitbox.hpp"
#include <curl/curl.h>

using namespace std;

enum class song_play_state_e
{
  loading,
  playing,
  unloading,
  stopped
};


// curl writes received data into buffer at curl_buffer.wptr
// mpg123 reads data from curl_buffer at curl_buffer.rptr

#define ICY_MAX_METADATA_SIZE ((256 * 16) + 1) /* +1 for null terminator */
// #define CURL_BUFFER_SIZE      (4 * CURL_MAX_WRITE_SIZE)
#define CURL_BUFFER_SIZE      (1024 * 1024)
#define CURL_BUFFER_PTR_MASK  (CURL_BUFFER_SIZE - 1)

struct curl_icy_t
{
  bool header_ok { false };
  bool is_audio_mpeg { false };
  bool metadata_valid { false };
  unsigned char metadata[ICY_MAX_METADATA_SIZE];// CHANGE METADATA TO C++ ARRAY FOR SAFETY!!!
  uint32_t metadata_cnt { 0 };
  uint32_t metadata_interval { 0 };
  uint32_t metadata_interval_cnt { 0 };
  string name {};
  string description {};
  string genre {};
};

struct curl_buffer_t
{
  unsigned char data[CURL_BUFFER_SIZE];// CHANGE DATA TO C++ ARRAY FOR SAFETY!!!
  uint32_t wptr, rptr {};
  atomic<uint32_t> occ {};
};

class AudioClass
{
public:
  AudioClass(void);
  ~AudioClass();
  void Run(void);
  void ExtractArtistAndTitle(song_t &song, string line);
  bool GetICYMetadata(song_t &song);
  void GetID3Metadata(const char *filename, vector<song_t> &song);
  void GetOGVMetadata(const char *filename, vector<song_t> &song);
  void GetM3UMetadata(const char *filename, vector<song_t> &song);
  void GetPLSMetadata(const char *filename, vector<song_t> &song);
  void GetSongCoverArt(song_t *song);
  void RemoveSong(bool skipped);
  bool LoadSong(bool delay);
  void PlaySongThread(void);
  void GetCURLDataThread(void);
  void LoadArtworkThread(void);
  void LoadAlbumArtwork(const song_t *song, bitmap_t *bitmap);
  void PlaySound(sound_t &sound);
  void StopSound(sound_t &sound);
  void StopSong(bool skip);
  void PauseSong(void);
  void SetVolume(uint32_t &vol);
  void SetVolume(uint32_t &vol, bool is_status_volume);
  void VolumeUp(uint32_t &vol);
  void VolumeDown(uint32_t &vol);
  void Mute(void);
  void UnMute(void);

  string song_filename {};
  string song_artist {};
  string song_album_artist {};
  string song_album {};
  string song_title {};
  mpg123_picture *song_picture {};
  int32_t song_number {};
  string song_year {};
  static atomic<bool>play_song;
  atomic<bool>skipped {};
  song_play_state_e song_play_state { song_play_state_e::stopped };
  static ALLEGRO_AUDIO_STREAM *mp3_stream;
  atomic<int32_t>SongPlayThread_status_event {};
  static atomic<int32_t>GetCURLDataThread_status_event;
  atomic<int32_t>LoadArtworkThread_status_event {};
  bool stereo {};
  bool spectrum_analyser { false };
  bool muted { false };
  static bool paused;
  static curl_icy_t curl_icy;
  static ALLEGRO_MIXER *songs_mixer;
  static ALLEGRO_MIXER *output_mixer;
  static ALLEGRO_VOICE *voice;

private:

  static mutex icy_buffer_mtx;
  // static size_t CurlGetICYHeader(char *buffer, size_t size, size_t nitems, void *userdata);
  static size_t GetCURLData_EmptyWriteFunction(void *buffer, size_t size, size_t nmemb, void *userp);
  static size_t GetCURLData_WriteFunction(void *buffer, size_t size, size_t nmemb, void *userp);
  static size_t GetCURLICYHeader(char *buffer, size_t size, size_t nitems, void *userdata);
  // static size_t CurlPlayMP3(void *buffer, size_t size, size_t nmemb, void *userp);
  // void GetICYMetadata(mpg123_handle *mp,    song_t &song);
  bool AttachMP3ToMixer(const string &filename);
  void LoadFolderArtwork(const song_t *song, ALLEGRO_BITMAP **bitmap);
  void SleepFrameTicks(uint32_t frames);
  static ssize_t file_read_cb(void *handle, void *buf, size_t sz);
  static off_t file_lseek_cb(void *handle, off_t offset, int whence);
  static void file_cleanup_cb(void *handle);
  static ssize_t stream_read_cb(void *handle, void *buf, size_t sz);
  static off_t stream_lseek_cb(void *handle, off_t offset, int whence);
  static void stream_cleanup_cb(void *handle);

  time_t start_time, current_time;
  static mpg123_handle *mp3;
  static unsigned char *mp3_buffer;
  static size_t mp3_buffer_size;
  // int32_t channels {}, encoding {};
  // long rate {};
  // uint32_t samples {};
  uint32_t num_songs_played { 0 };
  uint32_t songs_played_total_time { 0 };
  song_t no_song {};
  
  mutex artwork_mtx {};
  condition_variable get_artwork {};

  mutex start_url_read_mtx {};
  condition_variable start_url_read {};

  mutex stop_url_read_mtx {};
  condition_variable stop_url_read {};
  
  song_t *artwork_song {};

  static CURL *curl;
  static curl_buffer_t curl_buffer;
  vector<float> gain_db {};
};

