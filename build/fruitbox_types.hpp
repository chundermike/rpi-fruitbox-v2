#pragma once

using namespace std;

#define HINT      "HINT: "
#define NOTE      "NOTE: "
#define WARNING   "WARNING: "
#define ERROR     "ERROR: "

#define FILE_SEPARATOR '/'

constexpr char commandLineArgVersion[]          { "--version" };
constexpr char commandLineArgCfg[]              { "--cfg" };
constexpr char commandLineArgSkin[]             { "--skin" };
constexpr char commandLineArgNoSplash[]         { "--no-splash" };
constexpr char commandLineArgMusicPath[]        { "--music-path" };
constexpr char commandLineArgUserGuide[]        { "--user-guide" };
constexpr char commandLineArgSavePlaylist[]     { "--save-playlist" };
constexpr char commandLineArgLoadPlaylist[]     { "--load-playlist" };
constexpr char commandLineArgDebugSongNums[]    { "--debug-song-nums" };
constexpr char commandLineArgNoDbRefresh[]      { "--no-database-refresh" };
constexpr char commandLineArgForceDbRefresh[]   { "--force-database-refresh" };
constexpr char commandLineArgNoScale[]          { "--no-scale" };
constexpr char commandLineArgRotate[]           { "--rotate" };
constexpr char commandLineArgIniFile[]          { "--ini" };
constexpr char commandLineArgDumpTitleStrips[]  { "--dump-title-strips" };
constexpr char commandLineArgDisplaySize[]      { "--display-size" };

constexpr char commandLineOptVersion[]          { "                       " };
constexpr char commandLineOptSkin[]             { " <filename>               " };
constexpr char commandLineOptIniFile[]          { " <filename>                " };
constexpr char commandLineOptDumpTitleStrips[]  { "             " };
constexpr char commandLineOptDisplaySize[]      { " <width> <height> " };
constexpr char commandLineOptDatabase[]         { " <filename>           " };
constexpr char commandLineOptMusicPath[]        { " <filepath>         " };
constexpr char commandLineOptUserGuide[]        { "                    " };
constexpr char commandLineOptSavePlaylist[]     { " <filename>      "};
constexpr char commandLineOptLoadPlaylist[]     { " <filename>      "};
constexpr char commandLineOptDebugSongNums[]    { "               "};
constexpr char commandLineOptNoDbRefresh[]      { "           "};
constexpr char commandLineOptForceDbRefresh[]   { "        "};
constexpr char commandLineOptConfigButtons[]    { "                "};
constexpr char commandLineOptCalibrateTouch[]   { "               "};
constexpr char commandLineOptScreenshot[]       { "                    "};
constexpr char commandLineOptNoScale[]          { "                      "};
constexpr char commandLineOptRotate[]           { " <angle>                "};

