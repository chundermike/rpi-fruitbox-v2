#pragma once

#include "fruitbox.hpp"

extern void error(const char *fmt, ...);

using namespace std;

constexpr uint32_t maxCfgKeywordWidth                    { 32 };
constexpr char TitleStripDescriptionsVarStart            { static_cast<char>(-128) };

constexpr char cfgFile_section_start                     { '[' };
constexpr char cfgFile_section_end                       { ']' };
constexpr char cfgFile_comment                           { '#' };
constexpr char cfgFile_keyword_param_separator[]         { "\t :=" };

constexpr char cfgSection_ini_general[]                  { "[general]" };
constexpr char cfgSection_ini_attract[]                  { "[attract mode]" };
constexpr char cfgSection_ini_skin_list[]                { "[skins]" };
constexpr char cfgSection_ini_buttons[]                  { "[buttons]" };
constexpr char cfgSection_ini_touch_screen[]             { "[touch screen]" };
constexpr char cfgSection_ini_mouse[]                    { "[mouse]" };
constexpr char cfgSection_ini_joystick[]                 { "[joystick]" };

constexpr char cfgSection_skin_general[]                 { "[general]" };
constexpr char cfgSection_touch_buttons[]                { "[touch buttons]" };
constexpr char cfgSection_touch_song[]                   { "[touch song]" };
constexpr char cfgSection_fonts[]                        { "[fonts]" };
constexpr char cfgSection_title_strip[]                  { "[title strip]" };
constexpr char cfgSection_status[]                       { "[status]" };
constexpr char cfgSection_bitmap[]                       { "[bitmap]" };
constexpr char cfgSection_spectrum_analyser[]            { "[spectrum]" };

constexpr char DefaultSkinStr[]                          { "skins/SB-M100/fruitbox.cfg" };
constexpr char cfgKeyword_SkinSize[]                     { "SkinSize" };
constexpr char cfgKeywordDesc_SkinSize[]                 { "<width> <height> Size of the skin (in pixels).\n" \
                                                           "                                      The skin is scaled to match the full screen size of the display" };
constexpr char cfgKeyword_SkinName[]                     { "SkinName" };
constexpr char cfgKeywordDesc_SkinName[]                 { "<name> of the skin" };

constexpr char cfgKeyword_SkinVersion[]                  { "SkinVersion" };
constexpr char cfgKeywordDesc_SkinVersion[]              { "<version string> of the skin" };

constexpr char cfgKeyword_SkinDescription[]              { "SkinDescription" };
constexpr char cfgKeywordDesc_SkinDescription[]          { "<description> of the skin" };

constexpr char cfgKeyword_Screenshot[]                   { "Screenshot" };
constexpr char cfgKeywordDesc_Screenshot[]               { "<filename> of screenshot capture" };

constexpr char cfgKeyword_MusicPath[]                    { "MusicPath" };
constexpr char cfgKeywordDesc_MusicPath[]                { "<filename> of path to music files (mp3, ogv, m3u, pls).  Can contain sub-directories.\n" };

constexpr char cfgKeyword_SortSongsBy[]                  { "SortSongsBy" };
constexpr char cfgKeywordDesc_SortSongsBy[]              { "<title|artist|album|albumArtist|year|genre|trackNumber|publisher|ISRC|custom|random|unsorted> [Descend|Ascend]\n" \
                                                           "                                      optional [Descend|Ascend] is sort direction (Ascend if not specified)" };

constexpr char cfgKeyword_NoDuplicates[]                 { "NoDuplicates" };
constexpr char cfgKeywordDesc_NoDuplicates[]             { "<yes|no> Prevent songs being added to the playqueue if they are already in the playqueue\n" \
                                                           "                                      Note enabling this option disables the [general] LoopPlayQueue parameter" };

constexpr char cfgKeyword_DuplicatesUseCredits[]         { "DuplicatesUseCredits" };
constexpr char cfgKeywordDesc_DuplicatesUseCredits[]     { "<yes|no> Determines if a selected song which is already playing or in the queue (duplicate song)\n" \
                                                           "                                      uses up a credit" };

constexpr char cfgKeyword_SelectButtons[]                { "SelectButtons" };
constexpr char cfgKeywordDesc_SelectButtons[]            { "List of characters for the select code for the button presses" };

constexpr char cfgKeyword_SelectButtonsSequence[]        { "SelectButtonsSequence" };
constexpr char cfgKeywordDesc_SelectButtonsSequence[]    { "<rowcol|colrow>\n" \
                                                           "                                      colrow : SelectButton sequences are cycled in order they are defined\n" \
                                                           "                                      rowcol : SelectButton sequences are cycled in reverse order they are defined" };
// constexpr char cfgKeyword_TouchDevice[]                  { "TouchDevice" };
// constexpr char cfgKeywordDesc_TouchDevice[]              { "Name of touch device (defaults to 'FT5406' - the official Raspberry Pi 7\" display)" };

// constexpr char cfgKeyword_MousePointer[]                 { "MousePointer" };
// constexpr char cfgKeywordDesc_MousePointer[]             { "<filename> of graphic image (bmp, png, tga, jpg, pcx).\n" \
                                                           // "                                      Specifying this enables mouse control" };
constexpr char cfgKeywordDesc_TouchEnable[]              { "<yes|no>\n" \
                                                           "                                      Yes : touch screen control is enabled" };

constexpr char cfgKeyword_TouchTopLeft[]                 { "TopLeft" };
constexpr char cfgKeywordDesc_TouchTopLeft[]             { "<x> <y> (the touch co-ordinates for top left of touch display)" };

constexpr char cfgKeyword_TouchBottomRight[]             { "BottomRight" };
constexpr char cfgKeywordDesc_TouchBottomRight[]         { "<x> <y> (the touch co-ordinates for bottom right of touch display)" };
// constexpr char cfgKeyword_InputDevice[]                  { "InputDevice" };
// constexpr char cfgKeywordDesc_InputDevice[]              { "Name of an input device.  Can be the full device name or part of the device name\n" \
                                                          // "                                      ('evtest' gives you this information) *Can be defined multiple times" };

constexpr char cfgKeyword_CustomMP3Tag[]                 { "CustomMP3Tag" };
constexpr char cfgKeywordDesc_CustomMP3Tag[]             { "<name> of an MP3 ID3v2 tag the user wishes to extract to a song's 'Custom' field (e.g. \"TCON\" is content type)\n" \
                                                          "                                      Note: this is only used during database file *creation*" };

constexpr char cfgKeyword_AutoSelect[]                   { "AutoSelect" };
constexpr char cfgKeywordDesc_AutoSelect[]               { "<yes|no>\n" \
                                                           "                                      No : Select button needs to be pressed to select song (after the select code is entered)\n" \
                                                           "                                      Yes : song selected immediately select code is entered" };

constexpr char cfgKeyword_InstantPlay[]                  { "InstantPlay" };
constexpr char cfgKeywordDesc_InstantPlay[]              { "<yes|no>\n" \
                                                           "                                      No : selected song is queued in the coming up list\n" \
                                                           "                                      Yes : selected is immediately played (and any currently playing song is stopped)" };

constexpr char cfgKeyword_ScreenJump[]                   { "ScreenJump" };
constexpr char cfgKeywordDesc_ScreenJump[]               { "<number> of screens of title strips moved in one go when 'LeftScreen' or 'RightScreen' button is pressed" };

constexpr char cfgKeyword_SelectTimeout[]                { "SelectTimeout" };
constexpr char cfgKeywordDesc_SelectTimeout[]            { "<time> [ticks|seconds|minutes|hours] Timeout for select code to return to undefined after not detecting all the selection digits" };

constexpr char cfgKeyword_SelectHoldTimeout[]            { "SelectHoldTimeout" };
constexpr char cfgKeywordDesc_SelectHoldTimeout[]        { "<time> [ticks|seconds|minutes|hours] Timeout for select code to return to undefined after song selected" };

constexpr char cfgKeyword_TitleStripAutoTurnTime[]       { "TitleStripAutoTurnTime" };
constexpr char cfgKeywordDesc_TitleStripAutoTurnTime[]   { "<time> [ticks|seconds|minutes|hours] Time between title_strips automatically turning (0 = no automatic title strip turn)" };

constexpr char cfgKeyword_MaxPlayQueueLength[]           { "MaxPlayQueueLength" };
constexpr char cfgKeywordDesc_MaxPlayQueueLength[]       { "<number> Maximum number of songs which can be stored in the coming up queue" };

constexpr char cfgKeyword_MenuColour[]                   { "MenuColour" };
constexpr char cfgKeywordDesc_MenuColour[]               { "<r> <g> <b> Modify the on-screen menu colour" };

constexpr char cfgKeyword_MenuBackgroundColour[]         { "MenuBackgroundColour" };
constexpr char cfgKeywordDesc_MenuBackgroundColour[]     { "<r> <g> <b> <a> Modify the on-screen menu background colour" };

constexpr char cfgKeyword_SkinChooserTimeout[]           { "SkinChooserTimeout" };
constexpr char cfgKeywordDesc_SkinChooserTimeout[]       { "<time> [ticks|seconds|minutes|hours] time before skin chooser starts current skin if no choice made\n" \
                                                           "                                      A value of zero or not defined disables timeout" };

constexpr char cfgKeyword_LoopPlayQueue[]                { "LoopPlayQueue" };
constexpr char cfgKeywordDesc_LoopPlayQueue[]            { "<yes|no>\n" \
                                                           "                                      Yes : a song is added to the back of the play queue when it has finished playing (credits permitting)\n" \
                                                           "                                      Note this option is ignored if the [general] NoDuplicates parameter is enabled in the skin configuration file" };

constexpr char cfgKeyword_IgnoreArtistPrefixThe[]        { "IgnoreArtistPrefixThe" };
constexpr char cfgKeywordDesc_IgnoreArtistPrefixThe[]    { "<yes|no>\n" \
                                                           "                                      Yes : ignore 'The ' beginning word in artist names" };


constexpr char cfgKeyword_AttractModeGenre[]             { "AttractModeGenre" };
constexpr char cfgKeywordDesc_AttractModeGenre[]         { "<name> of Genre.  Pressing AttractMode button will cycle through all AttractModeGenre definitions (and 'Off'\n" \
                                                           "                                      and 'Any') and only select a random song from that Genre **" };
constexpr char cfgKeyword_AttractModeEnable[]            { "Enable" };
constexpr char cfgKeywordDesc_AttractModeEnable[]        { "<yes|no>\n" \
                                                           "                                      Yes : a random song is played if the play queue is empty and no songs are playing" };
constexpr char cfgKeyword_AttractModeChoice[]            { "Choice" };
constexpr char cfgKeywordDesc_AttractModeChoice[]        { "<random|sorted>\n" \
                                                           "                                      Determines if the songs in attract mode are selected randomly or in the order in which they are sorted" };
constexpr char cfgKeyword_AttractModeInterval[]          { "Interval" };
constexpr char cfgKeywordDesc_AttractModeInterval[]      { "<time> [ticks|seconds|minutes|hours] The time between a random song being selected and played after the last song has finished playing" };

constexpr char cfgKeyword_AttractModeFadeIn[]            { "FadeIn" };
constexpr char cfgKeywordDesc_AttractModeFadeIn[]        { "<time> [ticks|seconds|minutes|hours] Length of fade in time of attract mode song (0 = no fade in)" };

constexpr char cfgKeyword_AttractModeFadeOut[]           { "FadeOut" };
constexpr char cfgKeywordDesc_AttractModeFadeOut[]       { "<time> [ticks|seconds|minutes|hours] Length of fade out time of attract mode song (0 = no fade out)" };

constexpr char cfgKeyword_AttractModeMaxVolume[]         { "MaxVolume" };
constexpr char cfgKeywordDesc_AttractModeMaxVolume[]     { "<0 to 100> Maximum volume of attract mode song (with respect to current volume level)" };

constexpr char cfgKeyword_AttractModeSkipLoad[]          { "SkipLoad" };
constexpr char cfgKeywordDesc_AttractModeSkipLoad[]      { "<yes|no>\n" \
                                                           "                                      Yes : attract mode songs don't invoke load / unload sequences" };

constexpr char cfgKeyword_AttractModeFadeInPosition[]       { "FadeInPosition" };
constexpr char cfgKeywordDesc_AttractModeFadeInPosition[]   { "<time> [ticks|seconds|minutes|hours] Start time of attract mode song" };

constexpr char cfgKeyword_AttractModeFadeOutPosition[]      { "FadeOutPosition" };
constexpr char cfgKeywordDesc_AttractModeFadeOutPosition[]  { "<time> [ticks|seconds|minutes|hours] Stop time of attract mode song" };

constexpr char cfgKeyword_FreePlay[]                     { "FreePlay" };
constexpr char cfgKeywordDesc_FreePlay[]                 { "<yes|no>\n" \
                                                           "                                      Yes : Credits/coins are not required to add a song to the play queue" };
constexpr char cfgKeyword_CreditsPerCoin1[]              { "CreditsPerCoin1" };
constexpr char cfgKeyword_CreditsPerCoin2[]              { "CreditsPerCoin2" };
constexpr char cfgKeyword_CreditsPerCoin3[]              { "CreditsPerCoin3" };
constexpr char cfgKeyword_CreditsPerCoin4[]              { "CreditsPerCoin4" };
constexpr char cfgKeyword_CreditsPerCoin5[]              { "CreditsPerCoin5" };
constexpr char cfgKeyword_CreditsPerCoin6[]              { "CreditsPerCoin6" };
constexpr char cfgKeywordDesc_CreditsPerCoin[]           { "<number> of song credits added when a coin is inserted" };

constexpr char cfgKeyword_CreditsPerSong[]               { "CreditsPerSong" };
constexpr char cfgKeywordDesc_CreditsPerSong[]           { "<number> of song credits required to play one song" };

constexpr char cfgKeyword_SongsPerTitleStrip[]           { "SongsPerTitleStrip" };
constexpr char cfgKeywordDesc_SongsPerTitleStrip[]       { "<number> of song entries on each song title strip" };
                                                       
constexpr char cfgKeyword_TitleStripSize[]               { "TitleStripSize" };
constexpr char cfgKeywordDesc_TitleStripSize[]           { "<width> <height> (in pixels) of each song title strip" };

constexpr char cfgKeyword_AlbumMode[]                    { "AlbumMode" };
constexpr char cfgKeywordDesc_AlbumMode[]                { "<yes|no>\n" \
                                                           "                                      Yes : Songs are grouped and selected by Album\n" \
                                                           "                                      No : Songs are selected individually\n" };

constexpr char cfgKeyword_PairSongs[]                    { "PairSongs" };
constexpr char cfgKeywordDesc_PairSongs[]                { "<yes|no|dual>\n" \
                                                           "                                      No : each song in a title strip is listed with its artist line\n" \
                                                           "                                      Yes : two songs are displayed (above and below) the artist line only if they are by the same artist\n" \
                                                           "                                      Dual : two songs are displayed (above and below) the artist line regardless of artist" };

constexpr char cfgKeyword_TitleStripMoveStyle[]          { "TitleStripMoveStyle" };
constexpr char cfgKeywordDesc_TitleStripMoveStyle[]      { "<effect> <speed> <fading>.  See section 'TitleStrips'" };

constexpr char cfgKeyword_SongDescription[]              { "SongDescription" };
constexpr char cfgKeywordDesc_SongDescription[]          { "<string> defining the song description for the song entry (first in a pair) in the title_strips.\n" \
                                                           "                                      Can contain a mixture of fixed text and reserved keywords\n" \
                                                           "                                      See 'TitleStrips section' for details." };

constexpr char cfgKeyword_PairedSongDescription[]        { "PairedSongDescription" };
constexpr char cfgKeywordDesc_PairedSongDescription[]    { "<string> defining the song description for the second song in a pair\n" \
                                                           "                                      NOTE: In Albums mode ([general] AlbumMode = yes) this determines the Album Title line" };

