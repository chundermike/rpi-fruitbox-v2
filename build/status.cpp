#include "fruitbox.hpp"
#include "status.hpp"
#include <ftw.h>

#include <vector>

using namespace std;

int32_t StatusDisplayClass::if_song_coming_ups;
int32_t StatusDisplayClass::coming_up_song_title;
int32_t StatusDisplayClass::coming_up_song_artist;
int32_t StatusDisplayClass::coming_up_song_album;
int32_t StatusDisplayClass::coming_up_song_album_artist;
int32_t StatusDisplayClass::coming_up_song_track_number;
int32_t StatusDisplayClass::coming_up_song_year;
int32_t StatusDisplayClass::coming_up_song_genre;
int32_t StatusDisplayClass::coming_up_song_publisher;
int32_t StatusDisplayClass::coming_up_song_isrc;
int32_t StatusDisplayClass::coming_up_song_custom_tag;
int32_t StatusDisplayClass::coming_up_song_length;
uint32_t StatusDisplayClass::num_sound_channels {};

vector<string> StatusDisplayClass::static_bitmap_name;

///////////////////////////////////////////////////////////////////////////////

bool StatusDisplayClass::funcNowPlayingTitle(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->title;
  return false;
}

bool StatusDisplayClass::funcNowPlayingStreamTitle(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->stream_title;
  return false;
}

bool StatusDisplayClass::funcNowPlayingStreamUrl(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->stream_url;
  return false;
}

bool StatusDisplayClass::funcNowPlayingArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->artist;
  return false;
}

bool StatusDisplayClass::funcNowPlayingAlbum(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->album;
  return false;
}

bool StatusDisplayClass::funcNowPlayingAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->albumArtist;
  return false;
}

bool StatusDisplayClass::funcNowPlayingTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->trackNumberStr;
  return false;
}

bool StatusDisplayClass::funcNowPlayingYear(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->year;
  return false;
}

bool StatusDisplayClass::funcNowPlayingGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->genre;
  return false;
}

bool StatusDisplayClass::funcNowPlayingPublisher(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->publisher;
  return false;
}

bool StatusDisplayClass::funcNowPlayingISRC(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->isrc;
  return false;
}

bool StatusDisplayClass::funcNowPlayingCustomTag(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing->custom_tag;
  return false;
}

bool StatusDisplayClass::funcNowPlayinglength(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_length_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingElapsedTime(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_elapsed_time_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingTimeRemaining(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.now_playing_time_remaining_str;
  return false;
}

bool StatusDisplayClass::funcNowPlayingArtwork(StatusDisplayClass *s, unsigned char param)
{
  s->artwork_bitmap.handle = status.now_playing->artwork.handle;
  return false;
}

bool StatusDisplayClass::funcComingUpNumSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.coming_up_num_songs_str;
  return false;
}

bool StatusDisplayClass::funcComingUpTotalTime(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.coming_up_total_length_str;
  return false;
}

bool StatusDisplayClass::funcComingUpTitle(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_title + 1) }; // +1 since first song in play list is currently playing song
  if (song != nullptr)
  {
    s->var_str = &song->title;
    StatusDisplayClass::coming_up_song_title++; // next time the variable is used it should return the coming up song title after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpArtist(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_artist + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->artist;
    StatusDisplayClass::coming_up_song_artist++; // next time the variable is used it should return the coming up song artist after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpAlbum(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_album + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->album;
    StatusDisplayClass::coming_up_song_album++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_album_artist + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->albumArtist;
    StatusDisplayClass::coming_up_song_album_artist++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_track_number + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->trackNumberStr;
    StatusDisplayClass::coming_up_song_track_number++; // next time the variable is used it should return the coming up song album after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpYear(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_year + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->year;
    StatusDisplayClass::coming_up_song_year++; // next time the variable is used it should return the coming up song year after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpGenre(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_genre + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->genre;
    StatusDisplayClass::coming_up_song_genre++; // next time the variable is used it should return the coming up song year after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpPublisher(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_publisher + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->publisher;
    StatusDisplayClass::coming_up_song_publisher++; // next time the variable is used it should return the coming up song publisher after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpISRC(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_isrc + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->isrc;
    StatusDisplayClass::coming_up_song_isrc++; // next time the variable is used it should return the coming up song ISRC after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpCustomTag(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_custom_tag + 1) };
  if (song != nullptr)
  {
    s->var_str = &song->custom_tag;
    StatusDisplayClass::coming_up_song_custom_tag++; // next time the variable is used it should return the coming up song ISRC after this one
  }
  return false;
}

