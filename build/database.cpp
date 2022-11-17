#include "fruitbox.hpp"
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>

// #define DEBUG_LOG_SONG_SORTING

using namespace std;

// fruitbox database...
//
// The database consists of a sorted vector of song_t structures
// The vector is created from multiple database files (one in each directory).

// If the database file exists, it is read into a vector of song_t and then sorted (by whatever
// is specified in the config file).  Alongside the songs vector, a 2d vector of songs is created
// (song_lookup) each time fruitbox is run. The two dimensions correspond to the title_strip number and
// song entry within each title_strip. Each song is represented by a song_t* which points to a song_t in
// the database songs vector.
//
// Songs are retrieved by the GetSong(title_strip, entry) or GetSong() methods

vector<song_t> DatabaseClass::database { };
string DatabaseClass::database_filename { };
string DatabaseClass::database_filepath { };
fstream DatabaseClass::dbFile { };
deque<string> DatabaseClass::song_info;

bool DatabaseClass::db_out_of_date { false };
bool DatabaseClass::create_db_file { false };
DialogListClass * DatabaseClass::ListDialog {};
constexpr int  search_depth     { 16 };
constexpr char dbFile_delimiter { '|' };
constexpr char dbFile_comment   { '#' };

/////////////////////////////////////////////////////////////////////////////////////////////////////

#define SelectSortFunction(func, name, sort_ascend, sort_descend, descend) \
log_file << name; \
if (descend) \
{ \
  log_file << " (descending)..." << endl; \
  func = sort_descend; \
} \
else \
{ \
  log_file << " ..." << endl; \
  func = sort_ascend; \
}

