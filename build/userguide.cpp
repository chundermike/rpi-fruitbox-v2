///////////////////////////////////////////////////////////////////////////////
// Project fruitbox.  A Retro MP3 Jukebox forthe Raspberry Pi.
// Mike Kingsley 2016.
//
// userguide.cpp :
//
// Prints the user guide.
//
///////////////////////////////////////////////////////////////////////////////

#include "fruitbox.hpp"
#include "userguide.hpp"

using namespace std;

constexpr uint32_t rightMargin           { 120 };
constexpr uint32_t maxWordSize           { 20 };
constexpr char sectionNumberSepStr[]     { ": " };
constexpr char sectionindentStr[]        { "  " };
constexpr char subSectionindentStr []    { "    " };
constexpr char subSubSectionindentStr[]  { "      " };

size_t section_number = 0;
size_t sub_section_number = 0;

ofstream userguide {};

void UserGuideLine(const char *body, const char *indent)
{
  const char *b = body;
  char c;
  uint32_t x {};

  userguide << indent;
  while (c = *b++)
  {
    if (((x == 0) && ( c == ' ')) || (c == '\n')); else userguide << c;
    x++;
    if ((x == rightMargin) || (c == '\n') || ((c == ' ') && (x > rightMargin - maxWordSize)))
    {
      userguide << endl << indent;
      x = 0;
    }
  };
  userguide << endl;
}

void UserGuideBody(const char *body, const char *indent)
{
  UserGuideLine(body, indent);
  userguide << endl;
}

void UserGuideSection(const char *heading, const char *body)
{
  section_number++;
  sub_section_number = 0;
  userguide << endl << sectionindentStr << static_cast<int>(section_number) << sectionNumberSepStr << heading << endl << endl;

  UserGuideBody(body, sectionindentStr);
}

void UserGuideSubSection(const char *heading, const char *sub_heading, const char *body)
{
  if (heading[0])
  {
    sub_section_number++;
    userguide << endl << sectionindentStr << static_cast<int>(section_number) << "." << static_cast<int>(sub_section_number) << sectionNumberSepStr << heading << sub_heading << endl << endl;
  }
  UserGuideBody(body, subSectionindentStr);
}

void UserGuideShowTitleStripNameDescriptions(const char *indent)
{
  for (auto &t : text_description) {
    UserGuideLine(t.name.c_str(), indent);
  }
}
void UserGuideShowStatusVariables(const char *indent)
{
  for (auto &s : status_vars) {
    UserGuideLine(s.name.c_str(), indent);
    UserGuideBody(s.desc.c_str(), indent);
  }
}

void UserGuideShowIniParameters(const char *indent)
{
  Config->DescribeParamsIni(userguide, indent);
}

void UserGuideShowDynamicParameters(const char *indent)
{
  for (auto l = 1; l < DynamicParameter.size(); ++l) // don't print out element (0), as it's ${NONE}
  {
    UserGuideLine(DynamicParameter.at(l).label.c_str(), indent);
  }
  userguide << endl;
}

void UserGuideShowConfigParameters(const char *indent)
{
  Config->DescribeParams(userguide, indent);
}

void UserGuideShowGenres(const char *indent)
{
  userguide << endl << sectionindentStr << "** Recognised AttractModeGenre values are..." << endl << endl << sectionindentStr;
  for (uint32_t g = 0; g < NUM_GENRES; ++g)
  {
    userguide << setw(30) << GenreStr.at(g);
    if ((g % 4) == 3) userguide << endl << sectionindentStr;
  }
  userguide << endl << endl;
  userguide << sectionindentStr << "Note that you can also define your own Genres and fruitbox will recognise these if the 'AttractModeGenre' " << endl;
  userguide << sectionindentStr << "field matches the name in the MP3 (ID3v2) genre tag." << endl << endl;
  userguide << sectionindentStr << "fruitbox will make every effort to choose a song from the specified AttractModeGenre, but is constrained" << endl;
  userguide << sectionindentStr << "by the song history and number of songs available to choose from.  If it cannot choose a song" << endl;
  userguide << sectionindentStr << "in a reasonable time, it will play any song." << endl << endl;
}

void UserGuideShowButtonFileParameters(const char *indent)
{
  Config->buttons->DescribeParams(userguide, indent);
  userguide << endl;
}

