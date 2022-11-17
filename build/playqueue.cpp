#include "fruitbox.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Play Queues...

uint32_t PlayQueueClass::NumSongsTotal(void)
{
  return queue.size();
}

uint32_t PlayQueueClass::NumSongsComingUp(void)
{
  uint32_t n { 0 };
  mtx.lock();
  if (queue.size())
  { // exclude top song (which is playing/about to be played)
    n = queue.size() - 1;
  }
  mtx.unlock();
  return n;
}

string PlayQueueClass::NumSongsComingUpStr(void)
{
  stringstream s {};
  uint32_t n { NumSongsComingUp() };
  s << n;
  return s.str();
}

string PlayQueueClass::TotalTimeComingUp(void)
{
  uint32_t t { total_time };

  mtx.lock();
  if (queue.size())
  {
    song_t *top_song = queue.at(0);
    t -= top_song->length;
  }
  mtx.unlock();
  return StrHrMinSec(t);
}

string PlayQueueClass::RemainingSpaceStr(void)
{
  stringstream s {};
  uint32_t n { Config->ini_general->max_playqueue_length - NumSongsComingUp() - 1}; // -1 as max_playqueue_length includes now playing song
  s << n;
  return s.str();
}

// FindSong  : return whether the song is already in the queue or not.  Used
// to see if a song is already in the queue if no_duplicates is set.
bool PlayQueueClass::FindSong(song_t *song)
{
  song_t *songq;
  uint32_t cntr;
  uint32_t occ { static_cast<uint32_t>(queue.size()) };
  if ((song->title.compare(status.now_playing->title) == 0) && (song->artist.compare(status.now_playing->artist) == 0)) return 1; // song is currently playing
  if (occ == 0) return false; //nothing in the queue
  // Loop through the queue and look for the song
  for (cntr = 0; cntr < occ; ++cntr)
  {
    songq = queue.at(cntr);
    if ((song->title.compare(songq->title) == 0) && (song->artist.compare(songq->artist) == 0))
    {
      return true; // song is currently playing
    }
  }
  return false;
}

// QuerySong : return the song information for the entry in the queue "from_top" entries from the top
// i.e. if from_top = 0, this returns the next entry in the queue
// i.e. if from_top = 1, this returns the second entry in the queue

song_t * PlayQueueClass::QuerySong(const int32_t from_top)
{
  song_t *song;
  uint32_t occ { static_cast<uint32_t>(queue.size()) };
  if (occ == 0) return nullptr; // nothing in queue
  if (from_top >= occ) return nullptr; // not enough entries in the queue
  song = queue.at(from_top);
  string file_ext { song->filename.substr( song->filename.length() - 4 ) };
  transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

  song->type = song_type_e::unknown;
  if (file_ext == ".mp3") song->type = song_type_e::mp3;
  if (file_ext == ".ogv") song->type = song_type_e::ogv;
    // log_file << "song->filename " << song->filename << endl;
  if (song->filename.find(URLPrefix) != string::npos) // string contains "http"
  {
    // log_file << "SONG IS URL!!!" << endl;
    song->type = song_type_e::url;
  }

  // log_file << endl << "Query " << from_top << "..." << endl;
  // log_file << "title = " << song->title << endl;
  // log_file << "artist = " << song->artist << endl;
  // log_file << "album artist = " << song->albumArtist << endl;
  // log_file << "track = " << song->trackNumberStr << endl << endl;
  return song;
}

void PlayQueueClass::AddToHistory(const int32_t from_top)
{
  if (Config->ini_general->song_history_depth == 0) return;
  
  mtx.lock();
  uint32_t occ { static_cast<uint32_t>(queue.size()) };
  if (occ)
  {
    song_play_history.push_back(queue.at(from_top));
    if (song_play_history.size() > Config->ini_general->song_history_depth)
    // remove oldest entry if history size exceeds user specified...
    {
      song_play_history.pop_front();
    }
  }
  mtx.unlock();
}