constexpr char cfgKeyword_ArtistDescription[]            { "ArtistDescription" };
constexpr char cfgKeywordDesc_ArtistDescription[]        { "<string> defining the artist description in the title_strips (same values as 'SongDescription')" };

constexpr char cfgKeyword_MatchedArtistDescription[]     { "MatchedArtistDescription" };
constexpr char cfgKeywordDesc_MatchedArtistDescription[] { "<string> used instead of 'ArtistDescription' if the artists of the songs in a pair are the same\n" \
                                                           "                                      (or the second song in a pair is absent)" };

constexpr char cfgKeyword_ExtraDescription[]             { "ExtraDescription" };
constexpr char cfgKeywordDesc_ExtraDescription[]         { "<string> defining the extra description in the title_strips (same values as 'SongDescription')\n" \
                                                           "                                      Note that each entry must have a corresponding \"ExtraText\" entry"};

constexpr char cfgKeyword_SongHistoryDepth[]             { "SongHistoryDepth" };
constexpr char cfgKeywordDesc_SongHistoryDepth[]         { "<number> Determines the search range of number of previously played songs to ensure\n" \
                                                           "                                      no repeated songs are chosen in Attract mode or Random selection.\n" \
                                                           "                                      If not specified or set to zero, fruitbox will only check for\n" \
                                                           "                                      repeated songs from within the play queue" };

constexpr char cfgKeyword_SongHistoryIncludeUserSelection[]             { "SongHistoryIncludeUserSelection" };
constexpr char cfgKeywordDesc_SongHistoryIncludeUserSelection[]         { "<yes|no> User selection is included or excluded from the history search" };

constexpr char cfgKeyword_SongLoadTime[]                 { "SongLoadTime" };
constexpr char cfgKeywordDesc_SongLoadTime[]             { "<time> [ticks|seconds|minutes|hours] the time the song takes to load (from removing from the coming up queue to starting to play)" };

constexpr char cfgKeyword_SongUnloadTime[]               { "SongUnloadTime" };
constexpr char cfgKeywordDesc_SongUnloadTime[]           { "<time> [ticks|seconds|minutes|hours] the time the song takes to unload (from finishing playing to the next song in the queue loading)" };