constexpr char defaultIniFilename[]             { "fruitbox.ini" };
constexpr char defaultDatabaseFilename[]        { "fruitbox.db" };
constexpr char defaultScreenshotFilename[]      { "screenshot.jpg" };
constexpr char defaultFirstSelectButtons[]      { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
constexpr char defaultSecondSelectButtons[]     { "0123456789" };
constexpr char undefinedSelectDigit             { '-' };

constexpr char CalibrateTouchTitleStr[]         { "Touch Screen Calibration" };
constexpr char CalibrateTouchPressTargetStr[]   { "Press Target Center" };
constexpr char CalibrateTouchCompleteStr[]      { "Calibration Complete. Restart required" };
constexpr char PressAnyKeyStr[]                 { "Press Any Key" };
constexpr char userguideFilename[]              { "userguide.txt" };

constexpr char multiCfgParameter[]              { " * " };
constexpr char invalidTimeHMS[]                 { "--:--:--" };
constexpr char invalidTimeMS[]                  { "--:--" };
constexpr char zeroTimeHMS[]                    { "00:00:00" };
constexpr char timeFormatHMS[]                  { "%02d:%02d:%02d" };
constexpr char zeroTimeMS[]                     { "00:00" };
constexpr char timeFormatMS[]                   { "%02d:%02d" };

constexpr int32_t SystemFontNumber              { 0 };
constexpr int32_t UndefinedFontNumber           { ~0 };
constexpr int32_t TextModeNormal                { 0 };
constexpr int32_t TextModeCondensed             { -1 };
constexpr int32_t TextModeRegularEllipsis       { -2 };
constexpr int32_t TextModeWordEllipsis          { -3 };

constexpr int32_t FloatPrecision                { 1 };

inline auto SecondsToHours   = [](uint32_t A) -> uint32_t { return A / 3600; } ;
inline auto SecondsToMinutes = [](uint32_t A) -> uint32_t { return (A / 60) % 60; } ;
inline auto SecondsToSeconds = [](uint32_t A) -> uint32_t { return A % 60; } ;

inline auto StrHrMinSec = [](uint32_t hms) -> string {
  stringstream s;
  s << setfill('0') << setw(2) << SecondsToHours(hms)  << ":"
    << setfill('0') << setw(2) << SecondsToMinutes(hms) << ":"
    << setfill('0') << setw(2) << SecondsToSeconds(hms);
  return s.str();
};

inline auto StrMinSec = [](uint32_t ms) -> string { 
  if (ms > 3600) // more than 1 hr...
  {
    return StrHrMinSec(ms); // ...so switch to HH:MM:SS
  }
  else {
    stringstream s;
    s << setfill('0') << setw(2) << SecondsToMinutes(ms) << ":" 
      << setfill('0') << setw(2) << SecondsToSeconds(ms); 
    return s.str(); 
  }
};

constexpr char ButtonTypeKeyStr[]           { "Key" };
constexpr char ButtonDeviceStr[]            { "(" };
constexpr char ButtonDeviceStrPost[]        { ")" };
constexpr char ButtonTypeGPIOStr[]          { "GPIO_" };

constexpr char UnknownTitleStr[]            { "Unknown Title" };
constexpr char UnknownStreamTitleStr[]      { "" };
constexpr char UnknownStreamUrlStr[]        { "" };
constexpr char UnknownArtistStr[]           { "Unknown Artist" };
constexpr char UnknownAlbumStr[]            { "Unknown Album" };
constexpr char UnknownAlbumArtistStr[]      { "Unknown Album Artist" };
constexpr char UnknownYearStr[]             { "Unknown Year" };
constexpr char UnknownPublisherStr[]        { "Unknown Publisher" };

constexpr char UnknownGenreStr[]            { "Unknown" };
constexpr char GenreAnyStr[]                { "Any" };
constexpr char GenreOffStr[]                { "Off" };

constexpr char TimeUnitsTicksStr[]          { "Tick" };
constexpr char TimeUnitsSecondsStr[]        { "Second" };
constexpr char TimeUnitsMinutesStr[]        { "Minute" };
constexpr char TimeUnitsHoursStr[]          { "Hour" };

constexpr int32_t MinSongVolume             { 0 };
constexpr int32_t MaxSongVolume             { 100 };
constexpr int32_t MinSongVolumeStep         { 1 };
constexpr int32_t MaxSongVolumeStep         { 100 };
constexpr int32_t MinPlayQueueLength        { 1 };
constexpr int32_t MaxPlayQueueLength        { 1000000 };
constexpr int32_t MinCreditsPerCoin         { 1 };
constexpr int32_t MaxCreditsPerCoin         { 1000 };
constexpr int32_t MinCreditsPerSong         { 1 };
constexpr int32_t MaxCreditsPerSong         { 1000 };

#define NUM_GENRES (192 + 3) /* +3 for GenreOffStr, GenreAnyStr, UnknownGenreStr */

struct dynamic_parameter_t
{
  string label {""};
  uint32_t event_mask {0};
  bool is_dynamic {false};
  bool is_spectrum_analyser {false};
  void (*Update)(void *var) {nullptr};
};

extern const array<dynamic_parameter_t, 12> DynamicParameter;

const dynamic_parameter_t DynamicParameterNone {"${NONE}", 0, false, false, nullptr};

struct dynamic_t
{
  const dynamic_parameter_t *param { &DynamicParameterNone }; // points to one of the pre-defined parameters
  int32_t val { 0 };
  int32_t min { 0 };
  int32_t max { 0 };
  bool forward { true };
  int32_t mode_param { 0 };
};

struct dynamics2_t
{
  dynamic_t x {};
  dynamic_t y {};
};

struct dynamics4_t
{
  dynamic_t x {};
  dynamic_t y {};
  dynamic_t w {};
  dynamic_t h {};
};

struct ints2_t
{
  int32_t x {};
  int32_t y {};
};

struct uints2_t
{
  uint32_t x {};
  uint32_t y {};
};

const array<string, NUM_GENRES> GenreStr {
 "Blues",
 "Classic Rock",
 "Country",
 "Dance",
 "Disco",
 "Funk",
 "Grunge",
 "Hip-Hop",
 "Jazz",
 "Metal",
 "New Age",
 "Oldies",
 "Other",
 "Pop",
 "R&B",
 "Rap",
 "Reggae",
 "Rock",
 "Techno",
 "Industrial",
 "Alternative",
 "Ska",
 "Death Metal",
 "Pranks",
 "Soundtrack",
 "Euro-Techno",
 "Ambient",
 "Trip-Hop",
 "Vocal",
 "Jazz+Funk",
 "Fusion",
 "Trance",
 "Classical",
 "Instrumental",
 "Acid",
 "House",
 "Game",
 "Sound Clip",
 "Gospel",
 "Noise",
 "AlternRock",
 "Bass",
 "Soul",
 "Punk",
 "Space",
 "Meditative",
 "Instrumental Pop",
 "Instrumental Rock",
 "Ethnic",
 "Gothic",
 "Darkwave",
 "Techno-Industrial",
 "Electronic",
 "Pop-Folk",
 "Eurodance",
 "Dream",
 "Southern Rock",
 "Comedy",
 "Cult",
 "Gangsta Rap",
 "Top 40",
 "Christian Rap",
 "Pop / Funk",
 "Jungle",
 "Native American",
 "Cabaret",
 "New Wave",
 "Psychedelic",
 "Rave",
 "Showtunes",
 "Trailer",
 "Lo-Fi",
 "Tribal",
 "Acid Punk",
 "Acid Jazz",
 "Polka",
 "Retro",
 "Musical",
 "Rock & Roll",
 "Hard Rock",
 "Folk",
 "Folk-Rock",
 "National Folk",
 "Swing",
 "Fast Fusion",
 "Bebob",
 "Latin",
 "Revival",
 "Celtic",
 "Bluegrass",
 "Avantgarde",
 "Gothic Rock",
 "Progressive Rock",
 "Psychedelic Rock",
 "Symphonic Rock",
 "Slow Rock",
 "Big Band",
 "Chorus",
 "Easy Listening",
 "Acoustic",
 "Humour",
 "Speech",
 "Chanson",
 "Opera",
 "Chamber Music",
 "Sonata",
 "Symphony",
 "Booty Bass",
 "Primus",
 "Porn Groove",
 "Satire",
 "Slow Jam",
 "Club",
 "Tango",
 "Samba",
 "Folklore",
 "Ballad",
 "Power Ballad",
 "Rhythmic Soul",
 "Freestyle",
 "Duet",
 "Punk Rock",
 "Drum Solo",
 "A Cappella",
 "Euro-House",
 "Dance Hall",
 "Goa",
 "Drum & Bass",
 "Club-House",
 "Hardcore",
 "Terror",
 "Indie",
 "BritPop",
 "Negerpunk",
 "Polsk Punk",
 "Beat",
 "Christian Gangsta Rap",
 "Heavy Metal",
 "Black Metal",
 "Crossover",
 "Contemporary Christian",
 "Christian Rock",
 "Merengue",
 "Salsa",
 "Thrash Metal",
 "Anime",
 "JPop",
 "Synthpop",
 "Abstract",
 "Art Rock",
 "Baroque",
 "Bhangra",
 "Big Beat",
 "Breakbeat",
 "Chillout",
 "Downtempo",
 "Dub",
 "EBM",
 "Eclectic",
 "Electro",
 "Electroclash",
 "Emo",
 "Experimental",
 "Garage",
 "Global",
 "IDM",
 "Illbient",
 "Industro-Goth",
 "Jam Band",
 "Krautrock",
 "Leftfield",
 "Lounge",
 "Math Rock",
 "New Romantic",
 "Nu-Breakz",
 "Post-Punk",
 "Post-Rock",
 "Psytrance",
 "Shoegaze",
 "Space Rock",
 "Trop Rock",
 "World Music",
 "Neoclassical",
 "Audiobook",
 "Audio Theatre",
 "Neue Deutsche Welle",
 "Podcast",
 "Indie Rock",
 "G-Funk",
 "Dubstep",
 "Garage Rock",
 "Psybient",
  GenreOffStr, // fruitbox specific
  GenreAnyStr, // fruitbox specific
  UnknownGenreStr // fruitbox specific
};

constexpr char m3uFile_ExtInf[]             { "#EXTINF" };
constexpr char URLPrefix[]                  { "http" };
constexpr char plsFile_File[]               { "File" };
constexpr char plsFile_Title[]              { "Title" };
constexpr char plsFile_length[]             { "Length" };


enum class title_strip_move_direction_e
{
  Left,
  Right,
  None
};

enum class play_type_e
{
  FreePlay,
  CreditPlay,
  AttractMode
};

enum class spectrum_analyser_channel_e
{
  Left,
  Right,
  Both
};

enum class spectrum_analyser_mode_e
{
  Scaled,
  Clipped,
  Position
};

enum class select_buttons_sequence_e
{
  RowCol,
  ColRow
};

enum class sort_songs_by_e
{
  Title,
  Artist,
  Album,
  AlbumArtist,
  Year,
  Genre,
  TrackNumber,
  Publisher,
  ISRC,
  Custom,
  Random,
  Unsorted
};

enum class pair_songs_e
{
  No,
  Yes,
  Dual
};

enum class title_desc_e
{
  String,
  SongTitle,
  Artist,
  AlbumTitle,
  AlbumArtist,
  Year,
  Genre,
  TrackNumber,
  Publisher,
  ISRC,
  Custom,
  Length,
  PairedSongTitle,
  PairedArtist,
  PairedAlbumTitle,
  PairedAlbumArtist,
  PairedYear,
  PairedGenre,
  PairedTrackNumber,
  PairedPublisher,
  PairedISRC,
  PairedCustom,
  PairedLength,
  SelectCode
};

enum class select_mode_e
{
  SelectCode,
  JoyStick,
  TouchSong
};

enum class artwork_mode_e
{
  Auto,
  None,
  Embedded,
  Specified,
  Folder,
  Logo
};

enum class input_type_e
{
  None,
  Key,
  JoyStick,
  JoyButton,
  Touch,
  // Mouse,
  GPIO
};

enum class gpio_input_state_e
{
  NoChange = -1,
  NotPressed = 0,
  Pressed = 1
};

enum class gpio_e
{
  Unused = 0,
  Reserved,
  InputNormallyClosed,
  InputNormallyOpen,
  Output
};

enum class replay_gain_e
{
  None = 0,
  Track = 1,
  Album = 2
};

enum class attract_choice_e
{
  Random = 0,
  Sorted = 1
};

enum class song_type_e
{
  unknown,
  mp3,
  ogv,
  url
};

struct sort_songs_by_t
{
  sort_songs_by_e by {};
  bool descending { false };
};

struct band_gain_t
{
  uint32_t num { 0 };
  uint32_t val { 0 };
  double gain { 1.0 };
  ints2_t offset { 0, 0 };
  ALLEGRO_COLOR tint { };
};

struct status_line_t
{
  string str {};
  int32_t width {};
  int32_t offset {};
  ALLEGRO_BITMAP *bitmap {};
};

struct rgba_uchar_t
{
  unsigned char r {};
  unsigned char g {};
  unsigned char b {};
  unsigned char a {};
};

struct rgba_t
{
  uint32_t r {};
  uint32_t g {};
  uint32_t b {};
  uint32_t a {};
};

struct rgb_t
{
  uint32_t r {};
  uint32_t g {};
  uint32_t b {};
};

struct text_t
{
  int32_t font_number { UndefinedFontNumber };
  ALLEGRO_COLOR colour {};
  int32_t alignment {};
  bool capitalise {};
  int32_t mode {};
  bool quoted {};
  ints2_t offset {};
  uint32_t max_width {};
};

struct bitmap_t
{
  string filename {};
  ALLEGRO_BITMAP *handle {};
  bool destroy_needed { false };
};

struct video_t
{
  string filename {};
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_EVENT event;
  ALLEGRO_VIDEO *handle {};
  ALLEGRO_BITMAP *bm_handle {};
  bool playing {};
};

struct sound_t
{
  string filename {};
  ALLEGRO_SAMPLE *handle { nullptr };
  ALLEGRO_SAMPLE_ID id {};
  ALLEGRO_SAMPLE_INSTANCE *instance { nullptr };
  bool loop { false };
  uint32_t length {};
  uint32_t volume { MaxSongVolume / 2 };
};

struct font_t
{
  string filename {};
  ALLEGRO_FONT *handle {};
  int32_t size {};
};

struct title_strip_style_t
{
  uint32_t effect {0};
  uint32_t speed {8};
  bool fading {true};
};

struct genre_bkgnd_t
{
  ALLEGRO_BITMAP *bm {};
  string genre {};
};

enum class dynamic_flag_en_e : uint32_t 
{
  None = 0,
  Flag1 = 1,
  Flag2 = 2,
  Flag3 = 3,
  Flag4 = 4
};

enum class time_unit_e : uint32_t
{
  Ticks,
  Seconds,
  Minutes,
  Hours
};

struct time_unit_t
{
  float value {};
  uint32_t ticks {};
  time_unit_e units { time_unit_e::Ticks };
  string units_str { TimeUnitsTicksStr };
};

static const time_unit_t TimeUnitOneTick {
  1.0, 1, time_unit_e::Ticks, TimeUnitsTicksStr
};

static const time_unit_t TimeUnitOneSecond {
  1.0, 1, time_unit_e::Seconds, TimeUnitsSecondsStr
};

static const time_unit_t TimeUnitFiveSeconds {
  5.0, 1, time_unit_e::Seconds, TimeUnitsSecondsStr
};

static const time_unit_t TimeUnitTenSeconds {
  10.0, 1, time_unit_e::Seconds, TimeUnitsSecondsStr
};

static const time_unit_t TimeUnitSixtySeconds {
  60.0, 1, time_unit_e::Seconds, TimeUnitsSecondsStr
};

static const time_unit_t TimeUnitSeventySeconds {
  70.0, 1, time_unit_e::Seconds, TimeUnitsSecondsStr
};

static const time_unit_t TimeUnitOneMinute {
  1.0, 1, time_unit_e::Minutes, TimeUnitsMinutesStr
};

static const time_unit_t TimeUnitZero {
  0.0, 0, time_unit_e::Seconds, TimeUnitsSecondsStr
};

struct song_t
{
  bool ignore { false };
  string filename {};
  string title {UnknownTitleStr};
  string stream_title {UnknownStreamTitleStr};
  string stream_url {UnknownStreamUrlStr};
  string artist {UnknownArtistStr};
  string albumArtist {UnknownAlbumArtistStr};
  string album {UnknownAlbumStr};
  string year {UnknownYearStr};
  string publisher {UnknownPublisherStr};
  string isrc {""};
  string custom_tag {""};
  string genre {UnknownGenreStr};
  ALLEGRO_BITMAP *strip_bg { nullptr };
  uint32_t trackNumber {0};
  string trackNumberStr {"0"};
  uint32_t length {0};
  string lengthStr {"00:00"};
  bitmap_t artwork {};
  song_type_e type { song_type_e::unknown };
  play_type_e play_type { play_type_e::FreePlay };
};

struct area_t
{
  uint32_t x {};
  uint32_t y {};
  uint32_t w {};
  uint32_t h {};
};

struct touch_area_t
{
  uint32_t x {};
  uint32_t y {};
  uint32_t w {};
  uint32_t h {};
  ALLEGRO_BITMAP *bitmap { nullptr };
};

struct input_event_t
{
  input_type_e type;
  array<int32_t, 4> param {{0, 0, 0, 0}};
};

struct button_t
{
  string name {};
  input_type_e type { input_type_e::None };
  // input_type_e type_backup { input_type_e::None };
  array<int32_t, 4> param {{0, 0, 0, 0}};
  string val_str;
  touch_area_t skin_touch_area {};

  touch_area_t menu_touch_area {};
  bool menu_enable { false };
  string menu_label {};
  // string user_label;
};

struct text_description_t
{
  const string name;
  const string * (*add_desc_func)(const song_t *song, const song_t *paired_song);
};

struct default_button_t
{
  uint32_t num;
  const char *name;
  const char *desc;
  int32_t key;
  const char *menu_label;
};

inline string YesNo(const bool v)
{
  return (v ? "Yes" : "No");
}

inline string EnableDisable(const bool v)
{
  return (v ? "Enabled" : "Disabled");
}

inline string AttractChoiceString(const attract_choice_e v)
{
  return ((v == attract_choice_e::Random) ? "Random" : "Sorted");
}

inline string DescendAscend(const bool v)
{
  return (v ? "Descend" : "Ascend");
}

struct status_t
{
  uint32_t credits { 0 };
  uint32_t songs_credited { 0 };
  song_t *now_playing { };
  song_t *last_played { };
  string select_code_str {  };
  string num_songs_str {  };
  string num_search_songs_str {  };
  string num_title_strips_str {  };
  string first_visible_title_strip_str {};
  string last_visible_title_strip_str {};
  uint32_t now_playing_start_time { };
  string now_playing_elapsed_time_str { invalidTimeMS };
  string now_playing_length_str { invalidTimeMS };
  string last_played_length_str { invalidTimeMS };
  string now_playing_time_remaining_str { invalidTimeMS };
  float now_playing_time_remaining_scale { 0.0 };
  float song_load_position { 0.0 };
  string credits_str { "00" };
  string songs_credited_str { "00" };
  string volume_str { "---" };
  string coming_up_num_songs_str { "0" };
  string playqueue_space_str {  };
  string coming_up_total_length_str { zeroTimeHMS };
  string num_songs_played_str { "0" };
  string songs_played_total_time_str { zeroTimeHMS };
  // bool title_strips_moving { false };
};