DatabaseClass::DatabaseClass(void)
{
  number_of_songs = 0;
  
  DatabaseClass::ListDialog = new DialogListClass("");
  DatabaseClass::ListDialog->DetachButtons();  // remove default buttons
  DatabaseClass::ListDialog->show_on_draw = true;
 
  // read / create all the fruitbox.db files in the MusicPath(s) and their sub-directories into the database vector...
  vector<string> *v { &Config->skin_general->music_path }; // use command line or skin music paths by default

  if ((command_line_music_path == false) && (v->size() == 0) && (ini_file_music_path == true)) // use ini music paths if command line music paths not specified and no music paths in skin cfg
  {
    v = &Config->ini_general->music_path;
  }

  for (auto &i : *v) // for each music path specified
  {
    // cout << "music path = " << i << endl;
    ftw(i.c_str(), Build, search_depth);
  }

  DatabaseClass::ReadFile(); // read the very last database file into database vector

  DatabaseClass::database.shrink_to_fit(); // free unused capacity

  number_of_songs = DatabaseClass::database.size();
  log_file << "  " << number_of_songs << " songs found" << endl;

  if (number_of_songs == 0)
  {
    vector<string> message;
    message.push_back("No songs found.");
    message.push_back("");
    message.push_back("Please check MusicPath(s) in fruitbox.ini,");
    message.push_back("--music-path command line option");
    message.push_back("or the skin config file");
    error(message);
  }

  // sort the database...
  #ifdef DEBUG_LOG_SONG_SORTING
    for (auto &s : DatabaseClass::database) // list of pre-sorted songs for debug
    {
      log_file << "  " << s.title << " " << s.artist << " " << s.year << endl;
    }
    log_file << endl;
  #endif

  ProgressBar->Draw("Sorting music", 60);

  for (auto &song_sort : Config->skin_general->sort_songs_by)
  {
    log_file << "  Sorting songs by ";
    static bool (*sort_func)(const song_t &song_a, const song_t &song_b);
    bool descending = song_sort.descending;

    // choose sort method...
    switch (song_sort.by)
    {
      case sort_songs_by_e::Title :
        SelectSortFunction(sort_func, "Title", SortByTitle, SortByTitleDescending, descending);
        break;        

      case sort_songs_by_e::Artist :
        if (Config->ini_general->ignore_artist_prefix_the)
        {
          SelectSortFunction(sort_func, "Artist", SortByArtistIgnorePrefixThe, SortByArtistIgnorePrefixTheDescending, descending);
        }
        else
        {
          SelectSortFunction(sort_func, "Artist", SortByArtist, SortByArtistDescending, descending);
        }
        break;

      case sort_songs_by_e::Album :
        SelectSortFunction(sort_func, "Album", SortByAlbum, SortByAlbumDescending, descending);
        break;

      case sort_songs_by_e::AlbumArtist :
        SelectSortFunction(sort_func, "Album Artist", SortByAlbumArtist, SortByAlbumArtistDescending, descending);
        break;

      case sort_songs_by_e::Year :
        SelectSortFunction(sort_func, "Year", SortByYear, SortByYearDescending, descending);
        break;

      case sort_songs_by_e::Genre :
        SelectSortFunction(sort_func, "Genre", SortByGenre, SortByGenreDescending, descending);
        break;

      case sort_songs_by_e::TrackNumber :
        SelectSortFunction(sort_func, "Track Number", SortByTrackNumber, SortByTrackNumberDescending, descending);
        break;

      case sort_songs_by_e::Publisher :
        SelectSortFunction(sort_func, "Publisher", SortByPublisher, SortByPublisherDescending, descending);
        break;

      case sort_songs_by_e::ISRC :
        SelectSortFunction(sort_func, "ISRC", SortByISRC, SortByISRCDescending, descending);
        break;

      case sort_songs_by_e::Custom :
        SelectSortFunction(sort_func, "Custom MP3 tag", SortByCustom, SortByCustomDescending, descending);
        break;

      case sort_songs_by_e::Random :
        sort_func = nullptr;
        log_file << "Random..." << endl;
        std::random_shuffle(DatabaseClass::database.begin(), DatabaseClass::database.end());
        break;

      case sort_songs_by_e::Unsorted :
        sort_func = nullptr;
        log_file << "database order (Unsorted)" << endl;
        break;

    }

    // do the sort...
    if (sort_func != nullptr) {
      std::stable_sort(DatabaseClass::database.begin(), DatabaseClass::database.end(), sort_func);
      #ifdef DEBUG_LOG_SONG_SORTING
        for (auto &s : DatabaseClass::database) // list of sorted songs for debug
        {
          log_file << "  " << s.title << " " << s.artist << " " << s.year << endl;
        }
        log_file << endl;
      #endif
    }
  }

  // construct song title_strips (depends upon Config->songs_per_title_strip and Config->pair_songs)
  status.num_songs_str = to_string(number_of_songs);

  ProgressBar->Draw("Building song title strips", 70);
  log_file << "Building song Title Strips..." << endl;
  BuildTitleStrips();

  delete DatabaseClass::ListDialog;
}

