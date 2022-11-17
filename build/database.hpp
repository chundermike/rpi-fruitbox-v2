#pragma once

#include "fruitbox.hpp"

using namespace std;

class DatabaseClass {
public:
  DatabaseClass(void);
  bool SongIsInHistory(song_t *song);
  song_t* GetSong(const uint32_t title_strip, const uint32_t entry);
  song_t* GetNextSong(); // get next (sorted) song in the database 
  song_t* GetSong(const string &filename);
  song_t* GetSong(void); // get a random song
  song_t* GetGenreSong(const string &genre); // get random song from specified genre
  void DumpTitleStrips(void);
  void Filter(void);
  uint32_t number_of_songs { };
  uint32_t number_of_search_songs { };
  uint32_t number_of_title_strips { };
  vector<uint32_t> jump_sort_title_strip {};
  string dump_title_strip_filename {};
  bool dump_title_strips { false };
  string search_filter_Title {};
  string search_filter_Artist {};  
  string search_filter_Album {};
  string search_filter_AlbumArtist {};
  string search_filter_Genre {};
  string search_filter_Year {};
private:
  static string database_filename;
  static string database_filepath;
  static vector<song_t> database;
  // static string music_path;
  static fstream dbFile;
  static deque<string> song_info;
  vector< vector<song_t*> > song_lookup { };
  // void Create(const string filename);
  static void ReadFile(void);
  static int Build(const char *path, const struct stat *sptr, int type);
  static ALLEGRO_BITMAP *GenreStrToTitleStripBM(string &genre);
  bool CheckNewSortSectionStart(song_t *song);
  void BuildTitleStrips(void);
  static bool db_out_of_date;
  static bool create_db_file;
  static DialogListClass *ListDialog;
  static bool SortByAlbum(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.album < song_b.album) return true;
    return false;
  }

  static bool SortByAlbumDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.album > song_b.album) return true;
    return false;
  }

  static bool SortByTrackNumber(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.trackNumber < song_b.trackNumber) return true;
    return false;
  }

  static bool SortByTrackNumberDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.trackNumber > song_b.trackNumber) return true;
    return false;
  }

  static bool SortByAlbumArtist(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.albumArtist < song_b.albumArtist) return true;
    return false;
  }

  static bool SortByAlbumArtistDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.albumArtist > song_b.albumArtist) return true;
    return false;
  }

  static bool has_prefix(const string& a, const string& b)
  {
    return std::equal(a.begin(), a.begin()+3, b.begin(), [](char ca, char cb) { return tolower(ca) == cb; });
  }

  static bool SortByArtistIgnorePrefixThe(const song_t &song_a, const song_t &song_b)
  {
    bool this_a { song_a.artist.size() >= 4 };
    bool this_b { song_b.artist.size() >= 4 };

// log_file << boolalpha << "1) " << song_a.artist << " " << this_a << " " << song_b.artist << " " << this_b << " : ";
    if (this_a) this_a = has_prefix(song_a.artist, "the ");
    if (this_b) this_b = has_prefix(song_b.artist, "the ");
// log_file << boolalpha << this_a << " " << this_b << endl;
    if (this_a && this_b)
    {
      if (song_a.artist.substr(4) < song_b.artist.substr(4)) return true;
    }
    else if (this_a)
    {
      if (song_a.artist.substr(4) < song_b.artist) return true;
    }
    else if (this_b)
    {
      if (song_a.artist < song_b.artist.substr(4)) return true;
    }
    else
    {
      if (song_a.artist < song_b.artist) return true;
    }
    return false;
  }

  static bool SortByArtistIgnorePrefixTheDescending(const song_t &song_a, const song_t &song_b)
  {
    bool this_a { song_a.artist.size() >= 4 };
    bool this_b { song_b.artist.size() >= 4 };

    if (this_a) this_a = has_prefix(song_a.artist, "the ");
    if (this_b) this_b = has_prefix(song_b.artist, "the ");

    if (this_a && this_b)
    {
      if (song_a.artist.substr(4) > song_b.artist.substr(4)) return true;
    }
    else if (this_a)
    {
      if (song_a.artist.substr(4) > song_b.artist) return true;
    }
    else if (this_b)
    {
      if (song_a.artist > song_b.artist.substr(4)) return true;
    }
    else
    {
      if (song_a.artist > song_b.artist) return true;
    }
    return false;
  }

  static bool SortByArtist(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.artist < song_b.artist) return true;
    return false;
  }

  static bool SortByArtistDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.artist > song_b.artist) return true;
    return false;
  }

  static bool SortByTitle(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.title < song_b.title) return true;
    return false;
  }

  static bool SortByTitleDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.title > song_b.title) return true;
    return false;
  }

  static bool SortByYear(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.year < song_b.year) return true;
    return false;
  }

  static bool SortByYearDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.year > song_b.year) return true;
    return false;
  }

  static bool SortByGenre(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.genre < song_b.genre) return true;
    return false;
  }

  static bool SortByGenreDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.genre > song_b.genre) return true;
    return false;
  }

  static bool SortByPublisher(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.publisher < song_b.publisher) return true;
    return false;
  }

  static bool SortByPublisherDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.publisher > song_b.publisher) return true;
    return false;
  }

  static bool SortByISRC(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.isrc < song_b.isrc) return true;
    return false;
  }

  static bool SortByISRCDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.isrc > song_b.isrc) return true;
    return false;
  }

  static bool SortByCustom(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.custom_tag < song_b.custom_tag) return true;
    return false;
  }

  static bool SortByCustomDescending(const song_t &song_a, const song_t &song_b)
  {
    if (song_a.custom_tag > song_b.custom_tag) return true;
    return false;
  }

};