void UserGuide(void)
{
  userguide.open(userguideFilename);
  
  UserGuideSection("Introduction", introduction_str);
  UserGuideSection("Starting Up", starting_up_str);
  UserGuideSection("Operation", operation_str);
  UserGuideSection("Command Line Options", command_line_options_str);
  UserGuideSubSection("--help", "", command_line_help_option_str);
  UserGuideSubSection(commandLineArgVersion, commandLineOptVersion, command_line_version_option_str);
  UserGuideSubSection(commandLineArgSkin, commandLineOptSkin, command_line_skin_option_str);
  UserGuideSubSection(commandLineArgIniFile, commandLineOptIniFile, command_line_ini_file_str);
  UserGuideSubSection(commandLineArgMusicPath, commandLineOptMusicPath, command_line_musicpath_option_str);
  UserGuideSubSection(commandLineArgUserGuide, commandLineOptUserGuide, command_line_user_guide_option_str);
  UserGuideSubSection(commandLineArgDebugSongNums, commandLineOptDebugSongNums, command_line_debug_song_nums_option_str);
  UserGuideSubSection(commandLineArgNoDbRefresh, commandLineOptNoDbRefresh, command_line_no_db_refresh_option_str);
  UserGuideSubSection(commandLineArgForceDbRefresh, commandLineOptForceDbRefresh, command_line_force_db_refresh_option_str);
  UserGuideSubSection(commandLineArgLoadPlaylist, commandLineOptLoadPlaylist, command_line_load_playlist_str);
  UserGuideSubSection(commandLineArgSavePlaylist, commandLineOptSavePlaylist, command_line_save_playlist_str);
  UserGuideSubSection(commandLineArgDumpTitleStrips, commandLineOptDumpTitleStrips, command_line_dump_title_strips_str);
  UserGuideSubSection(commandLineArgDisplaySize, commandLineOptDisplaySize, command_line_display_size_str);
  UserGuideSubSection(commandLineArgNoScale, commandLineOptNoScale, command_line_no_scale_str);
  UserGuideSubSection(commandLineArgRotate, commandLineOptRotate, command_line_rotate_str);
  UserGuideSection("Initialisation File", ini_file_str);
  UserGuideShowIniParameters(subSubSectionindentStr);
  UserGuideSection("Skin Selection", skin_selection_str);
  UserGuideSection("Database Creation", database_creation_str);
  UserGuideSubSection("MP3 File Support", "", mp3_file_support_str);
  UserGuideSubSection("Video (OGV) File Support", "", ogv_file_support_str);
  UserGuideSubSection("MP3 Stream (Internet Radio) Support", "", mp3_stream_support_str);
  UserGuideSection("Input Control Buttons", buttons_def_str);
  UserGuideSubSection("Default Buttons", "", button_control_summary_str);
  UserGuideSubSection("Touch Screen and Mouse Support", "", touch_screen_str);
  UserGuideSection("On-screen Menus", menus_str);
  UserGuideSubSection("Main Menu", "", main_menu_str);
  UserGuideSubSection("Search Menu", "", search_menu_str);
  UserGuideSection("Troubleshooting", troubleshooting_str);
  UserGuideSection("Hints and Tips", hints_and_tips_str);

  userguide << endl << endl << sectionindentStr <<  "If you wish to design your own skins, please read on..." << endl << endl;

  UserGuideSection("Configuration (Skin) Files", cfg_file_str);
  UserGuideShowConfigParameters(subSubSectionindentStr);
  UserGuideShowGenres(subSubSectionindentStr);
  UserGuideSubSection("Dynamic Parameter values", "", dynamics_pre_str);
  UserGuideShowDynamicParameters(subSubSectionindentStr);
  UserGuideSubSection("", "", dynamics_post_str);
  UserGuideSubSection("Time Values", "", timers_str);
  UserGuideSubSection("Status Bitmaps", "", status_bitmaps_str);
  UserGuideSubSection("Status Videos", "", status_videos_str);
  UserGuideSubSection("Spectrum Analyser", "", spectrum_str);
  UserGuideSubSection("Fonts and Text", "", font_text_def_str);
  UserGuideSubSection("FreePlay / Coin Mode", "", freeplay_or_coin_str);
  UserGuideSubSection("Touch Song Mode / Button Touch Areas", "", touch_areas_str);
  UserGuideSubSection("Mouse Mode", "", mouse_str);
  UserGuideSubSection("Joystick Mode", "", joystick_str);
  UserGuideSubSection("Instant Play", "", instant_play_str);
  UserGuideSubSection("Random Songs", "", random_songs_str);
  UserGuideSubSection("Albums / Singles Mode", "", albums_singles_mode_str);
  UserGuideSection("Screen Layout", screen_layout_str);
  UserGuideSubSection("TitleStrips", "", title_strips_str);
  UserGuideShowTitleStripNameDescriptions(subSubSectionindentStr);
  UserGuideSubSection("Status Boxes", "", status_boxes_pre_var_str);
  UserGuideShowStatusVariables(subSubSectionindentStr);
  UserGuideSubSection("", "", status_boxes_post_var_str);
  UserGuideSection("Sound Effects", sound_effects_str);
  UserGuideSection("Status Flags", status_flags_str);
  UserGuideSection("GPIO Input/Output", gpio_str);
  userguide.close();
  cout << "User Guide written to \"" << userguideFilename << "\"." << endl;
}