void DatabaseClass::ReadFile(void)
{
  if (DatabaseClass::dbFile.is_open())
  {
    DatabaseClass::dbFile.close(); // close (from previous directory search)
  }
  
  DatabaseClass::dbFile.open(DatabaseClass::database_filename, ios::in);
  if (!DatabaseClass::dbFile.is_open()) return; // open failed for some reason

  log_file << "  Reading database file '" << DatabaseClass::database_filename << "'" << endl;
  
  // read the songs from the file...as robust as possible
  song_t song;
  string line;
  uint32_t dbFile_line_number { 0 };
  
  while (getline(DatabaseClass::dbFile, line))
  {
    dbFile_line_number++;
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.at(0) == dbFile_comment) continue; // comment line
    istringstream ss { line };
    // if (line.find(dbFile_delimiter) == string::npos)
    // { // no delimiter, so not a valid song entry
      // getline(ss >> std::ws, DatabaseClass::music_path, dbFile_comment);
      // DatabaseClass::music_path.erase(DatabaseClass::music_path.find_last_not_of(" \t")+1);// remove trailing whitespace
      // continue;
    // }
    // else song entry ...
    string intstr;
    if (!getline(ss >> std::ws, song.filename, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.title, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.artist, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.album, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.albumArtist, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.year, dbFile_delimiter)) goto bad_line;
    if (!getline(ss >> std::ws, song.trackNumberStr, dbFile_delimiter)) goto bad_line;
    // if (!getline(ss, intstr, dbFile_delimiter)) goto bad_line;
    try { song.trackNumber = static_cast<uint32_t>(stoi(song.trackNumberStr)); }
    catch (const std::invalid_argument &err) { goto bad_line; }
    catch (const std::out_of_range &err) { goto bad_line; }

    if (!getline(ss, intstr, dbFile_delimiter)) goto bad_line;

    try { song.length = static_cast<uint32_t>(stoi(intstr)); }
    catch (const std::invalid_argument &err) { song.length = 0; }
    catch (const std::out_of_range &err) { song.length = 0; }
    song.lengthStr = StrMinSec(song.length);

    song.publisher.clear();
    song.isrc.clear();
    song.custom_tag.clear();
    song.strip_bg = Config->skin_general->default_title_strip_bkgnd.bm;

    // publisher, IRSC and custom (V1.4 onwards, so if they don't exist we are probably loading a pre V1.4 database, so don't throw a wobbly)
    if (getline(ss >> std::ws, song.publisher, dbFile_delimiter))
    {
      if (getline(ss >> std::ws, song.isrc, dbFile_delimiter))
      {
        if (getline(ss >> std::ws, song.custom_tag, dbFile_delimiter))
        {
          if (getline(ss >> std::ws, song.genre, dbFile_delimiter))
          {
            song.strip_bg = DatabaseClass::GenreStrToTitleStripBM(song.genre);
          }
        }
      }
    }

    // add the current database file path to the song.filename (if it's not a URL)...
    if (song.filename.find(URLPrefix) == string::npos) // string doesn't contain "http"
    {
      song.filename = DatabaseClass::database_filepath + FILE_SEPARATOR + song.filename;
    }

    // ...and store the song in database
    DatabaseClass::database.push_back(song);
    continue;

    bad_line:
    log_file << endl << WARNING << "Badly formatted song entry ('" << DatabaseClass::database_filename << "', line " << dbFile_line_number << ")" << endl;
  }

  DatabaseClass::dbFile.close();
}

///////////////////////////////////////////////////////////////////////////////
// use file tree walker to search for database files and music files, and store them in the database files...

