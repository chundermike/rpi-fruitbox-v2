#pragma once

const char introduction_str[] = { \
  "Welcome to fruitbox, a customisable, Retro MP3 Jukebox for the Raspberry Pi.\n\n"
  "fruitbox attempts to emulate the operation of classic jukeboxes, by providing a " \
  "music player which operates on the principle of presenting songs on title strips, in " \
  "which the user can select a song by turning through pages of title strips, and selecting " \
  "individual songs by entering a unique code for that song, which is then entered into a play queue.\n\n" \
  "The look and feel of fruitbox is provided by 'skins', which are human readable text files which can be created and modified " \
  "by the user to create an almost infinite number of different jukebox styles.\n\n"
  "fruitbox provides many customisable features, which are described in the 'Configuration (Skin) File' sections of this " \
  "user guide.  A very brief (and by no means exhaustive) summary of its capabilities are...\n\n" \
  "-> MP3 or OGV (video) playback\n" \
  "-> MP3 playback from local files or URL streams (internet Radio)\n" \
  "-> Singles or Albums mode\n" \
  "-> Coin or Freeplay mode\n" \
  "-> Controls easily mappable to keyboards, USB controllers, GPIO, mouse or touch screens\n" \
  "-> Random song play (attract mode) with preview and fade effects\n" \
  "-> Output of Jukebox status via GPIO and/or text files for external status\n" \
  "-> Generation of title strip images for printing\n\n" \
  "fruitbox is free for non-commercial use. If you enjoy using fruitbox, and would like to encourage " \
  "future development, please consider making a donation to the author at https://paypal.me/rpifruitbox"
};

const char starting_up_str[] = { \
  "fruitbox is intended to be run directly from the command line for maximum performance.\n\n" \
  "See section 'Command Line Options' for startup options."
};

const char operation_str[] = { \
  "To run fruitbox, from the command line goto the installation directory and type ./fruitbox\n\n" \
  "fruitbox will then read the skin list in the [skins] section of the fruitbox.ini file and present " \
  "you with a skin chooser to allow you to select your skin (unless there's only one skin defined in the " \
  "[skins] section.  The skin chooser can be bypassed if you want to load a particular skin immediately by " \
  "using the '--skin' command line option and specifying a skin configuration file directly.  For example ...\n\n" \
  "  ./fruitbox --skin skins/Wurly/fruitbox.cfg\n\n" \
  "See section 'Configuration (Skin) Files' for more detail about the contents of these files.  " \
  "After the configuration file has been read, fruitbox will create the song " \
  "database by searching through the MusicPath directories (see section 'Database Creation').  " \
  "When the database has been read, fruitbox will start!\n\n" \
  "Song title strips are moved using the 'Left' and 'Right' buttons, and songs are selected using the select keys.  " \
  "Once a song is selected, it is added to the play queue.  If no song is " \
  "playing, the song at the top of the play queue is 'loaded', played, and then 'unloaded'."
  "\n\nControl inputs (buttons) can be re-defined via an on-screen menu or direcrly editing the [buttons] section of the fruitbox ini file."};


const char command_line_options_str[] = { \
  "fruitbox takes the following command line parameters..."
};

const char ini_file_str[] = { \
  "When starting up, fruitbox looks for an initialisation file (default 'fruitbox.ini') in the same directory " \
  "it is run from, which contains settings which are not skin-specific.  The command line option --ini can be used to specify an alternative ini file.  " \
  "If no ini file is found, it will be created, and you can manually edit it later.  The following list shows each parameter " \
  "in each section.  Note that some of these parameters can also be changed directly from the main menu (accessible via the 'Menu' button).  " \
  "Note that entries marked with a '*' means that these groups / parameters can be defined multiple times." \
  "\n\nNote also that if a touchscreen is detected and the [touch screen] section is not defined (or incomplete), the touch screen " \
  "calibration is automatically run."
};

const char skin_selection_str[] = { \
  "If fruitbox is run with the --skin <file> command line option, that skin will be immediately loaded and used.  " \
  "If no --skin option is specified, fruitbox will invoke the skin chooser for you to select a skin from the list " \
  "of skins specified in the [skins] section of the ini file.  If the [skins] list contains only one entry, then the skin " \
  "chooser is not invoked and the skin immediately loaded, in the same way as if it were specified from the --skin command " \
  "line argument."
};

const char touch_screen_str[] = { \
  "If a touch screen is detected and the skin is designed to support touch input, then fruitbox can use the touch screen " \
  "to accept button presses.  Song selection by pressing the song title within the title strips themselves can also be " \
  "supported.  The [touch screen] section in the fruitbox ini file defines the calibrated touch co-ordinates for the detected " \
  "touch screen.  If no calibration values are present in the ini file, fruitbox will automatically run the touch screen " \
  "calibration on start-up.  To run touch screen calibration again, simply delete the [touch screen] section in the fruitbox " \
  "ini file, or select 'Calibrate Touchscreen' through the Main menu 'Controls' option.\n\n" \
  "If no touch screen is detected but a [mouse] is defined in the fruitbox ini file, then if a mouse is connected " \
  "it can be used instead of a touch screen, using the touch defined areas in the skin file.  Parameters in the " \
  "[mouse] section of the ini file can be used to modify the look and behaviour of the visible mouse pointer."
};