bool StatusDisplayClass::funcComingUpLength(StatusDisplayClass *s, unsigned char param)
{
  song_t *song { PlayQueue->QuerySong(StatusDisplayClass::coming_up_song_length + 1) };
  if (song != nullptr)
  {
    if (song->length)
    {
      s->coming_up_song_length_str = StrMinSec(song->length);
    }
    else
    {
      s->coming_up_song_length_str = invalidTimeMS;
    }
    s->var_str = &s->coming_up_song_length_str;
    StatusDisplayClass::coming_up_song_length++; // next time the variable is used it should return the coming up song title after this one
  }
  return false;
}

bool StatusDisplayClass::funcLastPlayedTitle(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->title;
  return false;
}

bool StatusDisplayClass::funcLastPlayedArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->artist;
  return false;
}

bool StatusDisplayClass::funcLastPlayedAlbum(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->album;
  return false;
}

bool StatusDisplayClass::funcLastPlayedAlbumArtist(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->albumArtist;
  return false;
}

bool StatusDisplayClass::funcLastPlayedTrackNumber(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->trackNumberStr;
  return false;
}

bool StatusDisplayClass::funcLastPlayedYear(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->year;
  return false;
}

bool StatusDisplayClass::funcLastPlayedGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->genre;
  return false;
}

bool StatusDisplayClass::funcLastPlayedPublisher(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->publisher;
  return false;
}

bool StatusDisplayClass::funcLastPlayedISRC(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->isrc;
  return false;
}

bool StatusDisplayClass::funcLastPlayedCustomTag(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played->custom_tag;
  return false;
}

bool StatusDisplayClass::funcLastPlayedlength(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_played_length_str;
  return false;
}

bool StatusDisplayClass::funcCredits(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.credits_str;
  return false;
}

bool StatusDisplayClass::funcSongsCredited(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.songs_credited_str;
  return false;
}

bool StatusDisplayClass::funcAttractModeGenre(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &Config->skin_general->attract_mode[Config->attract_mode_select];
  return false;
}
bool StatusDisplayClass::funcCreditsPerCoin(StatusDisplayClass *s, unsigned char param)
{
  uint32_t coin { static_cast<uint32_t>(param) };
  s->var_str = &Config->ini_general->credits_per_coin_str[coin];
  return false;
}

bool StatusDisplayClass::funcCreditsPerSong(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &Config->ini_general->credits_per_song_str;
  return false;
}

bool StatusDisplayClass::funcVolume(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.volume_str;
  return false;
}

bool StatusDisplayClass::funcSelectCode(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.select_code_str;
  return false;
}

bool StatusDisplayClass::funcNumSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_songs_str;
  return false;
}

bool StatusDisplayClass::funcNumSearchSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_search_songs_str;
  return false;
}

bool StatusDisplayClass::funcPlayQueueRemainingSpace(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.playqueue_space_str;
  return false;
}

bool StatusDisplayClass::funcNumTitleStrips(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_title_strips_str;
  return false;
}

bool StatusDisplayClass::funcFirstVisibleTitleStrip(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.first_visible_title_strip_str;
  return false;
}

bool StatusDisplayClass::funcLastVisibleTitleStrip(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.last_visible_title_strip_str;
  return false;
}

bool StatusDisplayClass::funcTotalPlayedSongs(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.num_songs_played_str;
  return false;
}

bool StatusDisplayClass::funcTotalPlayedTime(StatusDisplayClass *s, unsigned char param)
{
  s->var_str = &status.songs_played_total_time_str;
  return false;
}

bool StatusDisplayClass::funcGPIOSetPinHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t pin { static_cast<uint32_t>(param) };

  // we check if it is unused to prevent setting as an output if it is being used as button input
  // if not, we set the direction to output for subsequent calls...
  if (Gpio->direction[pin] == gpio_e::Unused)
  {
    Gpio->ConfigurePinAsOutput(pin);
  }

  if (Gpio->direction[pin] == gpio_e::Output)
  {
    Gpio->SetPin(pin);
  }

  return false;
}