constexpr char cfgKeyword_SongText[]                     { "SongText" };
constexpr char cfgKeywordDesc_SongText[]                 { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n" \
                                                           "                                      Text style for Song title in song title strip. See section 'Fonts and Text'" };

constexpr char cfgKeyword_PairedSongText[]               { "PairedSongText" };
constexpr char cfgKeywordDesc_PairedSongText[]           { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n" \
                                                           "                                      Text style for the paired Song title in song title strip. See section 'Fonts and Text'" };

constexpr char cfgKeyword_ArtistText[]                   { "ArtistText" };
constexpr char cfgKeywordDesc_ArtistText[]               { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n" \
                                                           "                                      Text style for Artist name in song title strip. See section 'Fonts and Text'" };

constexpr char cfgKeyword_AlbumText[]                    { "AlbumText" };
constexpr char cfgKeywordDesc_AlbumText[]                { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n" \
                                                           "                                      Text style for Album name in song title strip. See section 'Fonts and Text'" };

constexpr char cfgKeyword_ExtraText[]                    { "ExtraText" };
constexpr char cfgKeywordDesc_ExtraText[]                { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n" \
                                                           "                                      Text style for the extra text field(s) in song title strip. See section 'Fonts and Text'\n" \
                                                           "                                      Note that this must be defined for each definition of \"ExtraDescription\"" };

constexpr char cfgKeyword_AlbumArtSize[]                 { "AlbumArtSize" };
constexpr char cfgKeywordDesc_AlbumArtSize[]             { "<width> <height> (in pixels)" };

constexpr char cfgKeyword_AlbumArtOffset[]               { "AlbumArtOffset" };
constexpr char cfgKeywordDesc_AlbumArtOffset[]           { "<x> <y> Offset from top left hand corner of songs title strip (in pixels)" };

constexpr char cfgKeyword_AlbumArtAngle[]                { "AlbumArtAngle" };
constexpr char cfgKeywordDesc_AlbumArtAngle[]            { "<angle> of Album artwork in degrees (0..359)" };

constexpr char cfgKeyword_NowPlayingMissingArtwork[]     { "NowPlayingMissingArtwork" };
constexpr char cfgKeywordDesc_NowPlayingMissingArtwork[] { "<filename> of graphic image (bmp, png, tga, jpg, pcx) to be used if NowPlayingArtworkMode = 'Specified',\n" \
                                                            "                                      or no song artwork is found and NowPlayingArtworkMode = 'Auto'" };

constexpr char cfgKeyword_AlbumModeMissingArtwork[]      { "AlbumModeMissingArtwork" };
constexpr char cfgKeywordDesc_AlbumModeMissingArtwork[]  { "<filename> of graphic image (bmp, png, tga, jpg, pcx) to be used if AlbumModeArtworkMode = 'Specified',\n" \
                                                           "                                      or no song artwork is found and AlbumModeArtworkMode = 'Auto'" };

constexpr char cfgKeyword_NowPlayingArtworkMode[]        { "NowPlayingArtworkMode" };
constexpr char cfgKeywordDesc_NowPlayingArtworkMode[]    { "<none|embedded|folder|specified|logo|a>\n" \
                                                           "                                      none : don't show artwork,\n" \
                                                           "                                      embedded : use image in MP3 file,\n" \
                                                           "                                      folder : use 'folder.jpg' in song directory,\n" \
                                                           "                                      specified : use MissingArtwork image,\n" \
                                                           "                                      logo : use fruitbox logo,\n" \
                                                           "                                      auto : use embedded/folder/missing/logo if available" };

constexpr char cfgKeyword_AlbumModeArtworkMode[]         { "AlbumModeArtworkMode" };
constexpr char cfgKeywordDesc_AlbumModeArtworkMode[]     { "<none|folder|specified|logo|auto>\n" \
                                                           "                                      none : don't show artwork,\n" \
                                                           "                                      folder : use 'folder.jpg' in song directory,\n" \
                                                           "                                      specified : use MissingArtwork image,\n" \
                                                           "                                      logo : use fruitbox logo,\n" \
                                                           "                                      auto : use folder/missing/logo if available" };

constexpr char cfgKeyword_SongVolume[]                   { "SongVolume" };
constexpr char cfgKeywordDesc_SongVolume[]               { "<volume> Initial song volume (0..100)" };

constexpr char cfgKeyword_SongVolumeStep[]               { "SongVolumeStep" };
constexpr char cfgKeywordDesc_SongVolumeStep[]           { "<step> Song volume step (0..100) (amount changed for VolumeUp / VolumeDown)" };

constexpr char cfgKeyword_ReplayGain[]                   { "ReplayGain" };
constexpr char cfgKeywordDesc_ReplayGain[]               { "<none|track|album> (automatic gain adjustment - requires MP3 ReplayGain tag data)" };

constexpr char cfgKeyword_Visible[]                      { "Visible" };
constexpr char cfgKeywordDesc_Visible[]                  { "<yes|no> (makes the object visible or invisible)" };
constexpr char cfgKeyword_Size[]                         { "Size" };
constexpr char cfgKeywordDesc_Size[]                     { "<width> <height> (in pixels)" };
constexpr char cfgKeywordDesc_SizeDynamic[]              { "<width> [dynamic] <height> [dynamic] (in pixels)" };
constexpr char cfgKeywordDesc_JoystickSize[]             { "<width> <height> (in pixels).  If not specified the size will be set to cover the song title exactly" };

constexpr char cfgKeyword_Position[]                     { "Position" };
constexpr char cfgKeywordDesc_Position[]                 { "<x> <y> (in pixels)" };
constexpr char cfgKeywordDesc_PositionDynamic[]          { "<x> [dynamic] <y> [dynamic] (in pixels)" };

constexpr char cfgKeyword_Clip[]                         { "Clip" };
constexpr char cfgKeywordDesc_Clip[]                     { "<x> <y> <width> <height> (in pixels)" };
constexpr char cfgKeywordDesc_ClipDynamic[]              { "<x> [dynamic] <y> [dynamic] <width> [dynamic] <height> [dynamic] (in pixels)" };

constexpr char cfgKeyword_Angle[]                        { "Angle" };
constexpr char cfgKeywordDesc_Angle[]                    { "<angle> of object in degrees (0..359)" };
constexpr char cfgKeywordDesc_AngleDynamic[]             { "<angle> [dynamic] of object in degrees (0..359)" };

constexpr char cfgKeyword_HorzFlip[]                     { "HorizontalFlip" };
constexpr char cfgKeywordDesc_HorzFlip[]                 { "<yes|no> flip object horizontally" };

constexpr char cfgKeyword_VertFlip[]                     { "VerticalFlip" };
constexpr char cfgKeywordDesc_VertFlip[]                 { "<yes|no> flip object vertically" };

constexpr char cfgKeyword_DynamicFlagEn[]                { "DynamicEnableFlag" };
constexpr char cfgKeywordDesc_DynamicFlagEn[]            { "<1..4> enable dynamic parameters using status flag 1..4" };

constexpr char cfgKeyword_Tint[]                         { "Tint" };
constexpr char cfgKeywordDesc_Tint[]                     { "<r> <g> <b> <a> (modify the objects colour)" };
constexpr char cfgKeywordDesc_TintDynamic[]              { "<r> [dynamic] <g> [dynamic] <b> [dynamic] <a> [dynamic] (modify the objects colour)" };

constexpr char cfgKeyword_Offset[]                       { "Offset" };
constexpr char cfgKeyword_HotSpot[]                      { "HotSpot" };
constexpr char cfgKeywordDesc_JoystickOffset[]           { "<x> <y> (offset in pixels from top left corner of joystick highlight in song title region)" };
constexpr char cfgKeywordDesc_TouchSongOffset[]          { "<x> <y> (offset in pixels from top left corner of song touch highlight in song title region)" };
constexpr char cfgKeywordDesc_MouseHotSpot[]             { "<x> <y> (offset in pixels from top left corner of mouse pointer which corresponds to the click position)" };

constexpr char cfgKeyword_HideAfter[]                    { "HideAfter" };
constexpr char cfgKeywordDesc_HideAfter[]                { "<time> [ticks|seconds|minutes|hours] (Hide inactive mouse pointer after this time. 0 = don't hide)" };

constexpr char cfgKeyword_Contents[]                     { "Contents" };
constexpr char cfgKeywordDesc_Contents[]                 { "<filename> of text file describing status box contents" };

constexpr char cfgKeyword_Enable[]                       { "Enable" };
constexpr char cfgKeyword_DisableTitleStripFlip[]        { "DisableTitleStripFlip" };

constexpr char cfgKeywordDesc_JoystickEnable[]           { "<yes|no>\n" \
                                                           "                                      Yes : joystick control is enabled" };

constexpr char cfgKeywordDesc_DisableTitleStripFlip[]    { "<yes|no>\n" \
                                                           "                                      Yes : Title Strip flipping is prevented using left/right in joystick mode" };

constexpr char cfgKeywordDesc_MouseEnable[]              { "<yes|no>\n" \
                                                           "                                      Yes : mouse control is enabled" };
constexpr char cfgKeyword_MouseSensitivity[]             { "Sensitivity" };
constexpr char cfgKeywordDesc_MouseSensitivity[]         { "<0.0 .. > sensitivity of mouse movement (1.0 nominal, higher is more sensitive)" };

constexpr char cfgKeyword_Output[]                       { "Output" };
constexpr char cfgKeywordDesc_Output[]                   { "<filename> of output text file containing status" };

constexpr char cfgKeyword_LineSpacing[]                  { "LineSpacing" };
constexpr char cfgKeywordDesc_StatusLineSpacing[]        { "<gap> (in pixels) between text lines in the status box" };

constexpr char cfgKeyword_LoopVideo[]                    { "LoopVideo" };
constexpr char cfgKeywordDesc_LoopVideo[]                { "<yes|no> start video from beginning after it finishes" };

constexpr char cfgKeyword_AlbumModeLineSpacing[]         { "AlbumModeLineSpacing" };
constexpr char cfgKeywordDesc_AlbumModeLineSpacing[]     { "<gap> (in pixels) between song titles in the albums song title_strips" };

constexpr char cfgKeyword_BitmapDirectory[]              { "BitmapDirectory" };
constexpr char cfgKeywordDesc_BitmapDirectory[]          { "<location> of image files (bmp, jpg, png)" };

constexpr char cfgKeyword_TimerTickPeriod[]              { "TimerTickPeriod" };
constexpr char cfgKeywordDesc_TimerTickPeriod[]          { "<time> (in video frame ticks) of status box timer period" };

constexpr char cfgKeyword_TimerOneShot[]                 { "TimerOneShot" };
constexpr char cfgKeywordDesc_TimerOneShot[]             { "<yes|no>\n" \
                                                           "                                      Yes : timer stops after one tick\n" \
                                                           "                                      No : timer runs indefinitely (default)" };

constexpr char cfgKeyword_TimerEnable[]                  { "TimerEnable" };
constexpr char cfgKeywordDesc_TimerEnable[]              { "<yes|no>\n" \
                                                           "                                      Yes : timer initially enabled (default)\n" \
                                                           "                                      No : timer initially disabled)" };

constexpr char cfgKeyword_Text[]                         { "Text" };
constexpr char cfgKeywordDesc_Text[]                     { "<font> <colour (r g b a)> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>" };

constexpr char cfgKeywordDesc_TouchSongBitmap[]          { "<filename> of graphic image (bmp, png, tga, jpg, pcx).\n" \
                                                           "                                      Image to overlay on title strip song name when touched\n" \
                                                           "                                      Note: Defining this parameter will enable touch song mode"};

constexpr char cfgKeyword_Bitmap[]                       { "Bitmap" };
constexpr char cfgKeywordDesc_Bitmap[]                   { "<filename> of graphic image (bmp, png, tga, jpg, pcx)" };

constexpr char cfgKeyword_Video[]                        { "Video" };
constexpr char cfgKeywordDesc_Video[]                    { "<filename> of video clip (ogv)" };

constexpr char cfgKeyword_Sound[]                        { "Sound" };
constexpr char cfgKeywordDesc_Sound[]                    { "<filename> of sound effect (wav, flac, ogg) <volume (0..100)> [loop (Yes|No)]" };

constexpr char cfgKeyword_Title[]                        { "Title" };

constexpr char cfgKeyword_File[]                         { "File" };
constexpr char cfgKeywordDesc_SkinFile[]                 { "<filename> of skin configuration file" };

constexpr char cfgKeywordDesc_Font[]                     { "<filename> <height> font to add to the font pool (ttf, opentype, type1, CID, CFF, fon, fnt, x11, pcf)" };

constexpr char cfgKeyword_TitleStripBackground[]         { "TitleStripBackground" };
constexpr char cfgKeywordDesc_TitleStripBackground[]     { "<filename> [genre]\n" \
                                                           "                                      Filename of graphic image (bmp, png, tga, jpg, pcx) to be used as the title strip background\n" \
                                                           "                                      Optional Genre string is name of genre specific title strip background" };

constexpr char cfgKeyword_MoveDelay[]                    { "MoveDelay" };
constexpr char cfgKeywordDesc_MoveDelay[]                { "<delay> (in video frame ticks) between left/right button press and title strip moving" };

constexpr char cfgKeyword_MoveReverse[]                  { "MoveReverse" };
constexpr char cfgKeywordDesc_MoveReverse[]              { "<yes|no> reverse the direction of the title strip movement" };

constexpr char cfgKeyword_AudioOnlyClip[]                { "AudioOnlyClip" };
constexpr char cfgKeywordDesc_AudioOnlyClip[]            { "<filename> of video (ogv) to be played for audio only music files" };
constexpr char cfgKeyword_IdleClip[]                     { "IdleClip" };
constexpr char cfgKeywordDesc_IdleClip[]                 { "<filename> of video (ogv) to be played when no music playing" };

constexpr char cfgKeywordDesc_SpectrumAnalyserBitmap[]   { "<filename> of band(s) graphic image (bmp, png, tga, jpg, pcx)" };
constexpr char cfgKeyword_SpectrumAnalyserBand[]         { "Band" };
constexpr char cfgKeywordDesc_SpectrumAnalyserBand[]     { "<number (0..31)> [gain (1.0 nominal)] [offset (x y)] [tint (r g b a)] of visible frequency band\n" \
                                                           "                                      Note: the tint is applied in addition to the global [spectrum] Tint" };
constexpr char cfgKeyword_SpectrumAnalyserMode[]         { "Mode" };
constexpr char cfgKeywordDesc_SpectrumAnalyserMode[]     { "<scaled|clipped|position> bitmap draw mode" };
constexpr char cfgKeyword_SpectrumAnalyserChannel[]      { "Channel" };
constexpr char cfgKeywordDesc_SpectrumAnalyserChannel[]  { "<left|right|both>" };
constexpr char cfgKeyword_SpectrumAnalyserDecay[]        { "Decay" };
constexpr char cfgKeywordDesc_SpectrumAnalyserDecay[]    { "<value> speed of peak decay (0=instant)" };

constexpr char cfgKeyword_ButtonQuit[]                   { "Quit" };         constexpr char menuLabel_ButtonQuit[]                   { "-" };
constexpr char cfgKeyword_ButtonMenu[]                   { "Menu" };         constexpr char menuLabel_ButtonMenu[]                   { "-" };
constexpr char cfgKeyword_ButtonSearch[]                 { "Search" };       constexpr char menuLabel_ButtonSearch[]                 { "-" };
constexpr char cfgKeyword_ButtonMouse[]                  { "Mouse" };        constexpr char menuLabel_ButtonMouse[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin1[]                  { "Coin1" };        constexpr char menuLabel_ButtonCoin1[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin2[]                  { "Coin2" };        constexpr char menuLabel_ButtonCoin2[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin3[]                  { "Coin3" };        constexpr char menuLabel_ButtonCoin3[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin4[]                  { "Coin4" };        constexpr char menuLabel_ButtonCoin4[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin5[]                  { "Coin5" };        constexpr char menuLabel_ButtonCoin5[]                  { "-" };
constexpr char cfgKeyword_ButtonCoin6[]                  { "Coin6" };        constexpr char menuLabel_ButtonCoin6[]                  { "-" };
constexpr char cfgKeyword_ButtonVolUp[]                  { "VolUp" };        constexpr char menuLabel_ButtonVolUp[]                  { "-" };
constexpr char cfgKeyword_ButtonVolDown[]                { "VolDown" };      constexpr char menuLabel_ButtonVolDown[]                { "-" };
constexpr char cfgKeyword_ButtonRandom[]                 { "Random" };       constexpr char menuLabel_ButtonRandom[]                 { "-" };
constexpr char cfgKeyword_ButtonSelect[]                 { "Select" };       constexpr char menuLabel_ButtonSelect[]                 { "-" };
constexpr char cfgKeyword_ButtonSkip[]                   { "Skip" };         constexpr char menuLabel_ButtonSkip[]                   { "-" };
constexpr char cfgKeyword_ButtonPause[]                  { "Pause" };        constexpr char menuLabel_ButtonPause[]                  { "-" };
constexpr char cfgKeyword_ButtonUp[]                     { "Up" };           constexpr char menuLabel_ButtonUp[]                     { "Up" };
constexpr char cfgKeyword_ButtonDown[]                   { "Down" };         constexpr char menuLabel_ButtonDown[]                   { "Down" };
constexpr char cfgKeyword_ButtonLeft[]                   { "Left" };         constexpr char menuLabel_ButtonLeft[]                   { "Left" };
constexpr char cfgKeyword_ButtonRight[]                  { "Right" };        constexpr char menuLabel_ButtonRight[]                  { "Right" };
constexpr char cfgKeyword_ButtonLeftScreen[]             { "LeftScreen" };   constexpr char menuLabel_ButtonLeftScreen[]             { "-" };
constexpr char cfgKeyword_ButtonRightScreen[]            { "RightScreen" };  constexpr char menuLabel_ButtonRightScreen[]            { "-" };
constexpr char cfgKeyword_ButtonLeftSort[]               { "LeftSort" };     constexpr char menuLabel_ButtonLeftSort[]               { "-" };
constexpr char cfgKeyword_ButtonRightSort[]              { "RightSort" };    constexpr char menuLabel_ButtonRightSort[]              { "-" };
constexpr char cfgKeyword_ButtonAuto[]                   { "AttractMode" };  constexpr char menuLabel_ButtonAuto[]                   { "-" };
constexpr char cfgKeyword_ButtonLoop[]                   { "LoopQueue" };    constexpr char menuLabel_ButtonLoop[]                   { "-" };
constexpr char cfgKeyword_ButtonFree[]                   { "FreePlay" };     constexpr char menuLabel_ButtonFree[]                   { "-" };
constexpr char cfgKeyword_ButtonClear[]                  { "ClearQueue" };   constexpr char menuLabel_ButtonClear[]                  { "-" };
constexpr char cfgKeyword_ButtonMute[]                   { "Mute" };         constexpr char menuLabel_ButtonMute[]                   { "-" };
constexpr char cfgKeyword_ButtonPowerOff[]               { "PowerOff" };     constexpr char menuLabel_ButtonPowerOff[]               { "-" };
constexpr char cfgKeyword_ButtonSelect0[]                { "Select0" };      constexpr char menuLabel_ButtonSelect0[]                { "0" };
constexpr char cfgKeyword_ButtonSelect1[]                { "Select1" };      constexpr char menuLabel_ButtonSelect1[]                { "1" };
constexpr char cfgKeyword_ButtonSelect2[]                { "Select2" };      constexpr char menuLabel_ButtonSelect2[]                { "2" };
constexpr char cfgKeyword_ButtonSelect3[]                { "Select3" };      constexpr char menuLabel_ButtonSelect3[]                { "3" };
constexpr char cfgKeyword_ButtonSelect4[]                { "Select4" };      constexpr char menuLabel_ButtonSelect4[]                { "4" };
constexpr char cfgKeyword_ButtonSelect5[]                { "Select5" };      constexpr char menuLabel_ButtonSelect5[]                { "5" };
constexpr char cfgKeyword_ButtonSelect6[]                { "Select6" };      constexpr char menuLabel_ButtonSelect6[]                { "6" };
constexpr char cfgKeyword_ButtonSelect7[]                { "Select7" };      constexpr char menuLabel_ButtonSelect7[]                { "7" };
constexpr char cfgKeyword_ButtonSelect8[]                { "Select8" };      constexpr char menuLabel_ButtonSelect8[]                { "8" };
constexpr char cfgKeyword_ButtonSelect9[]                { "Select9" };      constexpr char menuLabel_ButtonSelect9[]                { "9" };
constexpr char cfgKeyword_ButtonSelectA[]                { "SelectA" };      constexpr char menuLabel_ButtonSelectA[]                { "A" };
constexpr char cfgKeyword_ButtonSelectB[]                { "SelectB" };      constexpr char menuLabel_ButtonSelectB[]                { "B" };
constexpr char cfgKeyword_ButtonSelectC[]                { "SelectC" };      constexpr char menuLabel_ButtonSelectC[]                { "C" };
constexpr char cfgKeyword_ButtonSelectD[]                { "SelectD" };      constexpr char menuLabel_ButtonSelectD[]                { "D" };
constexpr char cfgKeyword_ButtonSelectE[]                { "SelectE" };      constexpr char menuLabel_ButtonSelectE[]                { "E" };
constexpr char cfgKeyword_ButtonSelectF[]                { "SelectF" };      constexpr char menuLabel_ButtonSelectF[]                { "F" };
constexpr char cfgKeyword_ButtonSelectG[]                { "SelectG" };      constexpr char menuLabel_ButtonSelectG[]                { "G" };
constexpr char cfgKeyword_ButtonSelectH[]                { "SelectH" };      constexpr char menuLabel_ButtonSelectH[]                { "H" };
constexpr char cfgKeyword_ButtonSelectI[]                { "SelectI" };      constexpr char menuLabel_ButtonSelectI[]                { "I" };
constexpr char cfgKeyword_ButtonSelectJ[]                { "SelectJ" };      constexpr char menuLabel_ButtonSelectJ[]                { "J" };
constexpr char cfgKeyword_ButtonSelectK[]                { "SelectK" };      constexpr char menuLabel_ButtonSelectK[]                { "K" };
constexpr char cfgKeyword_ButtonSelectL[]                { "SelectL" };      constexpr char menuLabel_ButtonSelectL[]                { "L" };
constexpr char cfgKeyword_ButtonSelectM[]                { "SelectM" };      constexpr char menuLabel_ButtonSelectM[]                { "M" };
constexpr char cfgKeyword_ButtonSelectN[]                { "SelectN" };      constexpr char menuLabel_ButtonSelectN[]                { "N" };
constexpr char cfgKeyword_ButtonSelectO[]                { "SelectO" };      constexpr char menuLabel_ButtonSelectO[]                { "O" };
constexpr char cfgKeyword_ButtonSelectP[]                { "SelectP" };      constexpr char menuLabel_ButtonSelectP[]                { "P" };
constexpr char cfgKeyword_ButtonSelectQ[]                { "SelectQ" };      constexpr char menuLabel_ButtonSelectQ[]                { "Q" };
constexpr char cfgKeyword_ButtonSelectR[]                { "SelectR" };      constexpr char menuLabel_ButtonSelectR[]                { "R" };
constexpr char cfgKeyword_ButtonSelectS[]                { "SelectS" };      constexpr char menuLabel_ButtonSelectS[]                { "S" };
constexpr char cfgKeyword_ButtonSelectT[]                { "SelectT" };      constexpr char menuLabel_ButtonSelectT[]                { "T" };
constexpr char cfgKeyword_ButtonSelectU[]                { "SelectU" };      constexpr char menuLabel_ButtonSelectU[]                { "U" };
constexpr char cfgKeyword_ButtonSelectV[]                { "SelectV" };      constexpr char menuLabel_ButtonSelectV[]                { "V" };
constexpr char cfgKeyword_ButtonSelectW[]                { "SelectW" };      constexpr char menuLabel_ButtonSelectW[]                { "W" };
constexpr char cfgKeyword_ButtonSelectX[]                { "SelectX" };      constexpr char menuLabel_ButtonSelectX[]                { "X" };
constexpr char cfgKeyword_ButtonSelectY[]                { "SelectY" };      constexpr char menuLabel_ButtonSelectY[]                { "Y" };
constexpr char cfgKeyword_ButtonSelectZ[]                { "SelectZ" };      constexpr char menuLabel_ButtonSelectZ[]                { "Z" };
constexpr char cfgKeyword_ButtonFlag1[]                  { "Flag1" };        constexpr char menuLabel_ButtonFlag1[]                  { "-" };
constexpr char cfgKeyword_ButtonFlag2[]                  { "Flag2" };        constexpr char menuLabel_ButtonFlag2[]                  { "-" };
constexpr char cfgKeyword_ButtonFlag3[]                  { "Flag3" };        constexpr char menuLabel_ButtonFlag3[]                  { "-" };
constexpr char cfgKeyword_ButtonFlag4[]                  { "Flag4" };        constexpr char menuLabel_ButtonFlag4[]                  { "-" };
constexpr char cfgKeyword_ButtonScreenshot[]             { "Screenshot" };   constexpr char menuLabel_ButtonScreenshot[]             { "-" };

constexpr char cfgKeywordDesc_ButtonQuit[]               { "<name> of button (quit fruitbox)" };
constexpr char cfgKeywordDesc_ButtonMenu[]               { "<name> of button (fruitbox menu)" };
constexpr char cfgKeywordDesc_ButtonSearch[]             { "<name> of button (song search/filter)" };
constexpr char cfgKeywordDesc_ButtonMouse[]              { "<name> of button (mouse select)" };
constexpr char cfgKeywordDesc_ButtonInsertCoin[]         { "<name> of button (insert coin)" };
constexpr char cfgKeywordDesc_ButtonVolume[]             { "<name> of button (change volume)" };
constexpr char cfgKeywordDesc_ButtonRandom[]             { "<name> of button (select random song)" };
constexpr char cfgKeywordDesc_ButtonSelect[]             { "<name> of button (play selected song)" };
constexpr char cfgKeywordDesc_ButtonSkip[]               { "<name> of button (stop current song)" };
constexpr char cfgKeywordDesc_ButtonPause[]              { "<name> of button (pause/unpause currently playing song)" };
constexpr char cfgKeywordDesc_ButtonDirections[]         { "<name> of button (move title_strips/joystick selector)" };
constexpr char cfgKeywordDesc_ButtonScreenDirections[]   { "<name> of button (move title_strips by 'ScreenJump' amount)" };
constexpr char cfgKeywordDesc_ButtonSortDirections[]     { "<name> of button (move title_strips by last 'SortSongsBy' value)" };
constexpr char cfgKeywordDesc_ButtonDirectionsJoy[]      { "<name> of button (joystick selector)" };
constexpr char cfgKeywordDesc_ButtonAuto[]               { "<name> of button (toggle Attract mode)" };
constexpr char cfgKeywordDesc_ButtonLoop[]               { "<name> of button (toggle Loop mode)" };
constexpr char cfgKeywordDesc_ButtonFree[]               { "<name> of button (toggle Freeplay mode)" };
constexpr char cfgKeywordDesc_ButtonClear[]              { "<name> of button (empty play queue)" };
constexpr char cfgKeywordDesc_ButtonMute[]               { "<name> of button (volume mute)" };
constexpr char cfgKeywordDesc_ButtonSongSelect[]         { "<name> of button (song selection)" };
constexpr char cfgKeywordDesc_ButtonFlag[]               { "<name> of button (toggle status flag)" };
constexpr char cfgKeywordDesc_ButtonPowerOff[]           { "<name> of button (power off)" };
constexpr char cfgKeywordDesc_ButtonScreenshot[]         { "<name> of button (take screenshot)" };

constexpr char cfgKeyword_ButtonTouchArea[]              { "<x> <y> <width> <height> [bitmap] (touch area of button, optional bitmap to draw when touched)" };

constexpr char dynamicParameterStartStr[]                 { "[" };
constexpr char dynamicParameterStopStr[]                  { "]" };
// const array<default_button_t, 2> default_button
const default_button_t default_button[NUM_BUTTONS] =
{
  {BUTTON_QUIT          , cfgKeyword_ButtonQuit        , cfgKeywordDesc_ButtonQuit             , KEY_ESC         , menuLabel_ButtonQuit        },
  {BUTTON_INSERT_COIN1  , cfgKeyword_ButtonCoin1       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F1          , menuLabel_ButtonCoin1       },
  {BUTTON_INSERT_COIN2  , cfgKeyword_ButtonCoin2       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F2          , menuLabel_ButtonCoin2       },
  {BUTTON_INSERT_COIN3  , cfgKeyword_ButtonCoin3       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F3          , menuLabel_ButtonCoin3       },
  {BUTTON_INSERT_COIN4  , cfgKeyword_ButtonCoin4       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F4          , menuLabel_ButtonCoin4       },
  {BUTTON_INSERT_COIN5  , cfgKeyword_ButtonCoin5       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F5          , menuLabel_ButtonCoin5       },
  {BUTTON_INSERT_COIN6  , cfgKeyword_ButtonCoin6       , cfgKeywordDesc_ButtonInsertCoin       , KEY_F6          , menuLabel_ButtonCoin6       },
  {BUTTON_VOL_UP        , cfgKeyword_ButtonVolUp       , cfgKeywordDesc_ButtonVolume           , KEY_EQUAL       , menuLabel_ButtonVolUp       },
  {BUTTON_VOL_DOWN      , cfgKeyword_ButtonVolDown     , cfgKeywordDesc_ButtonVolume           , KEY_MINUS       , menuLabel_ButtonVolDown     },
  {BUTTON_ADD_RANDOM    , cfgKeyword_ButtonRandom      , cfgKeywordDesc_ButtonRandom           , KEY_SPACE       , menuLabel_ButtonRandom      },
  {BUTTON_SELECT        , cfgKeyword_ButtonSelect      , cfgKeywordDesc_ButtonSelect           , KEY_ENTER       , menuLabel_ButtonSelect      },
  {BUTTON_SKIP          , cfgKeyword_ButtonSkip        , cfgKeywordDesc_ButtonSkip             , KEY_BACKSPACE   , menuLabel_ButtonSkip        },
  {BUTTON_PAUSE         , cfgKeyword_ButtonPause       , cfgKeywordDesc_ButtonPause            , KEY_SEMICOLON   , menuLabel_ButtonPause       },
  {BUTTON_UP            , cfgKeyword_ButtonUp          , cfgKeywordDesc_ButtonDirectionsJoy    , KEY_UP          , menuLabel_ButtonUp          },
  {BUTTON_DOWN          , cfgKeyword_ButtonDown        , cfgKeywordDesc_ButtonDirectionsJoy    , KEY_DOWN        , menuLabel_ButtonDown        },
  {BUTTON_LEFT          , cfgKeyword_ButtonLeft        , cfgKeywordDesc_ButtonDirections       , KEY_LEFT        , menuLabel_ButtonLeft        },
  {BUTTON_RIGHT         , cfgKeyword_ButtonRight       , cfgKeywordDesc_ButtonDirections       , KEY_RIGHT       , menuLabel_ButtonRight       },
  {BUTTON_LEFT_SCREEN   , cfgKeyword_ButtonLeftScreen  , cfgKeywordDesc_ButtonScreenDirections , KEY_LEFTBRACE   , menuLabel_ButtonLeftScreen  },
  {BUTTON_RIGHT_SCREEN  , cfgKeyword_ButtonRightScreen , cfgKeywordDesc_ButtonScreenDirections , KEY_RIGHTBRACE  , menuLabel_ButtonRightScreen },
  {BUTTON_LEFT_SORT     , cfgKeyword_ButtonLeftSort    , cfgKeywordDesc_ButtonSortDirections   , KEY_COMMA       , menuLabel_ButtonLeftSort    },
  {BUTTON_RIGHT_SORT    , cfgKeyword_ButtonRightSort   , cfgKeywordDesc_ButtonSortDirections   , KEY_DOT         , menuLabel_ButtonRightSort   },
  {BUTTON_ATTRACT_TOG   , cfgKeyword_ButtonAuto        , cfgKeywordDesc_ButtonAuto             , KEY_APOSTROPHE  , menuLabel_ButtonAuto        },
  {BUTTON_LOOPQUEUE_TOG , cfgKeyword_ButtonLoop        , cfgKeywordDesc_ButtonLoop             , KEY_F11         , menuLabel_ButtonLoop        },
  {BUTTON_FREEPLAY_TOG  , cfgKeyword_ButtonFree        , cfgKeywordDesc_ButtonFree             , KEY_F12         , menuLabel_ButtonFree        },
  {BUTTON_CLEARQUEUE    , cfgKeyword_ButtonClear       , cfgKeywordDesc_ButtonClear            , KEY_DELETE      , menuLabel_ButtonClear       },
  {BUTTON_MUTE          , cfgKeyword_ButtonMute        , cfgKeywordDesc_ButtonMute             , KEY_LEFTCTRL    , menuLabel_ButtonMute        },
  {BUTTON_POWER_OFF     , cfgKeyword_ButtonPowerOff    , cfgKeywordDesc_ButtonPowerOff         , KEY_SYSRQ       , menuLabel_ButtonPowerOff    },
  {BUTTON_0             , cfgKeyword_ButtonSelect0     , cfgKeywordDesc_ButtonSongSelect       , KEY_0           , menuLabel_ButtonSelect0     },
  {BUTTON_1             , cfgKeyword_ButtonSelect1     , cfgKeywordDesc_ButtonSongSelect       , KEY_1           , menuLabel_ButtonSelect1     },
  {BUTTON_2             , cfgKeyword_ButtonSelect2     , cfgKeywordDesc_ButtonSongSelect       , KEY_2           , menuLabel_ButtonSelect2     },
  {BUTTON_3             , cfgKeyword_ButtonSelect3     , cfgKeywordDesc_ButtonSongSelect       , KEY_3           , menuLabel_ButtonSelect3     },
  {BUTTON_4             , cfgKeyword_ButtonSelect4     , cfgKeywordDesc_ButtonSongSelect       , KEY_4           , menuLabel_ButtonSelect4     },
  {BUTTON_5             , cfgKeyword_ButtonSelect5     , cfgKeywordDesc_ButtonSongSelect       , KEY_5           , menuLabel_ButtonSelect5     },
  {BUTTON_6             , cfgKeyword_ButtonSelect6     , cfgKeywordDesc_ButtonSongSelect       , KEY_6           , menuLabel_ButtonSelect6     },
  {BUTTON_7             , cfgKeyword_ButtonSelect7     , cfgKeywordDesc_ButtonSongSelect       , KEY_7           , menuLabel_ButtonSelect7     },
  {BUTTON_8             , cfgKeyword_ButtonSelect8     , cfgKeywordDesc_ButtonSongSelect       , KEY_8           , menuLabel_ButtonSelect8     },
  {BUTTON_9             , cfgKeyword_ButtonSelect9     , cfgKeywordDesc_ButtonSongSelect       , KEY_9           , menuLabel_ButtonSelect9     },
  {BUTTON_A             , cfgKeyword_ButtonSelectA     , cfgKeywordDesc_ButtonSongSelect       , KEY_A           , menuLabel_ButtonSelectA     },
  {BUTTON_B             , cfgKeyword_ButtonSelectB     , cfgKeywordDesc_ButtonSongSelect       , KEY_B           , menuLabel_ButtonSelectB     },
  {BUTTON_C             , cfgKeyword_ButtonSelectC     , cfgKeywordDesc_ButtonSongSelect       , KEY_C           , menuLabel_ButtonSelectC     },
  {BUTTON_D             , cfgKeyword_ButtonSelectD     , cfgKeywordDesc_ButtonSongSelect       , KEY_D           , menuLabel_ButtonSelectD     },
  {BUTTON_E             , cfgKeyword_ButtonSelectE     , cfgKeywordDesc_ButtonSongSelect       , KEY_E           , menuLabel_ButtonSelectE     },
  {BUTTON_F             , cfgKeyword_ButtonSelectF     , cfgKeywordDesc_ButtonSongSelect       , KEY_F           , menuLabel_ButtonSelectF     },
  {BUTTON_G             , cfgKeyword_ButtonSelectG     , cfgKeywordDesc_ButtonSongSelect       , KEY_G           , menuLabel_ButtonSelectG     },
  {BUTTON_H             , cfgKeyword_ButtonSelectH     , cfgKeywordDesc_ButtonSongSelect       , KEY_H           , menuLabel_ButtonSelectH     },
  {BUTTON_I             , cfgKeyword_ButtonSelectI     , cfgKeywordDesc_ButtonSongSelect       , KEY_I           , menuLabel_ButtonSelectI     },
  {BUTTON_J             , cfgKeyword_ButtonSelectJ     , cfgKeywordDesc_ButtonSongSelect       , KEY_J           , menuLabel_ButtonSelectJ     },
  {BUTTON_K             , cfgKeyword_ButtonSelectK     , cfgKeywordDesc_ButtonSongSelect       , KEY_K           , menuLabel_ButtonSelectK     },
  {BUTTON_L             , cfgKeyword_ButtonSelectL     , cfgKeywordDesc_ButtonSongSelect       , KEY_L           , menuLabel_ButtonSelectL     },
  {BUTTON_M             , cfgKeyword_ButtonSelectM     , cfgKeywordDesc_ButtonSongSelect       , KEY_M           , menuLabel_ButtonSelectM     },
  {BUTTON_N             , cfgKeyword_ButtonSelectN     , cfgKeywordDesc_ButtonSongSelect       , KEY_N           , menuLabel_ButtonSelectN     },
  {BUTTON_O             , cfgKeyword_ButtonSelectO     , cfgKeywordDesc_ButtonSongSelect       , KEY_O           , menuLabel_ButtonSelectO     },
  {BUTTON_P             , cfgKeyword_ButtonSelectP     , cfgKeywordDesc_ButtonSongSelect       , KEY_P           , menuLabel_ButtonSelectP     },
  {BUTTON_Q             , cfgKeyword_ButtonSelectQ     , cfgKeywordDesc_ButtonSongSelect       , KEY_Q           , menuLabel_ButtonSelectQ     },
  {BUTTON_R             , cfgKeyword_ButtonSelectR     , cfgKeywordDesc_ButtonSongSelect       , KEY_R           , menuLabel_ButtonSelectR     },
  {BUTTON_S             , cfgKeyword_ButtonSelectS     , cfgKeywordDesc_ButtonSongSelect       , KEY_S           , menuLabel_ButtonSelectS     },
  {BUTTON_T             , cfgKeyword_ButtonSelectT     , cfgKeywordDesc_ButtonSongSelect       , KEY_T           , menuLabel_ButtonSelectT     },
  {BUTTON_U             , cfgKeyword_ButtonSelectU     , cfgKeywordDesc_ButtonSongSelect       , KEY_U           , menuLabel_ButtonSelectU     },
  {BUTTON_V             , cfgKeyword_ButtonSelectV     , cfgKeywordDesc_ButtonSongSelect       , KEY_V           , menuLabel_ButtonSelectV     },
  {BUTTON_W             , cfgKeyword_ButtonSelectW     , cfgKeywordDesc_ButtonSongSelect       , KEY_W           , menuLabel_ButtonSelectW     },
  {BUTTON_X             , cfgKeyword_ButtonSelectX     , cfgKeywordDesc_ButtonSongSelect       , KEY_X           , menuLabel_ButtonSelectX     },
  {BUTTON_Y             , cfgKeyword_ButtonSelectY     , cfgKeywordDesc_ButtonSongSelect       , KEY_Y           , menuLabel_ButtonSelectY     },
  {BUTTON_Z             , cfgKeyword_ButtonSelectZ     , cfgKeywordDesc_ButtonSongSelect       , KEY_Z           , menuLabel_ButtonSelectZ     },
  {BUTTON_FLAG_1        , cfgKeyword_ButtonFlag1       , cfgKeywordDesc_ButtonFlag             , KEY_F7          , menuLabel_ButtonFlag1       },
  {BUTTON_FLAG_2        , cfgKeyword_ButtonFlag2       , cfgKeywordDesc_ButtonFlag             , KEY_F8          , menuLabel_ButtonFlag2       },
  {BUTTON_FLAG_3        , cfgKeyword_ButtonFlag3       , cfgKeywordDesc_ButtonFlag             , KEY_F9          , menuLabel_ButtonFlag3       },
  {BUTTON_FLAG_4        , cfgKeyword_ButtonFlag4       , cfgKeywordDesc_ButtonFlag             , KEY_F10         , menuLabel_ButtonFlag4       },
  {BUTTON_MENU          , cfgKeyword_ButtonMenu        , cfgKeywordDesc_ButtonMenu             , KEY_TAB         , menuLabel_ButtonMenu        },
  {BUTTON_SEARCH        , cfgKeyword_ButtonSearch      , cfgKeywordDesc_ButtonSearch           , KEY_SLASH       , menuLabel_ButtonSearch      },
  {BUTTON_MOUSE         , cfgKeyword_ButtonMouse       , cfgKeywordDesc_ButtonMouse            , BTN_LEFT        , menuLabel_ButtonMouse       },
  {BUTTON_SCREENSHOT    , cfgKeyword_ButtonScreenshot  , cfgKeywordDesc_ButtonScreenshot       , KEY_RIGHTCTRL   , menuLabel_ButtonScreenshot  }
};

class ReadBool
{
public:
  ReadBool(bool& v) : v_(v) {}
  void Parse(istringstream& is) const
  {
    string s;
    is >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    v_ = (s == "1" || s == "yes" || s == "on" || s == "enable" || s == "true" || s == "descend");
  }
private:
  bool& v_;
};

static istringstream& operator>>(istringstream& is, const ReadBool& rb)
{
  rb.Parse(is);
  return is;
}

extern const string * TextDescriptionAddSongTitle(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddSongArtist(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddAlbumTitle(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddAlbumArtist(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddYear(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddGenre(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddTrackNumber(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPublisher(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddISRC(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddCustomTag(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddLength(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddStripCode(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedSongTitle(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedSongArtist(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedAlbumTitle(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedAlbumArtist(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedYear(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedGenre(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedTrackNumber(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedPublisher(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedISRC(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedCustomTag(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedLength(const song_t *song, const song_t *paired_song);
extern const string * TextDescriptionAddPairedStripCode(const song_t *song, const song_t *paired_song);

constexpr auto TextDescriptionSongTitle         { "${SONG_TITLE}"          };
constexpr auto TextDescriptionSongArtist        { "${SONG_ARTIST}"         };
constexpr auto TextDescriptionAlbumTitle        { "${ALBUM_TITLE}"         };
constexpr auto TextDescriptionAlbumArtist       { "${ALBUM_ARTIST}"        };
constexpr auto TextDescriptionYear              { "${YEAR}"                };
constexpr auto TextDescriptionGenre             { "${GENRE}"               };
constexpr auto TextDescriptionTrackNumber       { "${TRACK_NUMBER}"        };
constexpr auto TextDescriptionPublisher         { "${PUBLISHER}"           };
constexpr auto TextDescriptionISRC              { "${ISRC}"                };
constexpr auto TextDescriptionCustomTag         { "${CUSTOM_TAG}"          };
constexpr auto TextDescriptionLength            { "${LENGTH}"              };
constexpr auto TextDescriptionStripCode         { "${STRIP_CODE}"          };
constexpr auto TextDescriptionPairedSongTitle   { "${PAIRED_SONG_TITLE}"   };
constexpr auto TextDescriptionPairedSongArtist  { "${PAIRED_SONG_ARTIST}"  };
constexpr auto TextDescriptionPairedAlbumTitle  { "${PAIRED_ALBUM_TITLE}"  };
constexpr auto TextDescriptionPairedAlbumArtist { "${PAIRED_ALBUM_ARTIST}" };
constexpr auto TextDescriptionPairedYear        { "${PAIRED_YEAR}"         };
constexpr auto TextDescriptionPairedGenre       { "${PAIRED_GENRE}"        };
constexpr auto TextDescriptionPairedTrackNumber { "${PAIRED_TRACK_NUMBER}" };
constexpr auto TextDescriptionPairedPublisher   { "${PAIRED_PUBLISHER}"    };
constexpr auto TextDescriptionPairedISRC        { "${PAIRED_ISRC}"         };
constexpr auto TextDescriptionPairedCustomTag   { "${PAIRED_CUSTOM_TAG}"   };
constexpr auto TextDescriptionPairedLength      { "${PAIRED_LENGTH}"       };
constexpr auto TextDescriptionPairedStripCode   { "${PAIRED_STRIP_CODE}"   };

const array<text_description_t, 24> text_description {
  {
    {TextDescriptionSongTitle        , TextDescriptionAddSongTitle},
    {TextDescriptionSongArtist       , TextDescriptionAddSongArtist},
    {TextDescriptionAlbumTitle       , TextDescriptionAddAlbumTitle},
    {TextDescriptionAlbumArtist      , TextDescriptionAddAlbumArtist},
    {TextDescriptionYear             , TextDescriptionAddYear},
    {TextDescriptionGenre            , TextDescriptionAddGenre},
    {TextDescriptionTrackNumber      , TextDescriptionAddTrackNumber},
    {TextDescriptionPublisher        , TextDescriptionAddPublisher},
    {TextDescriptionISRC             , TextDescriptionAddISRC},
    {TextDescriptionCustomTag        , TextDescriptionAddCustomTag},
    {TextDescriptionLength           , TextDescriptionAddLength},
    {TextDescriptionStripCode        , TextDescriptionAddStripCode},
    {TextDescriptionPairedSongTitle  , TextDescriptionAddPairedSongTitle}, // NOTE POSITION IS IMPORTANT FOR paired_song_description INITIALISATION NEAR END OF THIS FILE
    {TextDescriptionPairedSongArtist , TextDescriptionAddPairedSongArtist},
    {TextDescriptionPairedAlbumTitle , TextDescriptionAddPairedAlbumTitle},
    {TextDescriptionPairedAlbumArtist, TextDescriptionAddPairedAlbumArtist},
    {TextDescriptionPairedYear       , TextDescriptionAddPairedYear},
    {TextDescriptionPairedGenre      , TextDescriptionAddPairedGenre},
    {TextDescriptionPairedTrackNumber, TextDescriptionAddPairedTrackNumber},
    {TextDescriptionPairedPublisher  , TextDescriptionAddPairedPublisher},
    {TextDescriptionPairedISRC       , TextDescriptionAddPairedISRC},
    {TextDescriptionPairedCustomTag  , TextDescriptionAddPairedCustomTag},
    {TextDescriptionPairedLength     , TextDescriptionAddPairedLength},
    {TextDescriptionPairedStripCode  , TextDescriptionAddPairedStripCode},
  }
};

class ConfigBaseClass {
public:
  static string filepath;
  virtual void cfgRead(string line) = 0;
  virtual void DescribeParams(ofstream &strm, const char *indent) = 0;
  static ints2_t touch_tl; // top left
  static ints2_t touch_br; // bottom right

  void DescribeParam(ofstream &strm, const string & indent, const string &keyword, const string &description, const bool multi_param)
  {
    if (multi_param)
    {
      strm << indent << keyword << setw(maxCfgKeywordWidth - keyword.size()) << left << multiCfgParameter << description << endl;
    }
    else
    {
      strm << indent << setw(maxCfgKeywordWidth) << left << keyword << description << endl;
    }
  }

private:

  bool ExtractParameterValues(string &line, const char *keyword)
  // if line contains "keyword=DATA", then return true and update line to contain just "DATA", else return false
  {
    // remove any CRLF characters...
    line.erase(std::remove(line.begin(), line.end(), 10), line.end());
    line.erase(std::remove(line.begin(), line.end(), 13), line.end());

    // remove everything after any comment...
    size_t eolc { line.find_first_of(cfgFile_comment) };
    if (eolc != string::npos) line.erase(eolc);

    if (line.size() == 0) return false; // no characters left!

    string lowercase_keyword {keyword};
    transform(lowercase_keyword.begin(), lowercase_keyword.end(), lowercase_keyword.begin(), ::tolower);

    string lowercase_line { line };
    transform(lowercase_line.begin(), lowercase_line.end(), lowercase_line.begin(), ::tolower);

    // search for keyword...
    size_t p { lowercase_line.find(lowercase_keyword) };
    if (p == string::npos) return false; // keyword not found

    if (p > 0) // there are some characters before the keyword so could be a different keyword...
    {
      return false; // only accept keywords if they are at the beginning of the line
      // char c { lowercase_line.at(p-1) };
      // if ((c != ' ')  && (c != '\t')) return false; // not a whitespace, so probably a different keyword
    }

    // see if there are any non separator characters immediately after the keyword - if so, it could be another keyword...
    size_t q { lowercase_line.find_first_not_of(cfgFile_keyword_param_separator, p + lowercase_keyword.size()) };
    if (q == lowercase_keyword.size()) return false;

    line.erase(0, line.find_first_not_of(cfgFile_keyword_param_separator, p + lowercase_keyword.size())); // remove keyword + parameter separators

    // replace certain characters with spaces...
    // constexpr char invalidParameterSeparators[] { ",{}[]()" };
    // size_t found = line.find_first_of(invalidParameterSeparators);
    // while (found!=std::string::npos)
    // {
      // line[found]=' ';
      // found=line.find_first_of(invalidParameterSeparators,found+1);
    // }

    // remove trailing whitespace...
    size_t eolw { line.find_last_not_of(" \t") };
    if (eolw != string::npos) line.erase(eolw + 1);
    return true;
  }

public:

  bool GetDescParam(string line, const char *keyword, string &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string str {};
    if (!getline(ss >> std::ws, str)) return false;
    if (str.size() == 0) return false;

    // parse complete string, searching for reserved description $keywords (from text_description vector) , and replacing them with TitleStripDescriptionsVarStart (=255), then code (index into text_description vector + 1)

    var.clear();
    for (auto pos = 0; pos < str.size(); ++pos)  // each character in string...
    {
      bool found { false };
      for (auto d = 0; d < text_description.size(); ++d)  // see if we have a reserved word...
      {
        size_t l { text_description.at(d).name.size() };
        if (str.compare(pos, l, text_description.at(d).name) == 0) // ...yep
        {
          // replace keyword with its position in the text_description vector (and lead-in character) ...
          var += TitleStripDescriptionsVarStart;
          var += static_cast<char>(d+1); // +1 to prevent null character
          pos += l - 1; // skip over reserved word
          found = true;
          break;
        }
      }
      if (found == false) var += str.at(pos); // just copy the character
    }

    PutParam(log_file, keyword, str);
    return true;
  }

///////////////////////////////////////////////////////////////////////////////////////////////////

  void PutParam(ofstream &strm, const char *keyword, dynamic_flag_en_e &var)
  {
    if (var != dynamic_flag_en_e::None)
    {
      strm << "  " << keyword << " = " << static_cast<uint32_t>(var) << endl;
    }
  }

  void PutParam(ofstream &strm, const char *keyword, uint32_t &var)
  {
    strm << "  " << keyword << " = " << var << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, int32_t &var)
  {
    strm << "  " << keyword << " = " << var << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, string &var)
  {
    strm << "  " << keyword << " = " << var << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, float &var)
  {
    strm << std::fixed << std::setprecision(FloatPrecision) << "  " << keyword << " = " << var << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, bool &var)
  {
    strm << "  " << keyword << " = " << YesNo(var) << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, time_unit_t &var)
  {
    strm << std::fixed << std::setprecision(FloatPrecision) << "  " << keyword << " = " << var.value << " " << var.units_str;
    if (var.value != 1.0) strm << "s";
    strm << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, uints2_t &var)
  {
    strm << "  " << keyword << " = " << var.x << " " << var.y << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, band_gain_t &var)
  {
    strm << "  " << keyword << " = " << var.num << " " << var.gain << " " << var.offset.x << " " << var.offset.y;

    rgba_uchar_t temp_tint;

    al_unmap_rgba(var.tint, &temp_tint.r, &temp_tint.g, &temp_tint.b, &temp_tint.a);

    if (
      (temp_tint.r != 255) ||
      (temp_tint.g != 255) ||
      (temp_tint.b != 255) ||
      (temp_tint.a != 255)
      ) // not the same as the default, so write it to the file
    {
      strm << " " << static_cast<uint32_t>(temp_tint.r) <<  " " << static_cast<uint32_t>(temp_tint.g) <<  " " << static_cast<uint32_t>(temp_tint.b) <<  " " << static_cast<uint32_t>(temp_tint.a);
    }
    strm << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, ints2_t &var)
  {
    strm << "  " << keyword << " = " << var.x << " " << var.y << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, attract_choice_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case attract_choice_e::Sorted :
        strm << "Sorted" << endl;
        break;

      default :
        strm << "Random" << endl;
        break;
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, replay_gain_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case replay_gain_e::Track :
        strm << "Track" << endl;
        break;

      case replay_gain_e::Album :
        strm << "Album" << endl;
        break;

      default :
        strm << "None" << endl;
        break;
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, pair_songs_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case pair_songs_e::No :
        strm << "No" << endl;
        break;

      case pair_songs_e::Yes :
        strm << "Yes" << endl;
        break;

      default :
        strm << "Dual" << endl;
        break;
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, select_buttons_sequence_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case select_buttons_sequence_e::RowCol :
        strm << "RowCol" << endl;
        break;

      case select_buttons_sequence_e::ColRow :
        strm << "ColRow" << endl;
        break;
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, artwork_mode_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case artwork_mode_e::Auto :
        strm << "Auto" << endl;
        break;

      case artwork_mode_e::None :
        strm << "None" << endl;
        break;

      case artwork_mode_e::Embedded :
        strm << "Embedded" << endl;
        break;

      case artwork_mode_e::Specified :
        strm << "Specified" << endl;
        break;

      case artwork_mode_e::Folder :
        strm << "Folder" << endl;
        break;

      case artwork_mode_e::Logo :
        strm << "Logo" << endl;
        break;

    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, sort_songs_by_t &var)
  {
    strm << "  " << keyword << " = ";
    switch (var.by)
    {
      case sort_songs_by_e::Title :
        strm << "Title";
        break;
    
      case sort_songs_by_e::TrackNumber :
        strm << "TrackNumber";
        break;
    
      case sort_songs_by_e::Artist :
        strm << "Artist";
        break;
    
      case sort_songs_by_e::AlbumArtist :
        strm << "AlbumArtist";
        break;
    
      case sort_songs_by_e::Album :
        strm << "Album";
        break;
    
      case sort_songs_by_e::Year :
        strm << "Year";
        break;
    
      case sort_songs_by_e::Genre :
        strm << "Genre";
        break;
    
      case sort_songs_by_e::Random :
        strm << "Random";
        break;
    
      case sort_songs_by_e::Unsorted :
        strm << "Unsorted";
        break;
    
      case sort_songs_by_e::Publisher :
        strm << "Publisher";
        break;
    
      case sort_songs_by_e::ISRC :
        strm << "ISRC";
        break;
    
      case sort_songs_by_e::Custom :
        strm << "Custom";
        break;
    }
    if (var.descending)
    {
      strm << " " << DescendAscend(var.descending);
    }
    strm << endl;
  }
    
  void PutParam(ofstream &strm, const char *keyword, spectrum_analyser_mode_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case spectrum_analyser_mode_e::Scaled :
        strm << "Scaled" << endl;
        break;
    
      case spectrum_analyser_mode_e::Clipped :
        strm << "Clipped" << endl;
        break;
    
      case spectrum_analyser_mode_e::Position :
        strm << "Position" << endl;
        break;    
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, spectrum_analyser_channel_e &var)
  {
    strm << "  " << keyword << " = ";
    switch (var)
    {
      case spectrum_analyser_channel_e::Left :
        strm << "Left" << endl;
        break;
    
      case spectrum_analyser_channel_e::Right :
        strm << "Right" << endl;
        break;
    
      case spectrum_analyser_channel_e::Both :
        strm << "Both" << endl;
        break;    
    }
  }
  
  void PutParam(ofstream &strm, const char *keyword, ALLEGRO_COLOR &var)
  {
    strm << "  " << keyword << " = " << var.r <<  " " << var.g <<  " " << var.b <<  " " << var.a << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, rgb_t &var)
  {
    strm << "  " << keyword << " = " << var.r <<  " " << var.g <<  " " << var.b << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, rgba_t &var)
  {
    strm << "  " << keyword << " = " << var.r <<  " " << var.g <<  " " << var.b <<  " " << var.a << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, font_t &var)
  {
    strm << "  " << keyword << " = " << var.filename << " " << var.size << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, text_t &var)
  {
    unsigned char r, g, b, a;
    al_unmap_rgba(var.colour, &r, &g, &b, &a);
    strm << "  " << keyword << " = " << var.font_number << " " << static_cast<uint32_t>(r) <<  " " << static_cast<uint32_t>(g) <<  " " << static_cast<uint32_t>(b) <<  " " << static_cast<uint32_t>(a);
    switch (var.alignment)
    {
      case ALLEGRO_ALIGN_CENTRE :
        strm << " centre";
        break;

      case ALLEGRO_ALIGN_RIGHT :
        strm << " right";
        break;

      default :
        strm << " left";
        break;
    }
    strm << " " << YesNo(var.capitalise);
    strm << " " << var.mode;
    strm << " " << YesNo(var.quoted);
    strm << " " << var.offset.x << " " << var.offset.y << " " << var.max_width << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, video_t &var)
  {
    strm << "  " << keyword << " = " << var.filename << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, bitmap_t &var)
  {
    strm << "  " << keyword << " = " << var.filename << endl;
  }

  void PutParam(ofstream &strm, const char *keyword, bitmap_t &var, string genre_str)
  {
    strm << "  " << keyword << " = " << var.filename << " " << genre_str << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, sound_t &var)
  {
    strm << "  " << keyword << " = " << var.filename << " " << var.volume << " " << YesNo(var.loop) << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, button_t &var)
  {
    strm << "  " << keyword << " = " << var.val_str << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, title_strip_style_t &var)
  {
    strm  << "  " << keyword << " = " << var.speed << " " << var.effect << " " << YesNo(var.fading) << endl;

  }
  
  void PutParam(ofstream &strm, const char *keyword, area_t &var)
  {
    strm << "  " << keyword << " = " << var.x << " " << var.y << " " << var.w << " " << var.h << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, const string filename, touch_area_t &var)
  {
    strm << "  " << keyword << " = " << var.x << " " << var.y << " " << var.w << " " << var.h;
    if (filename.size()) { // user has specified a bitmap for this touch area...
      strm << " " << filename;
    }
    strm << endl;
  }
  
  void PutDynamic(ofstream &strm, dynamic_t &var)
  {
    if (var.param->is_dynamic)
    {
      strm << var.min << " " << dynamicParameterStartStr << var.max << " " << var.param->label;
      if (var.param->is_spectrum_analyser) // add spectrum band
      {
        strm << " " << var.mode_param;
      }
      strm << dynamicParameterStopStr;
    }
    else // not dynamic
    {
      strm << var.val;
    }
  }

  void PutParam(ofstream &strm, const char *keyword, dynamic_t &var)
  {
    strm << "  " << keyword << " = ";
    PutDynamic(strm, var);
    strm << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, dynamics2_t &var)
  {
    strm << "  " << keyword << " = ";
    PutDynamic(strm, var.x); strm << " ";
    PutDynamic(strm, var.y); strm << endl;
  }
  
  void PutParam(ofstream &strm, const char *keyword, dynamics4_t &var)
  {
    strm << "  " << keyword << " = ";
    PutDynamic(strm, var.x); strm << " ";
    PutDynamic(strm, var.y); strm << " ";
    PutDynamic(strm, var.w); strm << " ";
    PutDynamic(strm, var.h); strm << endl;
  }
  
///////////////////////////////////////////////////////////////////////////////////////////////////

  bool GetParam(string line, const char *keyword, string &var, bool no_filepath_prefix)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(bool no_log_output, string line, const char *keyword, string &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    return true;
  }

  bool GetParam(string line, const char *keyword, string &var, bool no_filepath_prefix, bool supress_message)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    if (supress_message == false) PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, string &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var)) return false;
    var = ConfigBaseClass::filepath + FILE_SEPARATOR + var;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, bool &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> ReadBool(var);
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, time_unit_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string str {};
    float ticks_per_unit { 1.0 };
    float value;

    // undefined time unit parameter defaults to ticks
    var.units_str = TimeUnitsTicksStr;
    var.units = time_unit_e::Ticks;

    ss >> value; // read value

    if (ss.fail())
    {
      var.value = 0;
    }
    else
    {
      var.value = value;
    }
    ss >> str; // attempt to read units...
    if (str.size())
    {
      switch (tolower(str.at(0)))
      {
        case 's' : // seconds
          var.units = time_unit_e::Seconds;
          var.units_str = TimeUnitsSecondsStr;
          ticks_per_unit = display_refresh_rate;
        break;

        case 'm' : // minutes
          var.units = time_unit_e::Minutes;
          var.units_str = TimeUnitsMinutesStr;
          ticks_per_unit = 60.0 * display_refresh_rate;
        break;

        case 'h' : // hours
          var.units = time_unit_e::Hours;
          var.units_str = TimeUnitsHoursStr;
          ticks_per_unit = 3600.0 * display_refresh_rate;
        break;

        // ...any else defaults to ticks
      }
    }
    var.ticks = static_cast<uint32_t>(var.value * ticks_per_unit); // convert value to ticks

    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, uint32_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, dynamic_flag_en_e &var)
  {
    uint32_t v;
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> v;
    var = static_cast<dynamic_flag_en_e>(v);
    PutParam(log_file, keyword, var);
    return true;
  }
  
  bool GetParam(string line, const char *keyword, int32_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, float &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var;
    PutParam(log_file, keyword, var);
    return true;
  }

  uint32_t GetDynamic(string line, const char *keyword, dynamic_t &var)
  {
    string temp_str {};
    uint32_t current_line_pos {};
    istringstream ss { line };
    ss >> var.val;
    var.min = var.val;
    var.max = var.val;
    var.param = &DynamicParameterNone; // default to none
    var.mode_param = 0;
    current_line_pos = ss.tellg();
    try {
      temp_str = line.substr(ss.tellg(), string::npos);
    }
    catch (const std::out_of_range &err)
    {
      return current_line_pos; // skip over first parameter value for subsequent call to GetDynamic()
    }

    // try and extract "(max mode)" ...
    // from the current point (ss.tellg()), we look for a '[', and save its position...
    auto open_brace_pos = temp_str.find_first_of(dynamicParameterStartStr);

    // now we look for the position of the first numeric digit...
    auto digit_pos = temp_str.find_first_of("0123456789");

    if (digit_pos < open_brace_pos) // there's no optional dynamic params...
    {
      var.max = var.val;
      return current_line_pos; // skip over first parameter value for subsequent call to GetDynamic()
    }
    else
    {
      string mode;
      try {
        temp_str.erase(0, open_brace_pos + 1);
      }
      catch (const std::out_of_range &err)
      {
        return current_line_pos; // skip over first parameter value for subsequent call to GetDynamic()
      }
      current_line_pos += open_brace_pos + 1;
      auto close_brace_pos = temp_str.find_first_of(dynamicParameterStopStr);
      try
      {
        temp_str.erase(close_brace_pos, string::npos);
      }
      catch (const std::out_of_range &err)
      {
        return current_line_pos; // skip over first parameter value for subsequent call to GetDynamic()
      }
      current_line_pos += close_brace_pos + 1;
      istringstream ds { temp_str };
      ds >> var.max >> mode >> var.mode_param;
      if (mode.size())
      {
        for (auto &l : DynamicParameter)
        {
          if (mode.compare(l.label) == 0)
          {
            var.param = &l;
            break;
          }
        }
      }
      return current_line_pos;
    }
    return 0;
  }

  bool GetParam(string line, const char *keyword, dynamic_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    GetDynamic(line, keyword, var);
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, dynamics2_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    uint32_t second_param_pos = GetDynamic(line, keyword, var.x);
    line.erase(0, second_param_pos);
    GetDynamic(line, keyword, var.y);
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, dynamics4_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;

    uint32_t next_param_pos = GetDynamic(line, keyword, var.x);
    line.erase(0, next_param_pos);

    next_param_pos = GetDynamic(line, keyword, var.y);
    line.erase(0, next_param_pos);

    next_param_pos = GetDynamic(line, keyword, var.w);
    line.erase(0, next_param_pos);

    GetDynamic(line, keyword, var.h);

    PutParam(log_file, keyword, var);

    return true;
  }

  bool GetParam(string line, const char *keyword, uints2_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, band_gain_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.num >> var.gain >> var.offset.x >> var.offset.y;

    // read optional tint - if not present then default to 255 (no tint)
    uint32_t r,g,b,a {};
    rgba_uchar_t tint {255, 255, 255, 255};
    ss >> r; if (!ss.fail()) tint.r = static_cast<unsigned char>(r);
    ss >> g; if (!ss.fail()) tint.g = static_cast<unsigned char>(g);
    ss >> b; if (!ss.fail()) tint.b = static_cast<unsigned char>(b);
    ss >> a; if (!ss.fail()) tint.a = static_cast<unsigned char>(a);
    var.tint = al_map_rgba(tint.r, tint.g, tint.b, tint.a);
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, ints2_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y;
    PutParam(log_file, keyword, var);
    return true;
  }


  bool GetParam(string line, const char *keyword, attract_choice_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'r')
    {
      var = attract_choice_e::Random;
      ret = true;
    }

    if (c == 's')
    {
      var = attract_choice_e::Sorted;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, replay_gain_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'n')
    {
      var = replay_gain_e::None;
      ret = true;
    }

    if (c == 't')
    {
      var = replay_gain_e::Track;
      ret = true;
    }

    if (c == 'a')
    {
      var = replay_gain_e::Album;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, pair_songs_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'n')
    {
      var = pair_songs_e::No;
      ret = true;
    }

    if (c == 'y')
    {
      var = pair_songs_e::Yes;
      ret = true;
    }

    if (c == 'd')
    {
      var = pair_songs_e::Dual;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, select_buttons_sequence_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'r')
    {
      var = select_buttons_sequence_e::RowCol;
      ret = true;
    }

    if (c == 'c')
    {
      var = select_buttons_sequence_e::ColRow;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, artwork_mode_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'a')
    {
      var = artwork_mode_e::Auto;
      ret = true;
    }

    if (c == 'n')
    {
      var = artwork_mode_e::None;
      ret = true;
    }

    if (c == 'e')
    {
      var = artwork_mode_e::Embedded;
      ret = true;
    }

    if (c == 's')
    {
      var = artwork_mode_e::Specified;
      ret = true;
    }

    if (c == 'f')
    {
      var = artwork_mode_e::Folder;
      ret = true;
    }

    if (c == 'l')
    {
      var = artwork_mode_e::Logo;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, sort_songs_by_t &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() < 2) return false;

    auto c { tolower(s.at(0)) };

    if (c == 't')
    {
      if (tolower(s.at(1)) == 'i')
      {
        var.by = sort_songs_by_e::Title;
        ret = true;
      }
      else
      {
        var.by = sort_songs_by_e::TrackNumber;
        ret = true;
      }
    }

    if (c == 'a')
    {
      if (tolower(s.at(1)) == 'r')
      {
        var.by = sort_songs_by_e::Artist;
        ret = true;
      }
      else if (tolower(s.at(1)) == 'l')
      {
        if (s.size() > 5)
        {
          var.by = sort_songs_by_e::AlbumArtist;
          ret = true;
        }
        else
        {
          var.by = sort_songs_by_e::Album;
          ret = true;
        }
      }
    }

    if (c == 'y')
    {
      var.by = sort_songs_by_e::Year;
      ret = true;
    }

    if (c == 'g')
    {
      var.by = sort_songs_by_e::Genre;
      ret = true;
    }

    if (c == 'r')
    {
      var.by = sort_songs_by_e::Random;
      ret = true;
    }

    if (c == 'u')
    {
      var.by = sort_songs_by_e::Unsorted;
      ret = true;
    }

    if (c == 'p')
    {
      var.by = sort_songs_by_e::Publisher;
      ret = true;
    }

    if (c == 'i')
    {
      var.by = sort_songs_by_e::ISRC;
      ret = true;
    }

    if (c == 'c')
    {
      var.by = sort_songs_by_e::Custom;
      ret = true;
    }

    ss >> ReadBool(var.descending);

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, spectrum_analyser_mode_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 's')
    {
      var = spectrum_analyser_mode_e::Scaled;
      ret = true;
    }
    if (c == 'c')
    {
      var = spectrum_analyser_mode_e::Clipped;
      ret = true;
    }
    if (c == 'p')
    {
      var = spectrum_analyser_mode_e::Position;
      ret = true;
    }

    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, spectrum_analyser_channel_e &var)
  {
    bool ret { false };
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string s;
    ss >> s;

    if (s.size() == 0) return false;

    auto c { tolower(s.at(0)) };

    if (c == 'l')
    {
      var = spectrum_analyser_channel_e::Left;
      ret = true;
    }
    if (c == 'r')
    {
      var = spectrum_analyser_channel_e::Right;
      ret = true;
    }
    if (c == 'b')
    {
      var = spectrum_analyser_channel_e::Both;
      ret = true;
    }
    
    PutParam(log_file, keyword, var);
    return ret;
  }

  bool GetParam(string line, const char *keyword, ALLEGRO_COLOR &var)
  {
    rgba_t col;
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> setbase(0) >> col.r >> col.g >> col.b >> col.a;
    var = al_map_rgba(col.r, col.g, col.b, col.a);
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, rgb_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> setbase(0) >> var.r >> var.g >> var.b;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, rgba_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> setbase(0) >> var.r >> var.g >> var.b >> var.a;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, font_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    if (!getline(ss >> std::ws, var.filename, ' ')) return false;
    var.filename = ConfigBaseClass::filepath + FILE_SEPARATOR + var.filename;
    ss >> var.size;
    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, text_t &var)
  {
    rgba_t col;
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string align;
    ss >> var.font_number;
    ss >> setbase(0) >> col.r >> col.g >> col.b >> col.a;
    var.colour = al_map_rgba(col.r, col.g, col.b, col.a);
    ss >> align;
    var.alignment = ALLEGRO_ALIGN_LEFT;
    if (align.size())
    {
      auto c { tolower(align.at(0)) };

      if (c == 'c') var.alignment = ALLEGRO_ALIGN_CENTRE;
      if (c == 'r') var.alignment = ALLEGRO_ALIGN_RIGHT;
    }
    ss >> ReadBool(var.capitalise);
    ss >> var.mode;
    ss >> ReadBool(var.quoted);
    ss >> var.offset.x >> var.offset.y;
    ss >> var.max_width;

    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, vector<genre_bkgnd_t> &bitmaps, genre_bkgnd_t &default_bkgnd)
  {
    bitmap_t var {};
    // Extract filename for bitmap...
    if (ExtractParameterValues(line, keyword) == false) return false;
    string genre_str {};
    istringstream ss { line };
    ss >> var.filename;
    var.filename = ConfigBaseClass::filepath + FILE_SEPARATOR + var.filename;

    // Create bitmap, and push the ALLEGRO_BITMAP pointer to the title_strip_bkgnd_bitmap vector...
    if ((var.handle = al_load_bitmap(var.filename.c_str())) == nullptr) error("Couldn't load bitmap '%s'", var.filename.c_str());
    genre_bkgnd_t genre_bkgnd { nullptr, "" };
    genre_bkgnd.bm = var.handle;

    // Then (try to) extract genre...
    while (ss.peek() == ' ') ss.get(); // skip leading spaces
    getline(ss, genre_str);

    if (genre_str.size())
    // add it to the bitmaps vector (bitmap pointer and genre string)
    {
      genre_bkgnd.genre = genre_str;
      bitmaps.push_back(genre_bkgnd);
    }
    else
    // no genre specified, so store this bitmap pointer in the default_bkgnd
    {
      default_bkgnd = genre_bkgnd;
    }

    PutParam(log_file, keyword, var, genre_str);
    return true;
  }

  bool GetParam(string line, const char *keyword, bitmap_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.filename;
    var.filename = ConfigBaseClass::filepath + FILE_SEPARATOR + var.filename;
    if (var.handle == nullptr) // not already defined
    {
      if ((var.handle = al_load_bitmap(var.filename.c_str())) == nullptr) error("Couldn't load bitmap '%s'", var.filename.c_str());
      PutParam(log_file, keyword, var);
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, bitmap_t &var, bool no_filepath_prefix)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.filename;
    if (var.handle == nullptr) // not already defined
    {
      if ((var.handle = al_load_bitmap(var.filename.c_str())) == nullptr) error("Couldn't load bitmap '%s'", var.filename.c_str());
      PutParam(log_file, keyword, var);
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, video_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.filename;
    var.filename = ConfigBaseClass::filepath + FILE_SEPARATOR + var.filename;
    if (var.handle == nullptr) // not already defined
    {
      PutParam(log_file, keyword, var);
    }
    return true;
  }

  bool GetParam(string line, const char *keyword, sound_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    uint32_t vol { MaxSongVolume };
    istringstream ss { line };

    if (!getline(ss >> std::ws, var.filename, ' ')) return false;
    var.filename = ConfigBaseClass::filepath + FILE_SEPARATOR + var.filename;
    if ((var.handle = al_load_sample(var.filename.c_str())) == nullptr) error("Couldn't load sound '%s'", var.filename.c_str());
    var.instance = al_create_sample_instance(var.handle);

    ss >> vol;
    if (vol > MaxSongVolume) vol = MaxSongVolume;
    // var.volume = vol/MaxSongVolume;
    var.volume = vol;

    // al_attach_sample_instance_to_mixer(var.instance, AudioClass::output_mixer);
    ss >> ReadBool(var.loop);
    var.length = 10 * al_get_sample_length(var.handle) / al_get_sample_frequency(var.handle); // in hundreds of msec

    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, title_strip_style_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.speed >> var.effect;
    ss >> ReadBool(var.fading);

    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, area_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    ss >> var.x >> var.y >> var.w >> var.h;

    PutParam(log_file, keyword, var);
    return true;
  }

  bool GetParam(string line, const char *keyword, touch_area_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string filename {};
    ss >> var.x >> var.y >> var.w >> var.h;
    ss >> filename;
    if (filename.size()) // user has specified a bitmap for this touch area...
    {
      filename = ConfigBaseClass::filepath + FILE_SEPARATOR + filename;
      // Create bitmap...
      if ((var.bitmap = al_load_bitmap(filename.c_str())) == nullptr) error("Couldn't load touch area bitmap '%s'", filename.c_str());
    }

    PutParam(log_file, keyword, filename, var);
    return true;
  }

  uint32_t FindKeyLabel(const string &label, const string &id_str, uint32_t &id)
  {
    id = 0;
    for (auto l=0; l<input_event_labels::input_event_label.size(); ++l)
    {
      string s { input_event_labels::input_event_label.at(l) };
      if (s.compare(0, s.size(), label, 0, label.size()) == 0) // matched label, now see if there's a (x) after it...
      {
        size_t pos { id_str.find(ButtonDeviceStr) };
        if (pos != string::npos)
        {
          id = stoi(id_str.substr(pos + strlen(ButtonDeviceStr),1));
        }
        return l;
      }
    }
    
    return input_event_labels::NumInputKeys;
  }

  bool GetParam(string line, const char *keyword, button_t &var)
  {
    if (ExtractParameterValues(line, keyword) == false) return false;
    istringstream ss { line };
    string label, id_str;

    ss >> label;
    ss >> id_str;
    var.param = { 0, 0, 0, 0 };

    bool ok { false };
    uint32_t id { 0 };
    uint32_t label_idx { FindKeyLabel(label, id_str, id) };
    
    // cout << "FindKeyLabel for " << label << " returned id of " << id << endl;
    if (label_idx < input_event_labels::AbsLoOffset) // key, or btn
    {
      var.type = input_type_e::Key;
      var.param[EVENT_PARAM_ID] = id;
      var.param[EVENT_PARAM_VAL1] = label_idx;
      var.val_str = input_event_labels::input_event_label.at(label_idx);
      if (id) // add "(x)" to val_str if device non zero
      {
        var.val_str += " " + string(ButtonDeviceStr) + to_string(id) + string(ButtonDeviceStrPost);
      }
      ok = true;
    }
    else if (label_idx < input_event_labels::AbsHiOffset) // abs (joystick) lo region
    {
      var.type = input_type_e::JoyStick;
      var.param[EVENT_PARAM_ID] = id;
      var.param[EVENT_PARAM_VAL1] = label_idx - input_event_labels::AbsLoOffset;
      var.param[EVENT_PARAM_VAL2] = 0;
      var.val_str = input_event_labels::input_event_label.at(label_idx);
      if (id) // add "(x)" to val_str if device non zero
      {
        var.val_str += " " + string(ButtonDeviceStr) + to_string(id) + string(ButtonDeviceStrPost);
      }
      ok = true;
    }
    else if (label_idx < input_event_labels::NumInputKeys) // abs (joystick) hi region
    {
      var.type = input_type_e::JoyStick;
      var.param[EVENT_PARAM_ID] = id;
      var.param[EVENT_PARAM_VAL1] = label_idx - input_event_labels::AbsHiOffset;
      var.param[EVENT_PARAM_VAL2] = input_event_labels::AbsHiOffset - input_event_labels::AbsLoOffset;
      var.val_str = input_event_labels::input_event_label.at(label_idx);
      if (id) // add "(x)" to val_str if device non zero
      {
        var.val_str += " " + string(ButtonDeviceStr) + to_string(id) + string(ButtonDeviceStrPost);
      }
      ok = true;
    }
    else if (label.compare(0, 5, ButtonTypeGPIOStr, 0, 5) == 0) // GPIO
    {
      var.type = input_type_e::GPIO;
      uint32_t pin;
      try {
        pin = stoi(label.substr(strlen(ButtonTypeGPIOStr),2)); // extract integer after "GPIO_"
      }
      catch (const std::invalid_argument &err) {
        error("Unknown GPIO pin in ini file [buttons] section, line : %s", line);
      }
      var.param[EVENT_PARAM_VAL1] = pin;
      var.val_str = ButtonTypeGPIOStr + to_string(var.param[EVENT_PARAM_VAL1]);
      ok = true;
    }

    if (ok)
    {
      PutParam(log_file, keyword, var);
      return true;
    }
    return false;
  }
};

class IniGeneralConfigClass : public ConfigBaseClass
{
public:
  void cfgRead(string line)
  {
    uint32_t uint { 0 };
    string str {};
    if (GetParam(line, cfgKeyword_MusicPath, str, false))
    {
      if (ini_file_music_path == false) // this is our first MusicPath defined, so ...
      {
        music_path.clear(); // clear the default entry
      }
      ini_file_music_path = true;
      music_path.push_back(str);
      return;
    }

    if (GetParam(line, cfgKeyword_CustomMP3Tag,                    custom_mp3_tag, false)) return;
    if (GetParam(line, cfgKeyword_MaxPlayQueueLength,              max_playqueue_length)) return;
    if (GetParam(line, cfgKeyword_MenuColour,                      menu_colour)) return;
    if (GetParam(line, cfgKeyword_MenuBackgroundColour,            menu_bk_colour)) return;
    if (GetParam(line, cfgKeyword_SkinChooserTimeout,              skin_chooser_timeout)) return;
    if (GetParam(line, cfgKeyword_LoopPlayQueue,                   loop_playqueue)) return;
    if (GetParam(line, cfgKeyword_IgnoreArtistPrefixThe,           ignore_artist_prefix_the)) return;
    if (GetParam(line, cfgKeyword_SongHistoryDepth,                song_history_depth)) return;
    if (GetParam(line, cfgKeyword_SongHistoryIncludeUserSelection, song_history_include_user_selection)) return;
    if (GetParam(line, cfgKeyword_SongVolume,                      song_volume)) return;
    if (GetParam(line, cfgKeyword_SongVolumeStep,                  song_volume_step)) return;
    if (GetParam(line, cfgKeyword_ReplayGain,                      replay_gain)) return;
    if (GetParam(line, cfgKeyword_FreePlay,                        free_play)) return;
    if (GetParam(line, cfgKeyword_CreditsPerCoin1, uint))
    {
      credits_per_coin.at(0) = uint;
      credits_per_coin_str.at(0) = to_string(credits_per_coin.at(0));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerCoin2, uint))
    {
      credits_per_coin.at(1) = uint;
      credits_per_coin_str.at(1) = to_string(credits_per_coin.at(1));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerCoin3, uint))
    {
      credits_per_coin.at(2) = uint;
      credits_per_coin_str.at(2) = to_string(credits_per_coin.at(2));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerCoin4, uint))
    {
      credits_per_coin.at(3) = uint;
      credits_per_coin_str.at(3) = to_string(credits_per_coin.at(3));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerCoin5, uint))
    {
      credits_per_coin.at(4) = uint;
      credits_per_coin_str.at(4) = to_string(credits_per_coin.at(4));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerCoin6, uint))
    {
      credits_per_coin.at(5) = uint;
      credits_per_coin_str.at(5) = to_string(credits_per_coin.at(5));
      return;
    }
    if (GetParam(line, cfgKeyword_CreditsPerSong, uint))
    {
      credits_per_song = uint;
      if (credits_per_song < 1) credits_per_song = 1;
      credits_per_song_str = to_string(credits_per_song);
      return;
    }
  }

  void cfgWrite(ofstream &strm)
  {
    for (auto &m : music_path)
    {
      PutParam(strm, cfgKeyword_MusicPath, m);
    }
    PutParam(strm, cfgKeyword_CustomMP3Tag                   , custom_mp3_tag);
    PutParam(strm, cfgKeyword_MaxPlayQueueLength             , max_playqueue_length);
    PutParam(strm, cfgKeyword_LoopPlayQueue                  , loop_playqueue);
    PutParam(strm, cfgKeyword_IgnoreArtistPrefixThe          , ignore_artist_prefix_the);
    PutParam(strm, cfgKeyword_SongHistoryDepth               , song_history_depth);
    PutParam(strm, cfgKeyword_SongHistoryIncludeUserSelection, song_history_include_user_selection);
    PutParam(strm, cfgKeyword_SongVolume                     , song_volume);
    PutParam(strm, cfgKeyword_SongVolumeStep                 , song_volume_step);
    PutParam(strm, cfgKeyword_ReplayGain                     , replay_gain);
    PutParam(strm, cfgKeyword_FreePlay                       , free_play);
    PutParam(strm, cfgKeyword_CreditsPerCoin1                , credits_per_coin.at(0));
    PutParam(strm, cfgKeyword_CreditsPerCoin2                , credits_per_coin.at(1));
    PutParam(strm, cfgKeyword_CreditsPerCoin3                , credits_per_coin.at(2));
    PutParam(strm, cfgKeyword_CreditsPerCoin4                , credits_per_coin.at(3));
    PutParam(strm, cfgKeyword_CreditsPerCoin5                , credits_per_coin.at(4));
    PutParam(strm, cfgKeyword_CreditsPerCoin6                , credits_per_coin.at(5));
    PutParam(strm, cfgKeyword_CreditsPerSong                 , credits_per_song);
    PutParam(strm, cfgKeyword_MenuColour                     , menu_colour);
    PutParam(strm, cfgKeyword_MenuBackgroundColour           , menu_bk_colour);
    PutParam(strm, cfgKeyword_SkinChooserTimeout             , skin_chooser_timeout);
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_MusicPath                      , cfgKeywordDesc_MusicPath                      , true);
    DescribeParam(strm, indent, cfgKeyword_CustomMP3Tag                   , cfgKeywordDesc_CustomMP3Tag                   , false);
    DescribeParam(strm, indent, cfgKeyword_MaxPlayQueueLength             , cfgKeywordDesc_MaxPlayQueueLength             , false);
    DescribeParam(strm, indent, cfgKeyword_LoopPlayQueue                  , cfgKeywordDesc_LoopPlayQueue                  , false);
    DescribeParam(strm, indent, cfgKeyword_IgnoreArtistPrefixThe          , cfgKeywordDesc_IgnoreArtistPrefixThe          , false);
    DescribeParam(strm, indent, cfgKeyword_SongHistoryDepth               , cfgKeywordDesc_SongHistoryDepth               , false);
    DescribeParam(strm, indent, cfgKeyword_SongHistoryIncludeUserSelection, cfgKeywordDesc_SongHistoryIncludeUserSelection, false);
    DescribeParam(strm, indent, cfgKeyword_SongVolume                     , cfgKeywordDesc_SongVolume                     , false);
    DescribeParam(strm, indent, cfgKeyword_SongVolumeStep                 , cfgKeywordDesc_SongVolumeStep                 , false);
    DescribeParam(strm, indent, cfgKeyword_ReplayGain                     , cfgKeywordDesc_ReplayGain                     , false);
    DescribeParam(strm, indent, cfgKeyword_FreePlay                       , cfgKeywordDesc_FreePlay                       , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin1                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin2                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin3                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin4                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin5                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerCoin6                , cfgKeywordDesc_CreditsPerCoin                 , false);
    DescribeParam(strm, indent, cfgKeyword_CreditsPerSong                 , cfgKeywordDesc_CreditsPerSong                 , false);
    DescribeParam(strm, indent, cfgKeyword_MenuColour                     , cfgKeywordDesc_MenuColour                     , false);
    DescribeParam(strm, indent, cfgKeyword_MenuBackgroundColour           , cfgKeywordDesc_MenuBackgroundColour           , false);
    DescribeParam(strm, indent, cfgKeyword_SkinChooserTimeout             , cfgKeywordDesc_SkinChooserTimeout             , false);
  }

  array<uint32_t, 6> credits_per_coin { {1, 2, 5, 10, 25, 100} };
  array<string, 6> credits_per_coin_str { {"1", "2", "5", "10", "25", "100" } };
  uint32_t credits_per_song { 1 };
  string credits_per_song_str { "1" };
  vector<string> music_path { "../Music" };
  string custom_mp3_tag { };
  uint32_t max_playqueue_length { 20 };
  uint32_t song_volume { 50 }; // half volume
  uint32_t song_volume_step { 10 };
  replay_gain_e replay_gain { replay_gain_e::None };
  bool loop_playqueue { false };
  bool ignore_artist_prefix_the { true };
  uint32_t song_history_depth { 20 };
  bool song_history_include_user_selection { false };
  bool free_play { true };
  rgb_t menu_colour {255, 255, 255};
  rgba_t menu_bk_colour {32, 32, 32, 200};
  time_unit_t skin_chooser_timeout { TimeUnitZero };

private:
};

class IniAttractModeConfigClass : public ConfigBaseClass
{
public:
  void cfgRead(string line)
  {
    uint32_t uint { 0 };
    if (GetParam(line, cfgKeyword_AttractModeEnable,          enable)) return;
    if (GetParam(line, cfgKeyword_AttractModeChoice,          choice)) return;
    if (GetParam(line, cfgKeyword_AttractModeInterval,        interval)) return;
    if (GetParam(line, cfgKeyword_AttractModeMaxVolume,       max_volume)) return;
    if (GetParam(line, cfgKeyword_AttractModeFadeIn,          fade_in)) return;
    if (GetParam(line, cfgKeyword_AttractModeFadeOut,         fade_out)) return;
    if (GetParam(line, cfgKeyword_AttractModeFadeInPosition,  fade_in_position)) return;
    if (GetParam(line, cfgKeyword_AttractModeFadeOutPosition, fade_out_position)) return;
    if (GetParam(line, cfgKeyword_AttractModeSkipLoad,        skip_load)) return;
  }

  void cfgWrite(ofstream &strm)
  {
    PutParam(strm , cfgKeyword_AttractModeEnable         , enable);
    PutParam(strm , cfgKeyword_AttractModeChoice         , choice);
    PutParam(strm , cfgKeyword_AttractModeInterval       , interval);
    PutParam(strm , cfgKeyword_AttractModeMaxVolume      , max_volume);
    PutParam(strm , cfgKeyword_AttractModeFadeIn         , fade_in);
    PutParam(strm , cfgKeyword_AttractModeFadeOut        , fade_out);
    PutParam(strm , cfgKeyword_AttractModeFadeInPosition , fade_in_position);
    PutParam(strm , cfgKeyword_AttractModeFadeOutPosition, fade_out_position);
    PutParam(strm , cfgKeyword_AttractModeSkipLoad       , skip_load);
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_AttractModeEnable           , cfgKeywordDesc_AttractModeEnable           , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeChoice           , cfgKeywordDesc_AttractModeChoice           , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeInterval         , cfgKeywordDesc_AttractModeInterval         , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeMaxVolume        , cfgKeywordDesc_AttractModeMaxVolume        , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeFadeIn           , cfgKeywordDesc_AttractModeFadeIn           , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeFadeOut          , cfgKeywordDesc_AttractModeFadeOut          , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeFadeInPosition   , cfgKeywordDesc_AttractModeFadeInPosition   , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeFadeOutPosition  , cfgKeywordDesc_AttractModeFadeOutPosition  , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeSkipLoad         , cfgKeywordDesc_AttractModeSkipLoad         , false);
  }

  bool enable { false };
  attract_choice_e choice { attract_choice_e::Random };
  bool skip_load { true };
  time_unit_t interval { TimeUnitOneMinute };
  uint32_t max_volume { MaxSongVolume / 2 };
  time_unit_t fade_in { TimeUnitFiveSeconds };
  time_unit_t fade_out { TimeUnitTenSeconds };
  time_unit_t fade_in_position { TimeUnitSixtySeconds };
  time_unit_t fade_out_position { TimeUnitSeventySeconds };

private:
};

class SoftwareUpdateConfigClass : public ConfigBaseClass
{
  void cfgRead(string line) {};
  void cfgWrite(string line) {};
  void DescribeParams(ofstream &strm, const char *indent) {};
};

class IniSkinListConfigClass : public ConfigBaseClass
{
public:
  void cfgRead(string line)
  {
    string str {};
    if (GetParam(line, cfgKeyword_File, str, false))
    {
      ifstream skinFile;
      skinFile.open(str, ios::in);
      if (skinFile.is_open())
      // make sure file exists and can be opened before we add it to the list...
      {
        skin_file.push_back(str);
        skinFile.close();
        return;
      }
    }
  }

  void cfgWrite(ofstream &strm)
  {
    if (skin_file.size() == 0) // no skin file list (i.e. creating a fresh ini file), so add a few skins...
    {
      skin_file.push_back(DefaultSkinStr);
    }
    
    for (auto &f : skin_file)
    {
      PutParam(strm, cfgKeyword_File, f);
    }
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_File, cfgKeywordDesc_SkinFile, true);
  }

  vector<string> skin_file {};
};


class GeneralConfigClass : public ConfigBaseClass
{
public:
  void cfgRead(string line)
  {
    string str {};
    text_t text {};
    uint32_t uint { 0 };
    sort_songs_by_t song_sort {};
    if (GetParam(line, cfgKeyword_SkinSize, skin_size)) return;
    if (GetParam(line, cfgKeyword_SkinName, skin_name, false)) return;
    if (GetParam(line, cfgKeyword_SkinVersion, skin_version, false)) return;
    if (GetParam(line, cfgKeyword_SkinDescription, str, false))
    {
      skin_desc.push_back(str);
      return;
    }

    if (GetParam(line, cfgKeyword_Screenshot, screenshot, false)) return;
    if (command_line_music_path == false) // only if command line music path(s) not specified
    {
      if (GetParam(line, cfgKeyword_MusicPath, str, false))
      {
        music_path.push_back(str);
        return;
      }
    }
    if (GetParam(line, cfgKeyword_SortSongsBy, song_sort))
    {
      sort_songs_by.push_back(song_sort);
      return;
    }

    if (GetParam(line, cfgKeyword_SelectButtons, str, false))
    {
      select_buttons.push_back(str);
      return;
    }
    if (GetParam(line, cfgKeyword_SelectButtonsSequence,    select_buttons_sequence)) return;
    if (GetParam(line, cfgKeyword_AutoSelect,               auto_select)) return;
    if (GetParam(line, cfgKeyword_InstantPlay,              instant_play)) return;
    if (GetParam(line, cfgKeyword_ScreenJump,               screen_jump)) return;
    if (GetParam(line, cfgKeyword_SelectTimeout,            select_timeout)) return;
    if (GetParam(line, cfgKeyword_SelectHoldTimeout,        select_hold_timeout)) return;
    if (GetParam(line, cfgKeyword_TitleStripAutoTurnTime,   auto_title_strip_turn_time)) return;
    if (GetParam(line, cfgKeyword_NoDuplicates,             no_duplicates)) return;
    if (GetParam(line, cfgKeyword_DuplicatesUseCredits,     duplicates_use_credits)) return;
    if (GetParam(line, cfgKeyword_AttractModeGenre,         str, true))
    {
      attract_mode.push_back(str);
      return;
    }
    if (GetParam(line, cfgKeyword_SongsPerTitleStrip,           songs_per_title_strip)) return;
    if (GetParam(line, cfgKeyword_TitleStripSize,               title_strip_size)) return;
    if (GetParam(line, cfgKeyword_AlbumMode,                    album_mode)) return;
    if (GetParam(line, cfgKeyword_TitleStripBackground,         genre_bkgnd, default_title_strip_bkgnd)) return;
    if (GetParam(line, cfgKeyword_PairSongs,                    pair_songs)) return;
    if (GetParam(line, cfgKeyword_TitleStripMoveStyle,          title_strip_move_style)) return;
    if (GetDescParam(line, cfgKeyword_SongDescription,          song_description)) return;
    if (GetDescParam(line, cfgKeyword_PairedSongDescription,    paired_song_description)) return;
    if (GetDescParam(line, cfgKeyword_ArtistDescription,        artist_description)) return;
    if (GetDescParam(line, cfgKeyword_MatchedArtistDescription, matched_artist_description)) return;
    if (GetDescParam(line, cfgKeyword_ExtraDescription,         str))
    {
      extra_description.push_back(str);
      return;
    }
    if (GetParam(line, cfgKeyword_SongLoadTime,                    song_load_time)) return;
    if (GetParam(line, cfgKeyword_SongUnloadTime,                  song_unload_time)) return;
    if (GetParam(line, cfgKeyword_SongText,                        song_text)) return;
    if (GetParam(line, cfgKeyword_PairedSongText,                  paired_song_text)) return;
    if (GetParam(line, cfgKeyword_ArtistText,                      artist_text)) return;
    if (GetParam(line, cfgKeyword_AlbumText,                       album_text)) return;
    if (GetParam(line, cfgKeyword_ExtraText,                       text))
    {                                                              
      extra_text.push_back(text);                                  
      return;                                                      
    }                                                              
    if (GetParam(line, cfgKeyword_AlbumArtSize,                    album_art_size)) return;
    if (GetParam(line, cfgKeyword_AlbumArtOffset,                  album_art_offset)) return;
    if (GetParam(line, cfgKeyword_AlbumArtAngle,                   album_art_angle)) return;
    if (GetParam(line, cfgKeyword_AlbumModeLineSpacing,            album_song_title_line_spacing)) return;
    if (GetParam(line, cfgKeyword_NowPlayingMissingArtwork,        now_playing_missing_artwork)) return;
    if (GetParam(line, cfgKeyword_AlbumModeMissingArtwork,         album_mode_missing_artwork)) return;
    if (GetParam(line, cfgKeyword_NowPlayingArtworkMode,           now_playing_artwork_mode)) return;
    if (GetParam(line, cfgKeyword_AlbumModeArtworkMode,            album_mode_artwork_mode)) return;
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_SkinSize                       , cfgKeywordDesc_SkinSize                       , false);
    DescribeParam(strm, indent, cfgKeyword_SkinName                       , cfgKeywordDesc_SkinName                       , false);
    DescribeParam(strm, indent, cfgKeyword_SkinVersion                    , cfgKeywordDesc_SkinVersion                    , false);
    DescribeParam(strm, indent, cfgKeyword_SkinDescription                , cfgKeywordDesc_SkinDescription                , true);
    DescribeParam(strm, indent, cfgKeyword_Screenshot                     , cfgKeywordDesc_Screenshot                     , false);
    // DescribeParam(strm, indent, cfgKeyword_Database                       , cfgKeywordDesc_Database                       , false);
    DescribeParam(strm, indent, cfgKeyword_MusicPath                      , cfgKeywordDesc_MusicPath                      , true);
    DescribeParam(strm, indent, cfgKeyword_SortSongsBy                    , cfgKeywordDesc_SortSongsBy                    , true);
    DescribeParam(strm, indent, cfgKeyword_NoDuplicates                   , cfgKeywordDesc_NoDuplicates                   , false);
    DescribeParam(strm, indent, cfgKeyword_DuplicatesUseCredits           , cfgKeywordDesc_DuplicatesUseCredits           , false);
    DescribeParam(strm, indent, cfgKeyword_SelectButtons                  , cfgKeywordDesc_SelectButtons                  , true);
    DescribeParam(strm, indent, cfgKeyword_SelectButtonsSequence          , cfgKeywordDesc_SelectButtonsSequence          , false);
    // DescribeParam(strm, indent, cfgKeyword_CustomMP3Tag                   , cfgKeywordDesc_CustomMP3Tag                   , false);
    DescribeParam(strm, indent, cfgKeyword_AutoSelect                     , cfgKeywordDesc_AutoSelect                     , false);
    DescribeParam(strm, indent, cfgKeyword_InstantPlay                    , cfgKeywordDesc_InstantPlay                    , false);
    DescribeParam(strm, indent, cfgKeyword_ScreenJump                     , cfgKeywordDesc_ScreenJump                     , false);
    DescribeParam(strm, indent, cfgKeyword_SelectTimeout                  , cfgKeywordDesc_SelectTimeout                  , false);
    DescribeParam(strm, indent, cfgKeyword_SelectHoldTimeout              , cfgKeywordDesc_SelectHoldTimeout              , false);
    DescribeParam(strm, indent, cfgKeyword_TitleStripAutoTurnTime         , cfgKeywordDesc_TitleStripAutoTurnTime         , false);
    DescribeParam(strm, indent, cfgKeyword_AttractModeGenre               , cfgKeywordDesc_AttractModeGenre               , true);
    DescribeParam(strm, indent, cfgKeyword_SongsPerTitleStrip             , cfgKeywordDesc_SongsPerTitleStrip             , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumMode                      , cfgKeywordDesc_AlbumMode                      , false);
    DescribeParam(strm, indent, cfgKeyword_TitleStripSize                 , cfgKeywordDesc_TitleStripSize                 , false);
    DescribeParam(strm, indent, cfgKeyword_TitleStripBackground           , cfgKeywordDesc_TitleStripBackground           , false);
    DescribeParam(strm, indent, cfgKeyword_PairSongs                      , cfgKeywordDesc_PairSongs                      , false);
    DescribeParam(strm, indent, cfgKeyword_TitleStripMoveStyle            , cfgKeywordDesc_TitleStripMoveStyle            , false);
    DescribeParam(strm, indent, cfgKeyword_SongDescription                , cfgKeywordDesc_SongDescription                , false);
    DescribeParam(strm, indent, cfgKeyword_PairedSongDescription          , cfgKeywordDesc_PairedSongDescription          , false);
    DescribeParam(strm, indent, cfgKeyword_ArtistDescription              , cfgKeywordDesc_ArtistDescription              , false);
    DescribeParam(strm, indent, cfgKeyword_MatchedArtistDescription       , cfgKeywordDesc_MatchedArtistDescription       , false);
    DescribeParam(strm, indent, cfgKeyword_ExtraDescription               , cfgKeywordDesc_ExtraDescription               , true);
    DescribeParam(strm, indent, cfgKeyword_SongLoadTime                   , cfgKeywordDesc_SongLoadTime                   , false);
    DescribeParam(strm, indent, cfgKeyword_SongUnloadTime                 , cfgKeywordDesc_SongUnloadTime                 , false);
    DescribeParam(strm, indent, cfgKeyword_SongText                       , cfgKeywordDesc_SongText                       , false);
    DescribeParam(strm, indent, cfgKeyword_PairedSongText                 , cfgKeywordDesc_PairedSongText                 , false);
    DescribeParam(strm, indent, cfgKeyword_ArtistText                     , cfgKeywordDesc_ArtistText                     , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumText                      , cfgKeywordDesc_AlbumText                      , false);
    DescribeParam(strm, indent, cfgKeyword_ExtraText                      , cfgKeywordDesc_ExtraText                      , true);
    DescribeParam(strm, indent, cfgKeyword_AlbumArtSize                   , cfgKeywordDesc_AlbumArtSize                   , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumArtOffset                 , cfgKeywordDesc_AlbumArtOffset                 , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumArtAngle                  , cfgKeywordDesc_AlbumArtAngle                  , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumModeLineSpacing           , cfgKeywordDesc_AlbumModeLineSpacing           , false);
    DescribeParam(strm, indent, cfgKeyword_NowPlayingMissingArtwork       , cfgKeywordDesc_NowPlayingMissingArtwork       , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumModeMissingArtwork        , cfgKeywordDesc_AlbumModeMissingArtwork        , false);
    DescribeParam(strm, indent, cfgKeyword_NowPlayingArtworkMode          , cfgKeywordDesc_NowPlayingArtworkMode          , false);
    DescribeParam(strm, indent, cfgKeyword_AlbumModeArtworkMode           , cfgKeywordDesc_AlbumModeArtworkMode           , false);
  }

  string skin_name {};
  string skin_version {};
  vector<string> skin_desc {};
  string screenshot {defaultScreenshotFilename};
  // string database_filename { "fruitbox.db" };
  vector<string> music_path {};
  uint32_t songs_per_title_strip { 10 };
  uints2_t skin_size {};
  dynamics2_t title_strip_size {};
  bool album_mode { false };
  genre_bkgnd_t default_title_strip_bkgnd { nullptr, ""};
  vector<genre_bkgnd_t> genre_bkgnd { };
  // array<uint32_t, NUM_GENRES> genre_to_title_strip_bkgnd_bitmap { 0 }; // each entry is a genre, and points to a title_strip_bkgnd_bitmap vector element
  pair_songs_e pair_songs { pair_songs_e::Yes };
  select_mode_e select_mode { select_mode_e::SelectCode };
  uint32_t num_title_strips { 0 };
  uint32_t screen_jump { 5 };
  bool auto_select { false };
  bool instant_play { false };
  bool no_duplicates { false };
  bool duplicates_use_credits { false };
  time_unit_t auto_title_strip_turn_time { };
  vector<string> select_buttons { };
  select_buttons_sequence_e select_buttons_sequence { select_buttons_sequence_e::RowCol };
  vector<string> attract_mode { GenreOffStr, GenreAnyStr };
  vector<sort_songs_by_t> sort_songs_by { };
  time_unit_t select_timeout { };
  time_unit_t select_hold_timeout { };
  title_strip_style_t title_strip_move_style {};
  string song_description { TitleStripDescriptionsVarStart, static_cast<char>(1) /* TextDescriptionSongTitle */ };
  string paired_song_description { TitleStripDescriptionsVarStart, static_cast<char>(13) /* TextDescriptionPairedSongTitle position in text_description array */ };
  string artist_description { TitleStripDescriptionsVarStart, static_cast<char>(2) /* TextDescriptionSongArtist */ };
  string matched_artist_description { TitleStripDescriptionsVarStart, static_cast<char>(2) /* TextDescriptionSongArtist */ };
  vector<string> extra_description { };
  time_unit_t song_load_time {};
  time_unit_t song_unload_time {};
  text_t artist_text {};
  text_t album_text {};
  vector <text_t> extra_text {};
  text_t song_text {};
  text_t paired_song_text {};
  uints2_t album_art_size {};
  uints2_t album_art_offset {};
  uint32_t album_art_angle {};
  uint32_t album_song_title_line_spacing {};
  bitmap_t now_playing_missing_artwork {};
  bitmap_t album_mode_missing_artwork {};
  artwork_mode_e now_playing_artwork_mode {artwork_mode_e::Auto};
  artwork_mode_e album_mode_artwork_mode {artwork_mode_e::Auto};
};


class ButtonsConfigClass : public ConfigBaseClass {

public:

  void cfgRead(string line)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      if (GetParam(line, default_button[b].name , button[default_button[b].num])) return;
    }
  }

  void cfgWrite(ofstream &strm)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      PutParam(strm, button[b].name.c_str(), button[b].val_str);
    }
  }
  
  void DescribeParams(ofstream &strm, const char *indent)
  {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      DescribeParam(strm, indent, default_button[b].name, default_button[b].desc, false);
    }

  }

  array<button_t, NUM_BUTTONS> button {};
  array<button_t, NUM_BUTTONS> backup_button {};

  void ResetToDefaults(void)
  {
    for (auto b = 0; b < button.size(); ++b)
    // set all keys to keyboard defaults...
    {
      button.at(default_button[b].num).name = default_button[b].name;
      button.at(default_button[b].num).type = input_type_e::Key;
      // button.at(default_button[b].num).type_backup = input_type_e::Key;
      button.at(default_button[b].num).menu_label = default_button[b].menu_label;
      button.at(default_button[b].num).param[EVENT_PARAM_ID] = 0;
      button.at(default_button[b].num).param[EVENT_PARAM_VAL1] = default_button[b].key;
      button.at(default_button[b].num).param[EVENT_PARAM_VAL2] = 0;
      button.at(default_button[b].num).param[EVENT_PARAM_PRESSED] = 0;
      // button.at(default_button[b].num).val_str = string(ButtonTypeKeyStr) + " " + to_string(default_button[b].key);
      button.at(default_button[b].num).val_str = input_event_labels::input_event_label.at(default_button[b].key);

      backup_button[b] = button[b];
    }
  };

  void RegisterTouchAreas(void)
  {
    for (uint32_t b = 0; b < button.size(); ++b)
    {
      if (button[b].skin_touch_area.w && button[b].skin_touch_area.h) // touch area is non-zero...
      {
        button[b].type = input_type_e::Touch;
      }
    }
  }

  ButtonsConfigClass(void)
  {
    ResetToDefaults();
  };

  void BackupUserMappings(void) // make backups of all buttons types (to allow them to be restored after exiting menus)
  {
    for (uint32_t b = 0; b < button.size(); ++b)
    {
      backup_button[b] = button[b];
      // b.type_backup = b.type;
    }
  };

};

class TouchScreenConfigClass : public ConfigBaseClass {

public:

  void cfgRead(string line);
  void cfgWrite(ofstream &strm);

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_Enable           , cfgKeywordDesc_TouchEnable     , false);
    DescribeParam(strm, indent, cfgKeyword_TouchTopLeft     , cfgKeywordDesc_TouchTopLeft    , false);
    DescribeParam(strm, indent, cfgKeyword_TouchBottomRight , cfgKeywordDesc_TouchBottomRight, false);
  }

  TouchScreenConfigClass(void)
  {
  };

  bool enabled { false };
  bool calibrated { false };
  bool tl_calibrated { false };
  bool br_calibrated { false };

  static ints2_t touch_tl; // top left
  static ints2_t touch_br; // bottom right
};

class FontConfigClass : public ConfigBaseClass {
public:
  void cfgRead(string line)
  {
    font_t font {};
    if (GetParam(line, cfgKeyword_File, font))
    {
      fonts.push_back(font);
    }
  };

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DescribeParam(strm, indent, cfgKeyword_File, cfgKeywordDesc_Font, true);
  }

  FontConfigClass* clone() const { return new FontConfigClass(*this); }

  vector<font_t> fonts {};
  font_t font {};

private:
};

class PLSConfigClass : public ConfigBaseClass
{
  void cfgRead(string line) {};
  void DescribeParams(ofstream &strm, const char *indent) {};
};