const char menus_str[] = { \
  "Buttons 'Menu' and 'Search' provide access to on-screen menus. Each menu can be controlled directly by touch if a touchscreen is installed, or via the buttons or mouse if not.  " \
  "For mouse or touch operation, an on-screen keyboard is displayed, otherwise the mapped fruitbox buttons are used.  " \
  "In the latter case, the Left and Right keys are used to choose the menu option(s), any other button will select it. After selection, the value can be " \
  "changed by using left/right (boolean or numeric values), or buttons '0' to '9' and 'A' to 'Z' for strings. For string entry, 'Left' is used to " \
  "delete the last character and 'Right' is used to insert a space.  Any other button will exit the editing mode."
};

const char main_menu_str[] = { \
  "The main menu gives access to Global Settings, Button Configuration, Software Update, About information, and Power Off." \
};

const char search_menu_str[] = { \
  "The search menu allows the user to filter out songs in the database, in order to find specific songs.  Several filter fields are provided, " \
  "and entering text into a field causes fruitbox to search for songs containing text within that criteria.  For example...\n\n" \
  "If the text 'Bea' is entered into the Artist field, then fruitbox will only display Artists whose name contains 'Bea' (so for example, " \
  "'The Beatles', 'The Beach Boys', 'Bronski Beat', etc.).  If more than one field contains text, then all non-empty fields must be satisfied for " \
  "the song to be displayed (i.e. Artist : Bea and Year : 1965, will only display songs if the Artist name contains 'Bea', and they are from 1965).  " \
  "Hint: entering for example '198' into the Year field will display all songs from the 1980s."
};

const char cfg_file_str[] = { \
  "Configuration files (skins) define the look and feel of fruitbox.  " \
  "A configuration file is a human-readable text file containing a list of " \
  "parameters and their values.  Parameters are grouped into sections, where " \
  "each section is defined by its name enclosed in square brackets, followed " \
  "by the parameter list for that section.  The order of sections is not important " \
  "except when the section refers to a display object, in which case the order of the " \
  "sections determines the render order on the display.\n\n" \
  "A parameter is defined by specifying its name, followed by its parameter value(s).  " \
  "The parameter name and values can be separated by whitespace, = or :.  " \
  "Parameter values can be strings, numeric decimal values, or boolean values (true, false, " \
  "enable, disable, on, off, yes, no, 0, 1).\n\n" \
  "Parameter values in <> brackets are compulsory, and those in [] are optional.\n\n" \
  "Comments can be included in the configuration " \
  "file by prefixing any comment text with the '#' character.\n\n" \
  "The following list shows all the possible parameters for each section.  If a parameter is " \
  "not specified in the configuration file, fruitbox will use a default value.\n\nNote that entries marked " \
  "with a '*' means that these groups / parameters can be defined multiple times.\n" \
  "Note: filenames for 'MusicPath' parameters have file paths relative to the directory fruitbox " \
  "was run from, whereas filenames for all other parameters (sound files, bitmap files, status text files, font files) " \
  "have paths which are relative to the directory the configuration file itself is in.  This allows configuration files " \
  "and their associated content files to be kept together, but easily share common MusicPath(s) with other skins."
};

const char buttons_def_str[] = { \
  "The fruitbox input controls can be modified via the Controls menu.  " \
  "By default, the buttons are mapped to keyboard keys (see section 'Default Buttons'), " \
  "but each key can be re-mapped to any of the following...\n\n" \
  "1. Keyboard key\n" \
  "2. GPIO input pin\n" \
  "3. USB game controllers (joystick stick / button)\n" \
  "4. Region on touch screen\n" \
  "\nFor touch screen buttons, the touch areas are defined in the skin file itself, using the [touch buttons] " \
  "section, because these are skin-related.  If any buttons are defined in the skins' [touch buttons] section " \
  "and a touch screen is detected, the user-defined mapping for that button is ignored and set to touch input."
};

const char font_text_def_str[] = { \
  "The configuration file [fonts] section allows multiple fonts of different sizes " \
  "to be loaded and used by different display elements.  This removes the need for each text " \
  "definition to load it's own font, instead referencing a specific font type and size from " \
  "the 'font pool'.  Note that the order in which the fonts are define in the [fonts] section " \
  "determines their font number, starting at 1.  Font number 0 is the internal fruitbox font " \
  "used for the on-screen menus etc.\n\n" \
  "Text definitions ([general] ArtistText, [general] SongText, [general] PairedSongText, [general] ExtraText and [status] Text) " \
  "parameters have the following arguments...\n\n" \
  "<font> <colour> <alignment> <capitalise> <mode> <quoted> <offset (x y)> <max_width>\n\n" \
  "       font : number of font from 'font pool' (0..)\n"
  "              note that the fonts in the pool are numbered in\n" \
  "              the order in which they are defined in the\n" \
  "              [fonts] section of the skin configuration file\n" \
  "     colour : red green blue alpha (0..255)\n" \
  "              (alpha : 0 completely transparent\n" \
  "              through to 255 completely opaque)\n" \
  "  alignment : 'Left', 'Centre' or 'Right'\n" \
  " capitalise : 'Yes' or 'No'\n" \
  "       mode : 0 : text is displayed normally\n" \
  "             -1 : Condense ... wide text is horizontally squashed\n" \
  "                  to fit within max_width\n" \
  "              1..n : Scroll ... text is scrolled at the specified\n" \
  "                 speed (1 = slowest) if it doesn't fit into\n" \
  "                 max_width (See Note below)\n" \
  "     quoted : 'Yes' (text is wrapped within double-quotes),\n" \
  "              'No' text is unmodified\n" \
  "     offset : x y (text position is shifted by these amounts\n" \
  "              in pixels)\n" \
  "  max_width : The maximum width of the text.  If the text is\n" \
  "              wider than this, then it will be shrunk to the\n" \
  "              maximum width (if the 'mode' option is -1), or\n" \
  "              scrolled within this width (if mode > 0)\n\n" \
  " Note : scrolling text is only supported for status object text (not title strip text)\n"
};