int DatabaseClass::Build
(
  const char        *path,
  const struct stat *sptr,
  int               type
)
{
  string p { path };
  static uint32_t current_dir_song_count { 0 }; // temp count for dialog status

  if (type == FTW_D) // directory
  { 
    current_dir_song_count = 0;
    DatabaseClass::ReadFile(); // read the database file from any previous FTW_D directory into the database vector

    DatabaseClass::db_out_of_date = false;
    DatabaseClass::create_db_file = true;
    // database file is the one in the current directory...
    DatabaseClass::database_filepath = p;
    DatabaseClass::database_filename = p + FILE_SEPARATOR + defaultDatabaseFilename;
    
    // check database file exists in the current directory...
    DatabaseClass::dbFile.open(DatabaseClass::database_filename, ios::in);
    if (DatabaseClass::dbFile.is_open()) // yes, fruitbox.db exists in this directory, so check its timestamp against directory timestamp...
    {
      string title { "Checking music database " + DatabaseClass::database_filename };
      log_file << title << endl;
      ProgressBar->Draw(title, 50);

      DatabaseClass::dbFile.close();
      struct stat dir_stat, db_stat;
      if (stat(path, &dir_stat) == 0) // directory date
      {
        if (force_db_refresh) // always update database
        {
          DatabaseClass::db_out_of_date = true;
          log_file << "  " << NOTE << "Forcing update of " << DatabaseClass::database_filename << endl;
        }
        else // check if database needs updating
        {
          if (stat(DatabaseClass::database_filename.c_str(), &db_stat) == 0)  // database file date
          {
            if (dir_stat.st_mtime <= db_stat.st_mtime) // directory has been modified before (or same time as) database file...
            {
              DatabaseClass::create_db_file = false; // we don't need to create a local database if it exists and it's newer than the directory
            }
            else // directory modified after database file, so directory (contents) now out of date...
            {
              DatabaseClass::db_out_of_date = true;
              if (no_db_refresh)
              {
                DatabaseClass::create_db_file = false; // we don't re-create a local database if it's out of date but the user has specified no update
                log_file << "  " << NOTE << DatabaseClass::database_filename << " out of date, but refresh disabled with " << commandLineArgNoDbRefresh << endl;
              }
            }
          }
        }
      }
    }
  }

  if (type == FTW_F) // normal file, so add it to the currently open local database file
  {     
    if (DatabaseClass::create_db_file == false) return 0; // no need to refresh database file

    // ignore files beginning with "._" (as they are Apple turd files)...
    // cout << "Filename = " << p << endl;
    // if (p.size() >= 2)
    // {
      // if (p.compare(0, 2, "._") == 0) return 0;
    // }
    
    if (p.size() < 4) return 0;

    vector<song_t> song;

    // extract file extension and convert to lower case...
    string file_ext { p.substr( p.length() - 4 ) };
    transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);

    if (file_ext == ".mp3") Audio->GetID3Metadata((const char *)path, song);
    if (file_ext == ".ogv") Audio->GetOGVMetadata((const char *)path, song);
    if (file_ext == ".m3u") Audio->GetM3UMetadata((const char *)path, song); // could be more than one song
    if (file_ext == ".pls") Audio->GetPLSMetadata((const char *)path, song); // could be more than one song

    for (auto &s : song)
    {
      if (s.title.size())
      {
        if (s.type != song_type_e::url) // for url files, filename is extracted from inside m3u file (http address)
        {
          // exclude the filepath for each song entry (as the path is where the fruitbox.db file is, so is known)
          s.filename = p.substr(p.find_last_of(FILE_SEPARATOR) + 1);

          // ignore files beginning with "._" (as they are Apple turd files)...
          if (s.filename.size() >= 2)
          {
            if ((s.filename[0] == '.') && (s.filename[1] == '_')) continue;
            // if (s.filename.compare(0, 2, "._") == 0) continue;
          }
        }

        // write song to database file...
        // if first song (in this sub directory), then create a new database file...
        if (!DatabaseClass::dbFile.is_open()) // not open, so create new one and add header
        {
          // create a new database file in the current ftw directory...
          DatabaseClass::dbFile.open(DatabaseClass::database_filename, ios::out);
          if (!DatabaseClass::dbFile.is_open())
          {
            error("Couldn't create '%s'", DatabaseClass::database_filename.c_str());
          }

          // log file and on screen list dialog title...
          string menu_title {};
          if (DatabaseClass::db_out_of_date)
          {
            menu_title = "  Refreshing ";
          }
          else
          {
            menu_title = "  Creating ";
          }
          log_file << menu_title << "database file '" << DatabaseClass::database_filename << "'" << endl;
          DatabaseClass::ListDialog->SetTitle(menu_title + DatabaseClass::database_filename);

          // write database header
          DatabaseClass::dbFile << "# " << FRUITBOX_VERSION << " database file" << endl;
          DatabaseClass::dbFile << "# song entry format is Filename" << dbFile_delimiter << "SongTitle" << dbFile_delimiter << "Artist" << dbFile_delimiter << "AlbumTitle" << dbFile_delimiter;
          DatabaseClass::dbFile << "AlbumArtist" << dbFile_delimiter << "Year" << dbFile_delimiter << "TrackNumber" << dbFile_delimiter << "LengthInSeconds" << dbFile_delimiter;
          DatabaseClass::dbFile << "Publisher" << dbFile_delimiter << "ISRC" << dbFile_delimiter << "CustomTag[" << Config->ini_general->custom_mp3_tag << "]" << dbFile_delimiter;
          DatabaseClass::dbFile << "Genre" << endl;
        }

        DatabaseClass::dbFile << s.filename << dbFile_delimiter;
        DatabaseClass::dbFile << s.title << dbFile_delimiter;
        DatabaseClass::dbFile << s.artist << dbFile_delimiter;
        DatabaseClass::dbFile << s.album << dbFile_delimiter;
        DatabaseClass::dbFile << s.albumArtist << dbFile_delimiter;
        DatabaseClass::dbFile << s.year << dbFile_delimiter;
        DatabaseClass::dbFile << s.trackNumber << dbFile_delimiter;
        DatabaseClass::dbFile << s.length << dbFile_delimiter;
        DatabaseClass::dbFile << s.publisher << dbFile_delimiter;
        DatabaseClass::dbFile << s.isrc << dbFile_delimiter;
        DatabaseClass::dbFile << s.custom_tag << dbFile_delimiter;
        DatabaseClass::dbFile << s.genre << endl;

        ++current_dir_song_count;

        if (DatabaseClass::song_info.size() == 8) 
        // don't let visible list exceed 8; when it does, remove the first and shift all the others up one...
        {
          rotate(song_info.begin(), song_info.begin() + 1, song_info.end());
          DatabaseClass::song_info.pop_back(); // remove this (it was the first,so we no longer need it)
        }
        DatabaseClass::song_info.push_back( s.title + " (" + s.artist + ")" );
        string status { " ... " + to_string(current_dir_song_count) + " / " + to_string(DatabaseClass::database.size() + current_dir_song_count) + " songs" };
        DatabaseClass::ListDialog->SetFooter(status);
        DatabaseClass::ListDialog->redraw = true;
        DatabaseClass::ListDialog->Draw(DatabaseClass::song_info);
      }
    }
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////

void DatabaseClass::DumpTitleStrips(void)
{
  uint32_t display_page { UINT_MAX };
  stringstream ss;

  log_file << "Dumping Title Strips..." << endl;
  dump_title_strips = true;
  
  for (uint32_t s = 0; s < number_of_title_strips;) // for every title strip in the database...
  {
    if ((s % Config->skin_general->num_title_strips) == 0) // first song each display page
    {
      ++display_page;
      TitleStripDisplayClass::title_strip_offset = 0; // first title_strip in display is zero
    }
    dump_title_strip_filename.clear();
    for (auto &i : Config->skin_display_object) // for all display objects...
    {
      if (dynamic_cast<TitleStripDisplayClass*>(i) != nullptr) // if obj is a title strip...
      {
        TitleStripDisplayClass* t { dynamic_cast<TitleStripDisplayClass*>(i) };
        // start a new file name ...
        ss.str(string()); // clear ss string
        ss << setfill('0') << setw(5) << display_page;
        dump_title_strip_filename = "title_strip_" + ss.str();
        t->ConstructTitleStrip();
        dump_title_strip_filename += ".png";
        t->SaveTitleStrip(dump_title_strip_filename);
        TitleStripDisplayClass::title_strip_offset++; // next title strip on current display page
        ++s; // next title strip in database
      }
    }
    TitleStripDisplayClass::start_title_strip += Config->skin_general->num_title_strips;
  }
}


ALLEGRO_BITMAP* DatabaseClass::GenreStrToTitleStripBM
(
  string &genre
)
{
  // search genre_bkgnd vector for match with extracted genre...
  // extracted genre string may contain more than one genre, so we just try to match the first entry (i.e. first characters in extrecated string)
  for (auto &b : Config->skin_general->genre_bkgnd)
  {
    if (genre.compare(0, b.genre.size(), b.genre) == 0) // first characters of (extracted) genre match this genre_bkgnd genre string
    {
      return b.bm;
    }
  }
  return Config->skin_general->default_title_strip_bkgnd.bm; // no genre match, so return default title_strip background
}

bool DatabaseClass::CheckNewSortSectionStart(song_t *song)
{
  if (Config->skin_general->sort_songs_by.size() == 0) return false;

  static char previous_first_char {};
  char first_char;
  sort_songs_by_t song_sort { Config->skin_general->sort_songs_by.back()};
  string *str {};

  switch (song_sort.by)
  {
    case sort_songs_by_e::Title :
      str = &song->title;
      // log_file << "Title..." << endl;
      break;

    case sort_songs_by_e::Artist :
      str = &song->artist;
      // log_file << "Artist..." << endl;
      break;

    case sort_songs_by_e::Album :
      str = &song->album;
      // log_file << "Album..." << endl;
      break;

    case sort_songs_by_e::AlbumArtist :
      str = &song->albumArtist;
      // log_file << "Album Artist..." << endl;
      break;

    case sort_songs_by_e::Year :
      str = &song->year;
      // log_file << "Year..." << endl;
      break;

    case sort_songs_by_e::Genre :
      str = &song->genre;
      // log_file << "Genre..." << endl;
      break;

    case sort_songs_by_e::TrackNumber :
      str = &song->trackNumberStr;
      // log_file << "Track Number..." << endl;
      break;

    case sort_songs_by_e::Publisher :
      str = &song->publisher;
      // log_file << "Publisher..." << endl;
      break;

    case sort_songs_by_e::ISRC :
      str = &song->isrc;
      // log_file << "ISRC..." << endl;
      break;

    case sort_songs_by_e::Custom :
      str = &song->custom_tag;
      // log_file << "Custom MP3 tag..." << endl;
      break;

    case sort_songs_by_e::Random :
      return false;
      break;

    case sort_songs_by_e::Unsorted :
      return false;
      break;

  }

  if (str->size())
  {
    first_char = tolower(str->at(0));
    if (previous_first_char != first_char)
    {
      previous_first_char = first_char;
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
// The filter function applies the search strings to each song and marks a song as
// 'ignore' if it fails the search criterion

bool findStringIC(const std::string & strHaystack, const std::string & strNeedle)
{
  auto it = std::search(
    strHaystack.begin(), strHaystack.end(),
    strNeedle.begin(),   strNeedle.end(),
    [](char ch1, char ch2) { return std::toupper(ch1) == ch2; } // assumes ch2 (needle) is already upper case
  );
  return (it != strHaystack.end() );
}

void DatabaseClass::Filter(void)
{
  uint32_t songs_filtered {};
  uint32_t percent_filtered {};
  number_of_search_songs = number_of_songs;
  for (auto &s : DatabaseClass::database)
  {
    percent_filtered = (100 * ++songs_filtered) / number_of_songs;
    if ((percent_filtered % 5) == 0)
    {
      ProgressBar->Draw("Searching...", percent_filtered);
    }

    // this_thread::sleep_for(chrono::milliseconds(500));

    s.ignore = false;

    // ignore song if any one of the filter criterion fails...
    if (search_filter_Title.size())
    {
      if (findStringIC(s.title, search_filter_Title) == false) // no search string match
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }

    if (search_filter_Artist.size())
    {
      if (findStringIC(s.artist, search_filter_Artist) == false)
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }

    if (search_filter_Album.size())
    {
      if (findStringIC(s.album, search_filter_Album) == false)
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }
    
    if (search_filter_AlbumArtist.size())
    {
      if (findStringIC(s.albumArtist, search_filter_AlbumArtist) == false)
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }
    
    if (search_filter_Genre.size())
    {
      if (findStringIC(s.genre, search_filter_Genre) == false)
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }
    
    if (search_filter_Year.size())
    {
      if (findStringIC(s.year, search_filter_Year) == false)
      {
        s.ignore = true;
        --number_of_search_songs;
        continue;
      }
    }
  }

  log_file << "number_of_songs = " << number_of_songs << endl;
  log_file << "number_of_search_songs = " << number_of_search_songs << endl;

  status.num_search_songs_str = to_string(number_of_search_songs);

  BuildTitleStrips();

  Engine->status_event |= StatusEvent_NewDatabaseSearch;
}

///////////////////////////////////////////////////////////////////////////////
// fill the song_lookup 2d vector with title_strips of song entries
// lower dimension holds entries on each title_strip, upper dimension holds complete title_strips...

void DatabaseClass::BuildTitleStrips(void)
{
  vector<song_t*> title_strip(Config->skin_general->songs_per_title_strip, nullptr);
  uint32_t entry_number_this_title_strip { 0 };
  string previousAlbum {};

  number_of_title_strips = 0;
  jump_sort_title_strip.clear();
  song_lookup.clear();
  
  for (auto current_song { 0 }; current_song < number_of_songs; ) // for every (not ignored) song in the database
  {
    song_t *song { &DatabaseClass::database.at(current_song++) };
    if (song->ignore) continue;
    if ((Config->skin_general->album_mode) && (song->album != previousAlbum))
    // albums mode and album name changed, so start a new title_strip...
    {
      if (entry_number_this_title_strip) // don't start new title_strip if last just pushed back
      {
        if (number_of_title_strips > 0)
        {
          song_lookup.push_back(title_strip); // don't push anything before very first title_strip
        }
        entry_number_this_title_strip = 0;
      }
    }

    if (entry_number_this_title_strip == 0) // first entry on a title_strip
    {
      if ((number_of_title_strips % Config->skin_general->num_title_strips) == 0) // check first song every Config->skin_general->num_title_strips
      {
        if (CheckNewSortSectionStart(song))
        {
          jump_sort_title_strip.push_back(number_of_title_strips);// / Config->skin_general->num_title_strips);
        }
      }
      number_of_title_strips++;
      fill(title_strip.begin(), title_strip.end(), nullptr); // all entries default to empty
    }

    // add song from database to title_strip...
    title_strip.at(entry_number_this_title_strip++) = song;
    previousAlbum = song->album;
    // check if we have filled the current title_strip up; if so, add it to the song_lookup table
    if (entry_number_this_title_strip == Config->skin_general->songs_per_title_strip) // title_strip complete 
    {
      song_lookup.push_back(title_strip);
      entry_number_this_title_strip = 0;
    }
    else // paired song?...
    {
      if (Config->skin_general->album_mode == false)
      {
        if (Config->skin_general->pair_songs != pair_songs_e::No)
        { // if pairing songs, see if next song in database is by the same artist...
          while ((current_song < number_of_songs) && DatabaseClass::database.at(current_song).ignore) ++current_song; // find next song which isn't flagged as ignore
          if (current_song == number_of_songs) break; // no songs left
          // If in Dual pair_song mode we pair the songs up regardless of if they share the same artist
          // Otherwise (in Yes pair_song mode) we pair the songs up only if they share the same artist
          if ((Config->skin_general->pair_songs == pair_songs_e::Dual) || (song->artist == DatabaseClass::database.at(current_song).artist))
          { // yes, so add next song (ptr)
            song = &DatabaseClass::database.at(current_song++);
            title_strip.at(entry_number_this_title_strip) = song;
          }
          ++entry_number_this_title_strip;
          previousAlbum = song->album;
          if (entry_number_this_title_strip == Config->skin_general->songs_per_title_strip) // title_strip complete or no more songs
          {
            song_lookup.push_back(title_strip);
            entry_number_this_title_strip = 0;
          }
        }
      }
    }
  }

  if (entry_number_this_title_strip) // push a partially filled title_strip into the lookup vector...
  {
    song_lookup.push_back(title_strip);
  }
  
  song_lookup.shrink_to_fit(); // free unused capacity
  
  status.num_title_strips_str = to_string(number_of_title_strips);

  #if 0
  // debug print out of title_strips...
  for (uint32_t p {} ; p < song_lookup.size(); ++p) {
    log_file << endl << "title strip " << p << " ..." << endl;

    for (auto e : song_lookup.at(p)) {
      if (e == nullptr) log_file << "------" << endl;
      else log_file << e->title << endl;
    }
  }
  #endif

}

///////////////////////////////////////////////////////////////////////////////
// retrieve a song from the database, by specifying its filename...
// note this will be slow, but is used when loading a playlist at startup

song_t* DatabaseClass::GetSong
(
  const string &filename
)
{
  uint32_t title_strip {};
  uint32_t entry {};
  auto pos = std::find_if(DatabaseClass::database.begin(), DatabaseClass::database.end(), [s = filename](const song_t song) -> bool { return s == song.filename; });

  if (pos == DatabaseClass::database.end()) return nullptr;
  return &DatabaseClass::database.at(pos - DatabaseClass::database.begin());
}

///////////////////////////////////////////////////////////////////////////////
// Check is a song is in the history...

bool DatabaseClass::SongIsInHistory(song_t *song)
{
  deque<song_t *> *history = &PlayQueue->song_play_history;
  deque<song_t *> *playqueue = &PlayQueue->queue;

  if (find(history->begin(), history->end(), song) == history->end()) // song not in history
  {
    if (find(playqueue->begin(), playqueue->end(), song) == playqueue->end()) return false; // and also not in playqueue
  }
  return true; // is in history or playqueue
}

///////////////////////////////////////////////////////////////////////////////
// retrieve a song from the database, by specifying its title_strip number and
// entry position in that title_strip...

song_t* DatabaseClass::GetSong
(
  const uint32_t title_strip,
  const uint32_t entry
)
{
  return song_lookup.at(title_strip).at(entry);
}


///////////////////////////////////////////////////////////////////////////////
// retrieve the next song from the database (used in "sorted" choice Attract Mode)...
song_t* DatabaseClass::GetNextSong(void)
{
  static uint32_t next_song { 0 };

  song_t *song { &DatabaseClass::database.at(next_song) };
  
  if (++next_song == number_of_songs)
  {
    next_song = 0;
  }
  
  return song;
}

///////////////////////////////////////////////////////////////////////////////
// retrieve a random song from the database...

song_t* DatabaseClass::GetSong(void)
{
  uint32_t tries { 500 };
  song_t *song;
  deque<song_t *> *history = &PlayQueue->song_play_history;
  deque<song_t *> *playqueue = &PlayQueue->queue;
  // bool duplicate { false };
  PlayQueue->mtx.lock();

  while (tries--)
  // make sure we don't add one from the song_play_history, or also one from the playqueue, and one that is not being ignored...
  // if we timeout then just send back one anyway
  {
    song = &DatabaseClass::database.at(fast_random::rand() % number_of_songs);
    if (song->ignore) continue; // don't use this one
    if (SongIsInHistory(song) == false) break;
  }

  PlayQueue->mtx.unlock();
  return song;
}

///////////////////////////////////////////////////////////////////////////////
// retrieve a random song from the database from a certain genre...

song_t* DatabaseClass::GetGenreSong
(
  const string &genre
)
{
  uint32_t tries { 1000 };
  song_t *song;
  // deque<song_t *> *history = &PlayQueue->song_play_history;
  // deque<song_t *> *playqueue = &PlayQueue->queue;
  // bool duplicate { false };

  if (genre == GenreAnyStr)
  {
    song = GetSong(); // get a random song (genre doesn't matter)
  }
  else // genre does matter
  {
    while (tries--)
    {
      song = GetSong(); // get a random song (which isn't currently in the playqueue or history)

      // check if it's the genre we want...
      if (song->genre == genre) break; // genre exactly matches song genre string
      // if (song->genre.find(genre) != string::npos) break; // genre appears in song genre string
    }
  }

  return song;
}