bool StatusDisplayClass::funcGPIOSetPinLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t pin { static_cast<uint32_t>(param) };

  // we check if it is unused to prevent setting as an output if it is being used as button input
  // if not, we set the direction to output for subsequent calls...
  if (Gpio->direction[pin] == gpio_e::Unused)
  {
    Gpio->ConfigurePinAsOutput(pin);
  }

  if (Gpio->direction[pin] == gpio_e::Output)
  {
    Gpio->ClrPin(pin);
  }

  return false;
}

bool StatusDisplayClass::funcSetFlagLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };

  if (Config->status_flag[flag]) Engine->next_status_event |= StatusEvent_FlagChange;

  Config->status_flag[flag] = false;

  return false;
}

bool StatusDisplayClass::funcSetFlagHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };

  if (Config->status_flag[flag] == false) Engine->next_status_event |= StatusEvent_FlagChange;

  Config->status_flag[flag] = true;

  return false;
}

bool StatusDisplayClass::funcDrawBitmap(StatusDisplayClass *s, unsigned char param)
{
  if (s->bitmap_name.size())
  // bitmap directory specified and has bitmaps in it, so use these instead
  {
    s->draw_bitmap = true;
    if (++s->bitmap_idx == s->bitmap_name.size()) s->bitmap_idx = 0; // move to next bitmap
    return false;
  }

  if (s->bitmap_list.size())
  {
    s->draw_bitmap = true;
    if (++s->bitmap_idx == s->bitmap_list.size()) s->bitmap_idx = 0; // move to next bitmap
  }
  return false;
}

bool StatusDisplayClass::funcDrawRandomBitmap(StatusDisplayClass *s, unsigned char param)
{
  if (s->bitmap_name.size())
  {
    size_t size { s->bitmap_name.size() };
    if (size)
    {
      s->draw_bitmap = true;
      s->bitmap_idx = fast_random::rand() % size;
    }
    return false;
  }

  size_t size { s->bitmap_list.size() };
  if (size)
  {
    s->draw_bitmap = true;
    s->bitmap_idx = rand() % size;
  }
  return false;
}

bool StatusDisplayClass::funcUndrawBitmap(StatusDisplayClass *s, unsigned char param)
{
  s->draw_bitmap = false;
  return false;
}

bool StatusDisplayClass::funcDrawVideo(StatusDisplayClass *s, unsigned char param)
{
  s->draw_video = true;
  return false;
}

bool StatusDisplayClass::funcUndrawVideo(StatusDisplayClass *s, unsigned char param)
{
  s->draw_video = false;
  return false;
}

bool StatusDisplayClass::funcStartVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle == nullptr)
  {
    s->video.handle = al_open_video(s->video.filename.c_str());
    if (s->video.handle)
    {
      al_start_video(s->video.handle, AudioClass::songs_mixer);
      s->video.playing = true;
    }
  }
  return false;
}

bool StatusDisplayClass::funcStopVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, false);
    s->video.playing = false;
    al_close_video(s->video.handle);
    s->video.handle = nullptr;
  }
  return false;
}

bool StatusDisplayClass::funcPauseVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, false);
  }
  return false;
}

bool StatusDisplayClass::funcUnPauseVideo(StatusDisplayClass *s, unsigned char param)
{
  if (s->video.handle)
  {
    al_set_video_playing(s->video.handle, true);
  }
  return false;
}

bool StatusDisplayClass::funcStopTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_enable = false;
  return false;
}

bool StatusDisplayClass::funcStartTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_enable = true;
  return false;
}

bool StatusDisplayClass::funcResetTimer(StatusDisplayClass *s, unsigned char param)
{
  s->timer_count = 0;
  s->timer_hi = false;
  return false;
}

bool StatusDisplayClass::funcPlaySound(StatusDisplayClass *s, unsigned char param)
{
  Audio->PlaySound(s->sound);
  return false;
}

bool StatusDisplayClass::funcStopSound(StatusDisplayClass *s, unsigned char param)
{
  Audio->StopSound(s->sound);
  return false;
}