const char command_line_help_option_str[] = { \
  "Show basic help and version information."
};

const char command_line_user_guide_option_str[] = { \
  "Create this user-guide to file \"userguide.txt\"."
};

const char command_line_no_splash_option_str[] = { \
  "Disable the fruitbox logo splash screen on startup"
};

const char command_line_database_option_str[] = { \
  "Use the specified database instead of the one specified in the skin"
};

const char command_line_musicpath_option_str[] = { \
  "Use the specified music path instead of the one specified in the skin or ini files.  Note that the --music-path " \
  "option can be specified multiple times if the user wishes to construct the database from multiple sources."
};

const char command_line_load_playlist_str[] = { \
  "Loads a playlist file and populates the play queue with the songs in it; fruitbox will begin playing the songs after it has " \
  "started up."
};

const char command_line_save_playlist_str[] = { \
  "When fruitbox exits (by the user pressing the 'Quit' button), this option saves the contents of the play queue (and currently playing " \
  "song) to the specified file.  This can subsequently be loaded back into fruitbox using the '--load-playlist' command line " \
  "argument.  The playlist file contains a list of song filenames which can easily be edited by hand to modify the playlist as required."
};

const char command_line_dump_title_strips_str[] = { \
  "This option causes every title strip to be written to a unique png image file. fruitbox will then quit without running.  " \
  "If fruitbox is used in a real jukebox which has real (paper) title strips and not on-screen ones, then this can be used to generate " \
  "the title strips with real song data for printing out.  The user can modify the style and contents of the title strips in the " \
  "usual way using skin parameters. In order to supress the displaying of the actual title strips on the screen, you can just set the \"Visible\" " \
  "flag of each title strip to \"No\".\n\nNote that the --dump-title-strips option must be used in conjunction with a specified skin (--skin option) since the title " \
  "strips are defined in the skin."
};

const char command_line_display_size_str[] = { \
  "This option specifies the size of the display that fruitbox creates when starting up.  If not specified, then the display size " \
  "is auto-detected.  The display size does not have to be the same as the skin size, as fruitbox will scale the skin size to match " \
  "the display size."
};

// const char command_line_choose_cfg_str[] = { \
  // "This option allows the user to choose a configuration file (skin) from a menu when fruitbox starts up, rather than specifying it using " \
  // "the '--skin' command line option.  The <file> parameter, should contain a list of cfg files to choose from.  Each entry takes the form " \
  // "'File = <file>' (path and name of a skin's cfg file).\n\n" \
  // "fruitbox will allow the user to cycle through the list of files using the Left and Right buttons.  Any other button will select the " \
  // "skin.  The 'SkinName' and 'SkinDescription' values in the skin cfg files will be used to display information about each skin. A preview of the skin is shown if " \
  // "a screenshot file exists (by default, 'screenshot.jpg' in the same directory as the cfg file, or the name of the 'Screenshot' parameter value " \
  // "in the skin configuration file).  Note that screenshot files can be generated with the '--screenshot' command line option."
// };

const char command_line_no_scale_str[] = { \
  "Normally fruitbox will scale (resize) the skin to the display, so no matter what its size, it will always fit exactly.  " \
  "This option turns off the scaling so the skin will be shown at its original size (useful for debugging skin designs).  The skin " \
  "will be centered on the display.  If the skin is smaller than the display then the skin will be surrounded by a black border, but " \
  "if the skin is larger than the display, the outer edges of the skin will not be visible."
};

const char command_line_rotate_str[] = { \
  "This option allows the display to be rotated by <angle> degrees.  Please note that if using a touch based skin, " \
  "this will affect operation of the touch co-ordinates and the skin may have to be modified."
};

// const char command_line_touch_tl_str[] = { \
  // "These values can be used to define the co-ordinates of the top left corner of the touch screen (usually 0 0, but some touchscreens have a different value).  " \
  // "If not specified, will default to 0 0."
// };

// const char command_line_touch_br_str[] = { \
  // "These values can be used to define the co-ordinates of the bottom right corner of the touch screen (usually the size of the touch screen, " \
  // "but some touchscreens have a different value).  If not specified, will default to the size of the detected display."
// };

const char command_line_ini_file_str[] = { \
  "Name of initialisation file (defaults to 'fruitbox.ini' if not specified). " \
  "This file contains all the non-skin specific fruitbox parameters."
};

// const char command_line_button_map_str[] = { \
  // "Name of button mapping file (defaults to 'fruitbox.btn' if not specified)"
// };
// const char command_line_gpio_scan_row_str[] = { \
  // "These values define the GPIo pin numbers used to form the rows of the GPIO button matrix."
// };

// const char command_line_gpio_scan_col_str[] = { \
  // "These values define the GPIo pin numbers used to form the columns of the GPIO button matrix.\n\n" \
  // "Together with the rows, the columns form a matrix; the matrix is used to allow more buttons than GPIO pins to be " \
  // "defined.  Each row/column intersection on the matrix can be used to connect a button; an example is shown below.  Note " \
  // "that the size and shapre of the matrix is user defined, according to how many rows and columns are defined..." \
  // "***PICTURE OF MATRIX HERE ********"
// };

const char command_line_debug_song_nums_option_str[] = { \
  "Show select code alongside song entries."
};

const char command_line_no_db_refresh_option_str[] = { \
  "Normally fruitbox will refresh the database if any database files (fruitbox.db) have a modification time earler than the contents of the directories they are in.  " \
  "This option disables this check, so it is up to the user to delete the database file(s) in order for them to be refreshed."
};