bool PlayQueueClass::Add(song_t *song, play_type_e play_type)
// add song(s) to the end of the queue
// returns true if duplicate song selected
{
  bool credit_mode { false };
  if ((Config->ini_general->free_play == false) && (play_type == play_type_e::CreditPlay))
  {
    credit_mode = true;
  }

  mtx.lock();
  if (queue.size() < Config->ini_general->max_playqueue_length) // room in play queue
  {
    if (credit_mode) // check if we have credit...
    {
      if (status.credits < Config->ini_general->credits_per_song) // none left!
      {
        mtx.unlock();
        return false;
      }
      // use up a plays' worth of credits...
      status.credits -= Config->ini_general->credits_per_song;
      status_event |= StatusEvent_CreditsChange;
    }
    
    if (Config->skin_general->no_duplicates == true) // check for a duplicated song (selected song is already in the queue or currently playing)
    {
      if (FindSong(song) == true) // song is already in the queue (or currently playing)
      {
        if (credit_mode && (Config->skin_general->duplicates_use_credits == false))
        {
          status.credits += Config->ini_general->credits_per_song; // restore credit from decrement above as this song is duplicated, so we don't charge the user for it
          status_event &= ~StatusEvent_CreditsChange; // credits haven't changed after all
        }
        // return early so we don't add the song to the queue...
        mtx.unlock();
        return true;
      }
    }
    // add song to queue...
    song->play_type = play_type;
    queue.push_back(song);
    total_time += song->length;
    empty = false;
    if (queue.size() >= Config->ini_general->max_playqueue_length) // queue full
    {
      full = true;
    }
    occupancy = static_cast<float>(queue.size()) / static_cast<float>(Config->ini_general->max_playqueue_length);
    status_event |= StatusEvent_PlayQueueChange;
  }
  mtx.unlock();
  
  return false;
}

void PlayQueueClass::Remove(void)
{ // remove last song from the beginning of the queue
  mtx.lock(); // can be called by main thread or audio thread
  if (queue.size())
  {
    queue.pop_front();
    total_time -= status.now_playing->length;
    full = false;
    if (queue.size() == 0) empty = true;
    occupancy = static_cast<float>(queue.size()) / static_cast<float>(Config->ini_general->max_playqueue_length);
    status_event |= StatusEvent_PlayQueueChange;
  }
  mtx.unlock();
}

void PlayQueueClass::Clear(void)
{
  song_t *song {};
  if (queue.size() > 1) // remove all but first element (which is the currently playing song, if one)
  {
    mtx.lock();
    queue.erase(queue.begin()+1, queue.end());
    empty = true;
    full = false;
    song_t *song = queue.at(0);
    total_time = song->length;
    occupancy = static_cast<float>(queue.size()) / static_cast<float>(Config->ini_general->max_playqueue_length);
    mtx.unlock();
    status_event |= StatusEvent_PlayQueueChange;
  }
}

void PlayQueueClass::Load(const string filename)
{
  if (filename.size())
  {
    song_t *song;
    string line;
    string song_filename;
    ifstream playlistFile;
    playlistFile.open(filename.c_str(), ios::in);
    if (!playlistFile.is_open())
    {
      log_file << WARNING << "Couldn't open ''" << filename.c_str() << "'" << endl;
    }
    else
    {
      log_file << "Loading playlist '" << filename << "'..." << endl;
      while (getline(playlistFile, line))
      // read line (containing filename)
      {
        if (line.empty()) continue;
        line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
        if (line.at(0) == '#') continue; // comment line
        istringstream ss { line };
        if (!getline(ss >> std::ws, song_filename)) continue;
        song_filename.erase(song_filename.find_last_not_of(" \t")+1);// remove trailing whitespace
        song = Database->GetSong(song_filename);
        // search database for filename
        if (song != nullptr)
        {
          Add(song, play_type_e::FreePlay); // add song to queue
        }
      }
      playlistFile.close();
      status.coming_up_num_songs_str = NumSongsComingUpStr();
      status.coming_up_total_length_str = TotalTimeComingUp();
      status.playqueue_space_str = RemainingSpaceStr();
    }
  }
}

void PlayQueueClass::Save(const string filename)
{
  if (filename.size())
  {
    ofstream playlistFile;
    playlistFile.open(filename.c_str(), ios::out);
    if (!playlistFile.is_open())
    {
      log_file << WARNING << "Couldn't create ''" << filename.c_str() << "'" << endl;
    }
    else
    {
      log_file << "Saving playlist '" << filename << "'..." << endl;
      playlistFile << "# " << FRUITBOX_VERSION << " playlist file " << endl << endl;
      for (auto i : queue)
      {
        playlistFile << i->filename << endl;
      }
      playlistFile.close();
    }
  }
}