bool StatusDisplayClass::funcIfFreeplay(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->ini_general->free_play)
  { // if not free play then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotFreeplay(StatusDisplayClass *s, unsigned char param)
{
  if (Config->ini_general->free_play)
  { // if in free play then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNoCredits(StatusDisplayClass *s, unsigned char param)
{
  if (status.credits)
  { // if credits left then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfAnyCredits(StatusDisplayClass *s, unsigned char param)
{
  if (status.credits == 0)
  { // if no credits left then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::playing)
  { // if no song currently playing then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongPlaying(StatusDisplayClass *s, unsigned char param)
{
  // if ((Audio->song_play_state == song_play_state_e::playing) || PlayQueue->NumSongsTotal())
  if (Audio->song_play_state == song_play_state_e::playing)
  { // if song currently playing (or one about to) then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfAttractPlaying(StatusDisplayClass *s, unsigned char param)
{
  if ((Audio->song_play_state != song_play_state_e::playing)) // if no song currently playing then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotAttractPlaying(StatusDisplayClass *s, unsigned char param)
{
  // if ((Audio->song_play_state == song_play_state_e::playing) || PlayQueue->NumSongsTotal())
  if ((Audio->song_play_state == song_play_state_e::playing) && (status.now_playing->play_type == play_type_e::AttractMode))
  { // if song currently playing and in auto mode (or one about to) then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfFilePlaying(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::playing) return true; // nothing playing, so don't print rest of line

  if (status.now_playing->type != song_type_e::mp3) // if song currently playing isn't from a file then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotFilePlaying(StatusDisplayClass *s, unsigned char param)
{
  if ((Audio->song_play_state == song_play_state_e::playing) && (status.now_playing->type == song_type_e::mp3))
  { // if song currently playing and is from a file then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfVideoPlaying(StatusDisplayClass *s, unsigned char param)
{

  if (Audio->song_play_state != song_play_state_e::playing) return true; // nothing playing, so don't print rest of line

  if (status.now_playing->type != song_type_e::ogv) // if song currently playing isn't video then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotVideoPlaying(StatusDisplayClass *s, unsigned char param)
{
  if ((Audio->song_play_state == song_play_state_e::playing) && (status.now_playing->type == song_type_e::ogv))
  { // if song currently playing and is video then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfStreamPlaying(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::playing) return true; // nothing playing, so don't print rest of line

  if (status.now_playing->type != song_type_e::url) // if song currently playing isn't from a url link then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotStreamPlaying(StatusDisplayClass *s, unsigned char param)
{
  if ((Audio->song_play_state == song_play_state_e::playing) && (status.now_playing->type == song_type_e::url)) // if song currently playing and is from a url link then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongLoading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::loading)
  { // if no song currently loading then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongLoading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state == song_play_state_e::loading) // if song currently loading then don't print rest of line...
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongUnloading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state != song_play_state_e::unloading)
  { // if no song currently unloading then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotSongUnloading(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->song_play_state == song_play_state_e::unloading)
  { // if no song currently loading then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfAnyComingUp(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->NumSongsComingUp())
  { // if no songs coming up then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNoneComingUp(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->NumSongsComingUp())
  { // if songs coming up then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfSongComingUp(StatusDisplayClass *s, unsigned char param)
{
  bool ret { false };
  if ((PlayQueue->NumSongsComingUp()) <= StatusDisplayClass::if_song_coming_ups)
  { // if no songs (left to display) coming up then don't print rest of line...
    ret = true; //s->SkipToEndIf();
  }
  StatusDisplayClass::if_song_coming_ups++;
  return ret;
}

bool StatusDisplayClass::funcIfAttractModeMode(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->ini_attract->enable)
  { // if not in random play (attract mode) then...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotAttractModeMode(StatusDisplayClass *s, unsigned char param)
{
  if (Config->ini_attract->enable )
  { // if in random play (attract mode) then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfLoopMode(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->ini_general->loop_playqueue)
  { // if not in loop mode then...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotLoopMode(StatusDisplayClass *s, unsigned char param)
{
  if (Config->ini_general->loop_playqueue)
  { // if loop mode then don't print rest of line...
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerHi(StatusDisplayClass *s, unsigned char param)
{
  if (s->timer_hi == false)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerLo(StatusDisplayClass *s, unsigned char param)
{
  if (s->timer_hi == true)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTimerTick(StatusDisplayClass *s, unsigned char param)
{
  if (!s->timer_tick)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTitleStripMoving(StatusDisplayClass *s, unsigned char param)
{

  if (TitleStripDisplayClass::move_direction == title_strip_move_direction_e::None)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfTitleStripNotMoving(StatusDisplayClass *s, unsigned char param)
{
  // if (status.title_strips_moving)
  if (TitleStripDisplayClass::move_direction != title_strip_move_direction_e::None)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPlayQueueEmpty(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->empty)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPlayQueueEmpty(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->empty)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPlayQueueFull(StatusDisplayClass *s, unsigned char param)
{
  if (!PlayQueue->full)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPlayQueueFull(StatusDisplayClass *s, unsigned char param)
{
  if (PlayQueue->full)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfStereo(StatusDisplayClass *s, unsigned char param)
{
  if (!Audio->stereo)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotStereo(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->stereo)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfPaused(StatusDisplayClass *s, unsigned char param)
{
  if (!AudioClass::paused)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotPaused(StatusDisplayClass *s, unsigned char param)
{
  if (AudioClass::paused)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfInstantPlay(StatusDisplayClass *s, unsigned char param)
{
  if (!Config->skin_general->instant_play)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotInstantPlay(StatusDisplayClass *s, unsigned char param)
{
  if (Config->skin_general->instant_play)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfInvalidChoice(StatusDisplayClass *s, unsigned char param)
{
  if (!Engine->invalid_choice)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotInvalidChoice(StatusDisplayClass *s, unsigned char param)
{
  if (Engine->invalid_choice)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfDuplicateChoice(StatusDisplayClass *s, unsigned char param)
{
  if (!Engine->duplicate_choice)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotDuplicateChoice(StatusDisplayClass *s, unsigned char param)
{
  if (Engine->duplicate_choice)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfVisible(StatusDisplayClass *s, unsigned char param)
{
  if (s->visible == false)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotVisible(StatusDisplayClass *s, unsigned char param)
{
  if (s->visible == true)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfFlagHigh(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };
  if (Config->status_flag[flag] == false)
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfFlagLow(StatusDisplayClass *s, unsigned char param)
{
  uint32_t flag { static_cast<uint32_t>(param) };
  if (Config->status_flag[flag])
  {
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfMute(StatusDisplayClass *s, unsigned char param)
{
  if (!Audio->muted)
  { // if not mute then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfNotMute(StatusDisplayClass *s, unsigned char param)
{
  if (Audio->muted)
  { // if mute then we skip the text section (to $END_IF or end of line)
    return true; // s->SkipToEndIf();
  }
  return false;
}

bool StatusDisplayClass::funcIfButtonPressed(StatusDisplayClass *s, unsigned char param)
{
  return !Engine->IsButtonBitSet(static_cast<uint32_t>(param));
}

bool StatusDisplayClass::funcIfNotButtonPressed(StatusDisplayClass *s, unsigned char param)
{
  return Engine->IsButtonBitSet(static_cast<uint32_t>(param));
}

bool StatusDisplayClass::funcEndIf(StatusDisplayClass *s, unsigned char param)
{
  return false;
}

bool StatusDisplayClass::funcNoDraw(StatusDisplayClass *s, unsigned char param)
{
  s->no_draw = true;
  return false;
}

bool StatusDisplayClass::funcSetVisible(StatusDisplayClass *s, unsigned char param)
{
  s->visible = true;
  return false;
}

bool StatusDisplayClass::funcSetNotVisible(StatusDisplayClass *s, unsigned char param)
{
  s->visible = false;
  return false;
}

///////////////////////////////////////////////////////////////////////////////

int StatusDisplayClass::BitmapSearch
(
  const char        *path,
  const struct stat *sptr,
  int               type
)
{
  string p { path };
  if (type == FTW_F)
  { // normal file
    if (p.size() < 4) return 0;

    bool found { };
    // extract file extension and convert to lower case...
    string file_ext { p.substr( p.length() - 4 ) };
    transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

    if (file_ext == ".bmp") found = true;
    if (file_ext == ".jpg") found = true;
    if (file_ext == ".png") found = true;

    if (found)
    {
      StatusDisplayClass::static_bitmap_name.push_back(p);
    }
  }

  return 0;
}

struct else_code_t
{
  unsigned char code {};
  uint32_t param {};
  int32_t event_bit {};
};

void StatusDisplayClass::init(const dynamics2_t sze, const uint32_t emsk)
/*
  read the text file and replace any $VAR keyword strings with a 4-character
  shortcut code for fast lookup later (STATUS_VAR_START, code, code_param, if_skip).
  Also set appropriate bits in the event_mask
  depending upon which $VAR keywords are found.  Store each modified line from the text
  file into the internal "lines" vector array, for use by the real-time update function
  If $ELSE is found, insert a $END_IF and the complementary keyword code
*/
{
  ifstream inFile;
  string fl;
  string l;
  if (bitmap_directory.size())
  {
    // ftw bitmap_directory and save each image filename in the bitmap_name vector...
    // we have to push into the static bitmap_name vector, then copy this vector to our bitmap_name
    // vector unique to this status object instance...
    ftw(bitmap_directory.c_str(), BitmapSearch, 16);
  }

  dst.reserve(256);

  StatusDisplayClass::static_bitmap_name.shrink_to_fit();
  bitmap_name = StatusDisplayClass::static_bitmap_name;
  StatusDisplayClass::static_bitmap_name.clear();

  if (desc_name.size() == 0)
  {
    event_mask = 0;
    return;
  }

  if (text.font_number >= Config->fonts.size())
  {
    text.font_number = SystemFontNumber;
  }

  if (text.max_width == 0) text.max_width = size.x.val;

  inFile.open(desc_name, ios::in);
  if (!inFile.is_open())
  {
    error("Couldn't open status file '%s' for input", desc_name.c_str());
  }

  // replace any status variables ${...} with their 3-character code...

  while (getline(inFile, fl))
  {
    vector<else_code_t> else_code {};

    fl.erase(std::remove(fl.begin(), fl.end(), 13), fl.end()); // remove CR (for non-linux text file)
    fl.erase(std::remove(fl.begin(), fl.end(), 10), fl.end()); // remove LF (for non-linux text file)

    if (fl.back() == '\\') // if this line ends with '\', then it's concatenated with the next, so
    {
      fl.pop_back(); // remove the control character
      l += fl; // add it to the end of the current (un-parsed) line
      continue;
    }
    else // parse the current line...
    {
      l += fl; // add currently read line to the end of any previous (un-parsed) line(s)
    
      for (auto pos = 0; pos < l.length(); ++pos) // for each character in the line...
      {
        const status_vars_t *s;
        for (auto sv = 0; sv < status_vars.size(); ++sv) // see if we have a reserved word...
        {
          s = &status_vars[sv];
          if (l.compare(pos, s->name.length(), s->name) == 0) // ...yep
          {
            if (s->else_code != STATUS_VAR_NULL) // save the status var else_code etc. for this code in case we encounter an $ELSE in the future...
            {
              else_code.push_back( {s->else_code, s->code_param, s->event_bit} );
            }

            if (s->code == STATUS_VAR_END_IF) // if we have an end_if, then remove last else_code from else_code stack which will correspond to previous IF
            {
              if (else_code.size())
              {
                else_code.pop_back();
              }
            }
            
            if (s->code == STATUS_VAR_ELSE) // replace $ELSE keyword with $END_IF sequence and popped complimentary sequence...
            {
              if (else_code.size())
              {
                {
                  // get else code from else stack...
                  // const status_vars_t *var { &status_vars.at(static_cast<uint32_t>(else_code.back().code - STATUS_VAR_OFFSET)) };

                  // construct sequence for $END_IF and complimentary code...
                  string c { static_cast<char>(STATUS_VAR_START) };
                  c += static_cast<char>(STATUS_VAR_END_IF);
                  c += static_cast<char>(STATUS_CODE_PARAM_NONE);
                  c += static_cast<char>(STATUS_IF_SKIP_UNDEFINED);
                  c += static_cast<char>(STATUS_VAR_START);
                  c += else_code.back().code;
                  c += else_code.back().param;
                  c += STATUS_IF_SKIP_UNDEFINED;

                  l.replace(pos, s->name.length(), c);
                  event_mask |= else_code.back().event_bit;

                  // else_code.pop_back();
                }
              }
              else // remove $ELSE string
              {
                l.erase(pos, s->name.length());
              }
            }
            else // replace keyword with its code sequence (...
            {
              string c { static_cast<char>(STATUS_VAR_START) };
              c += static_cast<char>(s->code);
              c += static_cast<char>(s->code_param);
              c += static_cast<char>(STATUS_IF_SKIP_UNDEFINED); // if_skip ... to be calculated later
              l.replace(pos, s->name.length(), c);
              event_mask |= s->event_bit;
              if ((s->code >= STATUS_VAR_SET_GPIO_00_HI) && (s->code <= STATUS_VAR_SET_GPIO_27_LO))
              {
                Gpio->ConfigurePinAsOutput((s->code - STATUS_VAR_SET_GPIO_00_HI) / 2);
              }
            }
            break;
          }
        }
      }

      lines.push_back( {l, 0, 0, nullptr} );
      
      l.clear();
    }
  }

  inFile.close();

  CalculateIfSkips(); // ... fill in all the currently undefined if_skip values in all the lines
  
  if (text.mode > 0) event_mask |= StatusEvent_ScrollText;

  DisplayBaseClass::init(size, event_mask); // use size picked up from config file, and event_mask derived here in init()
  update(StatusEvent_init);
  event_mask &= ~StatusEvent_InitEmpty; // no longer need the init event mask bit

}

void StatusDisplayClass::CalculateIfSkips(void)
/*
  scan the lines and fill in the (undefined) if_skip values...
  Detects $IF vars and count the number of charcters in the string to the paired $END_IF,
  then puts this count value into the $IF var if_skip byte.  Using a vector for if_skip
  values allows nested IF/END_IF conditions.
*/
{

  for (auto & l: lines)
  { // each status line...
    line = &l.str;
    vector<uint32_t> if_skip_pos { };
    uint32_t end_level { 0 };

    line_pos = 0;
    while (line_pos < line->size())
    { // jump to the next $END_IF or end of line
      uint8_t c = static_cast<uint8_t>(line->at(line_pos++));
      if (c == STATUS_VAR_START) // start of VAR code sequence
      {
        c = static_cast<uint8_t>(line->at(line_pos++)); // VAR code
        line_pos++; // skip second control character (code_param)
        line_pos++; // skip third control character (if_skip)
        if (c != STATUS_VAR_END_IF)
        { // if not an $END_IF then we increase the nested end_if level
          if (status_vars[c - STATUS_VAR_OFFSET].is_if)
          {
            if_skip_pos.push_back(line_pos - 1);
            end_level++;
          }
        }
        else
        { // it is an $END_IF, but we only terminate if it corresponds to our level (1)
          if (if_skip_pos.size())
          {
            uint32_t skip { if_skip_pos.back() };
            if_skip_pos.pop_back();
            line->at(skip) = static_cast<uint8_t>(line_pos - skip - 1); // we need to skip this many characters if not executing this $IF statement
            end_level--;
          }
        }
      }
    }

    if (if_skip_pos.size()) // check as there may be a missing ${END_IF} at the end of the line...
    {
      uint32_t skip { if_skip_pos.back() };
      if_skip_pos.pop_back();
      line->at(skip) = static_cast<uint8_t>(line_pos - skip - 1); // we need to skip this many characters if not executing this $IF statement
    }
  }
}

bool StatusDisplayClass::update
/*
  Parse each line in the lines vector...normal characters get printed
  out, but embedded $VAR characters get their associated function called
  to do their specific task...
*/
(
  const uint32_t event
)
{
  if (DisplayBaseClass::update(event) == false) return false;

  ALLEGRO_BITMAP *bm {};
  // uint32_t y { };
  bool status_file_output { false };
  bool scroll_update { false };
  ofstream outFile;

  // Display->redraw = true;

  al_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  no_draw = false;

  timer_tick = false;

  uint32_t evnt {event_mask & event};

  if (evnt & (StatusEvent_TimerChange | StatusEvent_ScrollText))
  {
    // timer_tick = false;
    if (timer_enable)
    {
      if (++timer_count == timer_tick_period.ticks)
      {
        timer_tick = true;
        timer_count = 0;
        timer_hi = !timer_hi;
        if (timer_oneshot)
        {
          timer_enable = false;
        }
      }
    }
  }

  if (evnt & StatusEvent_ScrollText)
  {
    if (timer_tick)
    {
      if (text.mode > 0) // scroll mode...
      {
        for (auto & l: lines)
        {
          if (l.bitmap && (l.width > text.max_width)) // ... update scroll offset if too wide...
          {
            l.offset -= text.mode;
            if ((l.offset + l.width) < 0)
            {
              l.offset = text.max_width;
            }
          }
          else
          {
            l.offset = 0;
          }
        }
      }
    }
  }

  if ((evnt & ~StatusEvent_ScrollText)) // other event bits are set, so we need to re-build the bitmap...
  {
    if (output_filename.size())
    {
      outFile.open(output_filename, ios::out | ios::trunc);
      if (outFile.is_open())
      {
        status_file_output = true;
      }
      else
      {
        log_file << WARNING << "Couldn't open file '" << output_filename << "' for output" << endl;
      }
    }

    for (auto & l: lines)
    { // each status line...
      char c;
      line = &l.str;
      line_pos = 0;

      dst.clear();

      while (1) // search for control codes...
      {
        if (line_pos >= line->size()) break;

        c = line->at(line_pos++);

        if (static_cast<uint8_t>(c) == STATUS_VAR_START) // start of control code sequence
        {
          var_str = nullptr;
 
         uint8_t var_code = static_cast<uint8_t>(line->at(line_pos++));
          uint8_t var_code_param = static_cast<uint8_t>(line->at(line_pos++));
          uint8_t var_if_skip = static_cast<uint8_t>(line->at(line_pos++));

          const status_vars_t *var { &status_vars[static_cast<uint32_t>(var_code - STATUS_VAR_OFFSET)] };

// if (var_code_param != STATUS_CODE_PARAM_NONE) cout << "var->func(" << static_cast<uint32_t>(var_code_param) << ")" << endl;

          if (var->func(this, var_code_param) == true)
          {
            line_pos += var_if_skip;
          }

          if (var_str != nullptr)
          {
            dst += *var_str;
          }
        }
        else
        { // normal character
          dst += c;
        }

      }

      l.width = Display->RenderText(l.bitmap, text, dst);

      if (status_file_output)
      {
        outFile << dst << endl;
      }

    }

    if (artwork_bitmap.handle)
    {
      al_draw_scaled_bitmap(artwork_bitmap.handle, 0, 0, al_get_bitmap_width(artwork_bitmap.handle), al_get_bitmap_height(artwork_bitmap.handle), 0, 0, size.x.val, size.y.val, 0);
    }

    if (draw_bitmap)
    {
      if (bitmap_name.size())
      // bitmap directory specified and has bitmaps in it, so use these instead
      {
        if (bm)
        {
          al_destroy_bitmap(bm);
        }

        bm = al_load_bitmap(bitmap_name[bitmap_idx].c_str());

        if (bm)
        {
          al_draw_scaled_bitmap(bm, 0, 0, al_get_bitmap_width(bm), al_get_bitmap_height(bm), 0, 0, size.x.val, size.y.val, 0);
        }
      }
      else
      {
        bm = bitmap_list[bitmap_idx];
        if (bm)
        {
          al_draw_scaled_bitmap(bm, 0, 0, al_get_bitmap_width(bm), al_get_bitmap_height(bm), 0, 0, size.x.val, size.y.val, 0);
        }
      }
    }

    if (draw_video)
    {

      video_t *status_video;
      bool loop {};

      // If a Video has been defined in the status object, then use it, otherwise use the song video...

      if (video.filename.size())
      {
        status_video = &video;
        loop = loop_video;
      }
      else
      {
        status_video = &Engine->song_video;
      }

      if (loop)
      {
        if (al_is_video_playing(status_video->handle) == false) // restart (loop) video
        {
          al_seek_video(status_video->handle, 0);
          al_set_video_playing(status_video->handle, true);
        }
      }

      if (status_video->playing)
      {
        if (status_video->handle != nullptr)
        {
          status_video->bm_handle = al_get_video_frame(status_video->handle);
          if (status_video->bm_handle != nullptr)
          {
            al_draw_scaled_bitmap(status_video->bm_handle, 0, 0, al_get_bitmap_width(status_video->bm_handle), al_get_bitmap_height(status_video->bm_handle), 0, 0, size.x.val, size.y.val, 0);
          }
        }
      }
    }

    if (status_file_output)
    {
      outFile.close();
    }
  }

  // draw text lines after everything else...
  int32_t h { Config->fonts[text.font_number].size };
  int32_t y { 0 };

  h += line_spacing;
  int32_t align_width { al_get_bitmap_width(bitmap) };

  for (auto & l: lines) // each status line...
  {
    Display->DrawText(l.bitmap, bitmap, text, align_width, l.offset, y);
    y += h;
  }

  return true;
}

void StatusDisplayClass::draw(void)
{
  al_set_target_bitmap(Display->jukebox);
  DisplayBaseClass::draw();
}