const char command_line_force_db_refresh_option_str[] = { \
  "Normally fruitbox will refresh the database if any database files (fruitbox.db) have a modification time earler than the contents of the directories they are in.  " \
  "This option overrides this check, and always refreshes the database file(s).  This is useful if the user for example changes anything which is created " \
  "or used when the database is created (i.e. CustomMP3Tag)."
};

const char command_line_version_option_str[] = { \
  "Reports the version number."
};

const char command_line_skin_option_str[] = { \
  "This option determines which skin (configuration file) is used.  If omitted, " \
  "then fruitbox will use the [skins] section in the ini file to determine which skin " \
  "to use.  If more than one skin is defined in the [skins] section, then fruitbox will " \
  "allow the user to choose a skin from an on-screen menu."  
};

const char database_creation_str[] = { \
  "Once fruitbox has read the skin file and found no problems, it will try to load the music database.  " \
  "The database is built from multiple 'fruitbox.db' files which are created in each sub-directory in the MusicPath(s) " \
  "which contain music files (mp3, ogv, m3u, pls). Each fruitbox.db file contains a list of music files in that directory," \
  " along with their extracted metadata (mp3 tags). If fruitbox finds music files without an accompanying fruitbox.db file, it will " \
  "create a fruitbox.db file in that directory. This may take some time as fruitbox extracts the metadata from the music file(s), " \
  "but only needs to be done once, so subsequent fruitbox start-ups will be much faster.  If fruitbox detects that an existing " \
  "fruitbox.db file has been modified earlier than the directory it is in (for example if music files have been added or removed), " \
  "it will automatically refresh the fruitbox.db file (unless the --no-database-refresh command line option is specified).\n\n" \
  "MusicPath(s) can be specified in one of three places; fruitbox ini file, skin configuration file or --music-path command line option(s)." \
  "  They can be defined in more than one place, but the --music-path option overrides the skin configuration file, which in turn overrides " \
  "the fruitbox ini file.\n\n"
  "The database files can be edited by hand in a standard text editor if you have small changes to make or are feeling brave!  This can be useful " \
  "if you wish to tweak the song details, without having to re-generate the database from scratch.  " \
  "Note that the song order in the database files are irrelevant; after fruitbox has read the songs from the database files it will sort them " \
  "according to the 'SortSongsBy' configuration parameter(s)." \
};

const char mp3_file_support_str[] = { \
  "During database creation, any file in the MusicPath (or sub-directories) with .mp3 extension will be added to the database. " \
  "fruitbox will extract the mp3 metadata tag values (title, artist, album, etc.) from the files and store these details in the database " \
  "files for faster subsequent start-up of fruitbox."
};

const char ogv_file_support_str[] = { \
  "fruitbox can play video files if they are in ogv format (Vorbis + Theora). During database creation, any file in the " \
  "MusicPath (or sub-directories) with .ogv extension will be added to the database. fruitbox cannot extract metadata from the ogv " \
  "files, so will extract the artist and song title name from the filename if the filename (excluding .ogv extension) has the format " \
  "\"Artist - Title\", and set all other fields (album, genre, etc) to Unknown. The user can subsequently edit the database file to " \
  "manually add meaningful names to the unknown fields.\n\n" \
  "Any video format can be converted to ogv format using for example ffmpeg with the following options for specifying the video bitrate and " \
  "video picture size...\n\n" \
  "  ffmpeg -i MyVideo.mp4 -b:v 2M -vf scale=640x480 MyVideo.ogv\n\n" \
  "  NOTE: ffmpeg versions above 4.1 onwards seem to cause corruption of the video.  It is recommended " \
  "        to use ffmpeg version 4.0.2 (or older) ... see: https://www.videohelp.com/software/ffmpeg/old-versions\n\n" \
  "Since the video decoding process is quite CPU intensive, it is recommended that a Quad core Pi is used (Model 2 or 3) with a good PSU (at least 2 Amps) when running fruitbox " \
  "and skins with video content, and the display resolution is kept low (less than 1024x768)." 
};

const char mp3_stream_support_str[] = { \
  "fruitbox can play mp3 files sourced from url streams (internet radio).  During database creation, any file in the MusicPath (or sub-directories) " \
  "with .pls or .m3u extensions will be added to the database. For .m3u files, fruitbox will first extract the Artist and Title names from the " \
  "#EXTINF entries (if in the format \"Artist - Title\").  For .pls files, for each File* entry, fruitbox will first extract the Title from it's " \
  "corresponding Title* entry.\n\n" \
  "For both .m3u and .pls files, fruitbox will request the ICY Header from the stream server (during database creation) " \
  "and, if available, assign the icy-name to the Title name, and the icy-description to the Artist name. During playback of mp3 " \
  "streams, fruitbox will extract ICY (SHOUTcast) metadata to display real-time StreamTitle information (ie. currently playing song).\n\n"
  "Note: .pls and .m3u files for internet radio stations can be found on the internet.  A good source is https://www.internet-radio.com/"
};

const char dynamics_pre_str[] = { \
  "Dynamic parameter values (specified as [dynamic] in the above parameter descriptions), are optional values which extend " \
  "the usefulness of the parameter.  They can be applied to the Position, Size, Clip, Angle and/or Tint of displayable objects, and are used " \
  "to modify the parameter value in real-time.  The format of the dynamic value field is \"[max_value mode <param>]\".  Note the square " \
  "brackets must be specified in order for the dynamic values to be recognised.  The parameter value will change between the initial value and the " \
  "'max_value'.  How the value changes is given by the 'mode', which can be one of the following strings :"
};

const char dynamics_post_str[] = { \
  "Examples...\n\n" \
  "Size = 100 [200 ${VOLUME}] 150\n\n...will create an object whose horizontal size ranges from 100 to 200 depending upon the volume, " \
  "and whose vertical size is fixed at 150.\n\n"
  "Position = 100 150 [250 ${SPECTRUM_BAND} 2] \n\n...will create an object whose horizontal position is fixed at 100, and whose vertical position " \
  "ranges from 150 to 250 depending upon the value of the audio spectrum frequency band number 2\n\n" \
  "Tint = 100 150 75 [255 ${RANDOM}] 200\n\n...will create an object whose tint values red, green and alpha elements are fixed at 100, 150 and 200 " \
  "respectively, but whose blue element randomly changes between 75 and 255 in real time."
};

const char timers_str[] = { \
  "Several skin parameters are specified in terms of time.  The (integer and fractional) time value can be appended with " \
  "\"ticks\", \"seconds\", \"minutes\" or \"hours\" (defaults to ticks if no units are specified). \"ticks\" refers to the number of " \
  "video frame ticks.  So for example at 60Hz, a time value of 120 equals 2 seconds.  When starting up, " \
  "fruitbox will detect the video display and print out the frame rate (along with the resolution).  Specifying the time " \
  "in ticks is useful for animation, which is synced to the video display, but otherwise it is recommended to use conventional " \
  "time units for non display parameters (for example SongLoadTime) which means the time is not dependant upon the video frame rate, which can vary " \
  "depending on which display device is connected and how it's configured."
};

const char status_bitmaps_str[] = { \
  "There are two ways of specifying bitmaps in status objects...\n\n" \
  "Using one or more 'Bitmap' parameters.  This preloads the bitmaps on startup, so the number is limited " \
  "by the GPU memory, but allows for fast switching for full-frame rate animation.\n\n"
  "Alternatively, the 'BitmapDirectory' can be used.  This specifies a location on the file system in " \
  "which image files are stored (.bmp, .jpg, .png).  fruitbox only loads these into GPU memory when needed, " \
  "so is slower, but there is no limit on the number of image files.  This is more suitable for use in slide-show " \
  "displays for example.\n\n"
  "Animated GIF files can be supported by splitting the GIF file into individual files (by using 'ffmpeg -i file.gif file%02d.jpg' for example), " \
  "including them in a [status] section with multiple 'Bitmap' entries, and specifying the animation speed with 'TimerTickPeriod'.  Then " \
  "in your status Contents text file include the text '${IF_TIMER_TICK}${DRAW_BITMAP}'."
};

const char display_str[] = { \
  "The skin file contains a SkinSize parameter; this indicates the intended size of the skin.  fruitbox " \
  "will scale the skin size to the actual video screen size as necessary."
};

const char freeplay_or_coin_str[] = { \
  "fruitbox can operate in free play or coin mode.  In freeplay mode, no coins (or credits) need to be inserted to add a " \
  "song to the play queue.  In coin mode, fruitbox can support up to six coin buttons.  Each coin button has its own " \
  "'CreditsPerCoin' value, so that fruitbox can mimic jukeboxes which have multiple coin slots, for different coin " \
  "denominations.  The 'CreditsPerCoin' value determines how many credits are added when the coin is inserted.\n\n" \
  "The 'CreditsPerSong' parameter determines how many credits are used when a song is selected.  " \
  "All six 'CreditsPerCoin' parameters are ignored if fruitbox is in free play mode."
};

const char instant_play_str[] = { \
  "If the InstantPlay parameter is enabled in the skin configuration file, then the playqueue is bypassed.  When a song " \
  "is selected, any currently playing song is immediately stopped, and the selected song started.  This can be useful " \
  "when streaming mp3s from url sources (internet radio), which effectively have an infinite duration and hence don't naturally stop."
};

const char spectrum_str[] = { \
  "A [spectrum] object allows an audio frequency spectrum to be displayed for the mp3 songs (not ogv videos).  " \
  "Multiple [spectrum] objects can be defined.  Various options allow great flexibility in the visual appearance." \
  "  For example, the user has control over the look of each of the 32 possible frquency bands, and which are visible."
};

const char joystick_str[] = { \
  "If a [joystick] object is specified in the ini file, then joystick mode is activated.  " \
  "This allows a song to be chosen using the 'Up', 'Down', 'Left' and 'Right' buttons " \
  "instead of entering the select code, and is useful for running fruitbox in arcade cabinets for example, where buttons are limited.  " \
  "Pressing the 'Select' button will then add that song to the play queue (AutoSelect mode is disabled when joystick mode is active).\n\n" \
  "The joystick image specified is positioned in the same place as the song title being selected, and its size " \
  "is calculated to fit exactly into the region containing the song title.  Specifying the 'Size' parameter in the " \
  "configuration file allows the size to be set manually, for example if the highlighted bitmap needs to overlap the song " \
  "title region.  The 'Offset' parameter can then be used to adjust the position of the highlighter precisely around the song " \
  "title region."
};

const char touch_areas_str[] = { \
  "Touch Song mode is activated by defining the [touch song] Bitmap parameter, and if a touchsreen has been detected " \
  "(or a mouse has been detected and enabled).  " \
  "This option over-rides joystick mode if that has also been defined (using the [joystick] object).\n\n" \
  "In touch song mode, the user can touch the song title areas themselves to select a song, rather " \
  "than using select buttons.  Note that the song touch areas default to the title strip area holding the song name, " \
  "but their size and position can be adjusted by using the [touch song] 'Size' and 'Offset' parameters.  " \
  "As well as enabling touch song mode, the [touch song] Bitmap parameter specifies an image file which is displayed over the song area when being touched." \
  "\n\nIf any button assignments are specified in the [touch buttons] section, then (if a touchscreen has been detected) that area will trigger the corresponding button " \
  "press event if touched.  Furthermore, if the optional image file parameter is specified, then that image will be drawn " \
  "whilst that area of the display is touched, allowing simple button press animation effects.\n\n" \
  "Note : if a button area has been defined in the [touch buttons] section, and a touch screen has been detected, then that button " \
  "will be automatically configured as a touch input, over-riding any mapping in the fruitbox ini file."
};

const char mouse_str[] = { \
  "If the mouse is defined and enabled in the [mouse] section of the ini file, then mouse mode is activated.  " \
  "This mode allows a mouse to be used to select songs in a similar way to touch mode, in that touch areas and touch song " \
  "operation is activated, but responsive to the mouse pointer and left mouse button in addition to touch input.  This allows all " \
  "skins designed for touch to be used without touch devices."
};

const char random_songs_str[] = { \
  "fruitbox can play random songs in one of two ways...\n" \
  "  1. The user pressing the 'Random' button\n" \
  "  2. fruitbox selecting a random song in attract mode\n\n" \
  "In either case, fruitbox will attempt to prevent songs being repeatedly " \
  "played by only picking a song if it doesn't appear in it's song play history and current playqueue. " \
  "The size of the history list can be changed with the 'SongHistoryDepth' configuration " \
  "parameter.  If this is large and the number of songs in the database is relatively " \
  "small, then fruitbox may not be able to quickly choose a random song which has not previously " \
  "been played within the history and current play queue, so will just play a random song anyway even if it already been " \
  "played recently." \
};

const char screen_layout_str[] = { \
  "The display is built using a combination of the following objects, as defined in the skin file:\n" \
  "\n" \
  "1. [title strip] object       : a region which contains songs\n" \
  "                                See title strips section for more details\n" \
  "2.      [bitmap] object       : a region which contains a static bitmap\n" \
  "                                This can be used for background and foregrounds for example\n" \
  "3.      [status] object       : a region containing status information\n" \
  "                                See status box section for more details\n" \
  "4.    [spectrum] object       : a region containing an audio spectrum analyser\n" \
  "                                See spectrum section for more details\n" \
  "5.  [touch song] object       : a region containing a bitmap highlighting a song name when touched.\n" \
  "                                See touch song section for more details.\n" \
  "5.  [touch buttons] object(s) : region(s) containing a bitmap displayed when a touch button is pressed.\n" \
  "                                See touch button section for more details.\n" \
  "\n" \
  "Note that there is no limit on the number of objects which can be defined.  They are rendered to the " \
  "display in the order that they are defined in the skin file."
};

const char albums_singles_mode_str[] = { \
  "Fruitbox has two distinct modes - Albums and Singles, specified by the 'AlbumMode' parameter.\n\n" \
  "In Singles mode, each song is individually selectable, and each title strip displays a number of songs (or pairs of songs), each along " \
  "with the artist name.  'ArtistText', 'SongText', 'PairedSongText', 'PairSongs' and 'SongsPerTitleStrip' configuration parameters can be used adjust the appearance of " \
  "the song details on the title strips.\n\n" \
  "In Albums mode, each title strip shows the album title, album artist, album cover art, and list of songs in the album (upto the " \
  "SongsPerTitleStrip value).  One selection will add all the songs in the album to the play queue in one go (assuming, in non-freeplay " \
  "mode, there are sufficient credits).  'AlbumText', 'ArtistText', 'SongText', 'PairedSongText', 'AlbumArtSize', 'AlbumArtOffset' and 'SongsPerTitleStrip' " \
  "configuration parameters can be used adjust the appearance of the album details on the title strips.  Also note that 'PairedSongDescription' " \
  "is used to define the contents of the line which is associated with the 'AlbumText' parameter, and all of the " \
  "'Paired*' Description values are ignored (as these are only relevant for singles mode song pairs)."
};

const char title_strips_str[] = { \
  "TitleStrips are the regions in the display which contain the songs.  In Singles mode, song titles** are listed vertically, and shown along with the artist name.  " \
  "If 'PairSongs' is enabled, then the songs are arranged in pairs with the artist name*** shown in between them (i.e. side A/B).  In Albums mode, "\
  "the title strip contains details about the album in addition to the song list (see section 'Albums / Singles Mode' for more details).\n\n" \
  "Songs are sorted in the order according to the 'SortSongsBy' configuration parameter.  " \
  "Songs in each title strip (in Singles mode), or title strips themselves (in Albums mode) are assigned their own unique select code.  The " \
  "command line option '--debug-song-nums' can be used to make these codes visible; useful when developing skins.\n\n" \
  "TitleStrips automatically move and update their contents when the 'Left' or 'Right' buttons are pressed.  The look and movement of the title strips is " \
  "determined by 'TitleStripMoveStyle' parameter in the skin file, as follows:\n\n" \
  "  TitleStripMoveStyle <speed> <effect> <fade>\n\n" \
  "       <speed>\n" \
  "         1..x = higher number = faster title strip turn (0 = instant)\n" \
  "       <effect> ...\n" \
  "            0 = swipe horizontally\n" \
  "            1 = swipe vertically\n" \
  "            2 = reveal horizontally\n" \
  "            3 = reveal vertically\n" \
  "            4 = turn horizontally\n" \
  "            5 = turn vertically\n" \
  "            6 = dissolve\n" \
  "        <fade>\n" \
  "          no  = title strips don't fade\n" \
  "          yes = title strips fade to black" \
  "\n\nNotes:\n\n" \
  " ** The 'SongDescription' and 'PairedSongDescription' configuration parameters can be used to modify the text displayed on the song lines of the title strip(s) " \
  " ('PairedSongDescription' is only used if 'PairSongs' is not set to false)\n" \
  "*** The 'ArtistDescription' configuration parameter works in the same way as the 'SongDescription' parameter, but affects the " \
  "artist name text in the title strip(s) rather than the song title text.\n\n" \
  "Note that as well as fixed text, the *Description parameters can also contain one or more of the following reserved keywords which will be replaced by actual song details..."
};

const char sound_effects_str[] = { \
  "Sound effects can be added in status objects by using the Sound parameter.  " \
  "These are then referenced in the status Contents file using the ${PLAY_SOUND} and ${STOP_SOUND} " \
  "variables.  This flexibility allows sound effects to be played under many different conditions, such " \
  "as ... button presses, song loading/unloading, coin insertion, title strip movements, song selections, etc."
};

const char status_flags_str[] = { \
  "Four status flags allow for inter-status communication and user triggered status events.  " \
  "Each status flag can be set high or low from button presses (toggle) and/or status $variables.  The values " \
  "of the flags can be read in status objects, allowing support for functionality such as...\n\n" \
  "1. Inter status communication:\n" \
  "for example one status object could toggle a flag with a certain timer tick period " \
  "which could then be detected in a different status object with a different timer tick period. This would " \
  "allow status to \"time-out\" after being started from a different timer period (or a button press).\n\n" \
  "2. Button invoked status display:\n" \
  "The 'Flag*' buttons can be used to turn on and off status information.\n\n" \
  "In addition to the above, the DynamicEnableFlag parameter in some display objects can be used to directly enable or disable " \
  "any dynamic parameters the object has."
};

const char gpio_str[] = { \
  "fruitbox can use the GPIO pins for both input and output:\n\nWhen a button is defined which uses a GPIO pin, the GPIO " \
  "pin is automatically configured as an input, with an internal pullup resistor.  You then just have to ensure that the " \
  "hardware button is connected between this GPIO pin and GND.  Both normally-open and normally-closed switches are supported " \
  "(fruitbox will auto-detect the type on power-up, so ensure no buttons are pressed when fruitbox is started).\n\nWhen a ${SET_GPIO*} variable is encountered in a status object " \
  "Contents file, the specified GPIO pin is automatically configured as an output.\n\n" \
  "Note that if the same pin is defined in both the button mapping file and a status object, then input will take precedence over the " \
  "output, hence the status output will not work.\n\nThe fruitbox developer assumes no responsibility for any damage caused to the " \
  "Raspberry Pi or connected hardware due to the use of the GPIO pins from fruitbox, so please make sure you choose your GPIO pin " \
  "assignments carefully ;)"
};

const char status_boxes_pre_var_str[] = { \
  "Status Boxes provide a very flexible way of displaying real-time text-based information, fixed and animated bitmaps, video clips and sound effects.  " \
  "Using the 'Output' parameter also allows the status information to be written to an external file to be parsed by external applications*.  " \
  "Examples of status include 'Now Playing' information, 'Coming Up' song list, Select Code, Credits, etc.  Each status box defined should have a 'Contents' " \
  "file associated with it.  This is a file that contains human readable text which indicates what is drawn in the status box.\n\n" \
  "As well as fixed text, the user can also specify the following predefined variables, which represent song details and jukebox " \
  "status, and also enable text and bitmaps to be conditionally drawn under many different circumstances.  The GPIO related predefined " \
  "variables allow GPIO pins to be driven with high or low values under different fruitbox conditions.\n\n" \
  "* Note: outputting status to a text file can be done as well as displaying the status on the display, or instead of " \
  "(to supress the status being rendered to the display, do not define the 'Size' parameter (or set width and/or height to zero)."
};

const char status_videos_str[] = { \
  "Status boxes can be used to display either video clips or music videos.  " \
  "If the Video parameter is specified in the [status] object, any reference to VIDEO in the status Contents file variables, i.e. ${DRAW_VIDEO} " \
  "will refer to the video clip specified by the Video parameter.  If the Video parameter is not specified, any VIDEO $variables will refer to " \
  "the currently playing song (if it's a video file)." \
};

const char status_boxes_post_var_str[] = { \
  "The variables beginning ${IF_*}, ${IF_NOT_*} and ${ELSE} are used to conditionally display or ignore the text in the config file which follows it, " \
  "upto the next ${END_IF} (or end of the line).  Note that IF conditions cannot span lines in the text file (unless the line ends with the '\\' line concatentation character).  Variables which do not " \
  "begin with ${IF specify dedicated jukebox status such as song names, etc.\n\n" \
  "Each line in the Contents file corresponds to a unique line in the status output, and are therefore treated separately. A single line in " \
  "the status object can be split across multiple lines in the Contents file, to aid readability.  If a line ends with the '\\' character, " \
  "then it is joined with the following line, allowing long and/or " \
  "complex expressions to be split across multiple lines, but treated as one line entry.\n\n" \
  "Each status box can also include images for cover art for the currently playing song, and other user defined bitmaps.  " \
  "Any image will be scaled to cover the entire status box.\n\n" \
  "Hint: For best performance, it is advisable to limit the number of $ variables in a status box.  " \
  "It is better to group status variables together depending upon when they change; for example try " \
  "not to mix status which changes regularly (like now playing elapsed time) with status that " \
  "doesn't change regularly (such as 'coming up' status) in one status box.  This is because the entire " \
  "contents of a status box is re-drawn if just one element changes."
};

const char button_control_summary_str[] = { \
  "The button controls are mapped to the following keyboard keys by default, but can be re-mapped to " \
  "other keyboard keys, GPIO inputs, USB game controllers or touch screen inputs defined in the fruitbox ini file.\n\n" \
  "    Keyboard Key   fruitbox button     Description\n" \
  " ---------------   ------------------- --------------------------\n" \
  "            LEFT : Left .............. Move title strips left\n" \
  "           RIGHT : Right ............. Move title strips right\n" \
  "               [ : LeftScreen ........ Move to previous screen\n" \
  "               ] : RightScreen ....... Move to next screen\n" \
  "               , : LeftSort .......... Move to prev sort section*\n" \
  "               . : RightSort ......... Move to next sort section*\n" \
  "              UP : Up ................ Move song selection up (joystick mode only)\n" \
  "            DOWN : Down .............. Move song selection down (joystick mode only)\n" \
  " 0 to 9 / A to Z : Select0..SelectZ .. Song selection\n" \
  "           ENTER : Select ............ Select song\n" \
  "              F1 : Coin1 ............. Insert coin\n" \
  "              F2 : Coin2 ............. Insert coin\n" \
  "              F3 : Coin3 ............. Insert coin\n" \
  "              F4 : Coin4 ............. Insert coin\n" \
  "              F5 : Coin5 ............. Insert coin\n" \
  "              F6 : Coin6 ............. Insert coin\n" \
  "              F7 : Flag1 ............. Toggle status flag 1\n" \
  "              F8 : Flag2 ............. Toggle status flag 2\n" \
  "              F9 : Flag3 ............. Toggle status flag 3\n" \
  "             F10 : Flag4 ............. Toggle status flag 4\n" \
  "           SPACE : Random ............ Select random song\n" \
  "       BACKSPACE : Skip .............. Skip (stops currently playing song)\n" \
  "               ; : Pause ............. pause (pauses/unpauses currently playing song)\n" \
  "               ' : AttractMode ....... Toggle Attract Mode\n" \
  "             F11 : LoopQueue ......... Toggle Loop mode\n" \
  "             F12 : FreePlay .......... Toggle Free Play mode\n" \
  "          DELETE : ClearQueue ........ Clear all songs in play queue\n" \
  "               = : VolUp ............. Song volume up\n" \
  "               - : VolDown ........... Song volume down\n" \
  "       LEFT CTRL : Mute .............. Mute / Unmute song and sound effects\n" \
  "      RIGHT CTRL : Screenshot ........ Take Screenshot\n" \
  "   FORWARD SLASH : Search ............ Search Filter Menu\n" \
  "             TAB : Menu .............. Main Menu\n" \
  "             ESC : Quit .............. Quit fruitbox\n" \
  "           SYSRQ : PowerOff .......... Power off Raspberry Pi\n\n" \
  " * The sort sections start with a new letter of the alphabet corresponding to " \
  "the last SortSongsBy value.  For example, if the last SortSongsBy = Artist, " \
  "and the currently displayed artists begin with 'B', then pressing 'LeftSort' " \
  "will move to the screen which contains the first title strip which contains the first Artist beginning with the letter 'A'.\n\n" \
  "The 'Screenshot' button is used to capture the screen, and write the image to 'screenshot.jpg' in the skin directory " \
  "by default or the value of the 'Screenshot' parameter in the skin configuration file." \
  
};

const char troubleshooting_str[] = { \
  "Poor graphics performance is usually caused by not allocating enough memory to the GPU.  " \
  "If the display is very sluggish, or is corrupted / flashing white, quit fruitbox and check " \
  "for any 'GetError_0x505' messages.  These messages mean the GPU hasn't got enough memory to " \
  "create the graphics in video memory, so has to use (slower) CPU memory instead.  To fix this, " \
  "change the Raspberry Pi memory split using the Advanced Options in the raspi-config (type " \
  "'sudo raspi-config' from the command line).  256M is recommended for the GPU, but more may be " \
  "needed if the skin contains lots of large graphics objects."
};

const char hints_and_tips_str[] = { \
  "Automatically run fruitbox on power up\n" \
  "--------------------------------------\n\n" \
  "To run fruitbox automatically on power up, add the following lines to /etc/rc.local :\n\n" \
  "  cd <directory where fruitbox is installed>\n" \
  "  ./fruitbox --skin <your cfg file>\n\n\n" \

  "Automatically mount USB memory stick on power up\n" \
  "------------------------------------------------\n\n" \
  "If your music is stored on a USB memory stick, you can automatically mount the USB memory " \
  "stick at boot time by typing the following commands:\n\n" \
  "  sudo mkdir -p /mnt/usb\n" \
  "  sudo nano /etc/fstab\n\n" \
  "When inside the nano editor, add the following line at the end of the table...\n\n" \
  "/dev/sda1     /mnt/usb       vfat    defaults,nofail    0       0\n\n" \
  "Save (Ctrl-O), then Quit nano (Ctrl-X).  Then in your fruitbox ini file, set the 'MusicPath' parameter to '/mnt/usb/'\n\n\n" \

  "Quick fruitbox style change using USB memory sticks\n" \
  "---------------------------------------------------\n\n" \
  "As a general tip, you can store the configuration file on a USB memory " \
  "stick along with the music, and run fruitbox using the command './fruitbox --skin /mnt/usb/fruitbox.cfg'.  " \
  "That way, you could have a complete jukebox look and feel with specific music all self-contained on " \
  "the USB stick, so then all you need to do to change jukebox styles and music collections is to swap USB sticks..." \
  "\n\nLet's Rock!"
};

void UserGuide(void);
