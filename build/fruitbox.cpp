#include "fruitbox.hpp"

using namespace std;

// uint32_t bitmaps_created { 0 };
uint32_t PiVersion { 0 };
uint32_t display_width { 0 };
uint32_t display_height { 0 };
ofstream log_file {};
int display_refresh_rate {};
bool Engine_finished { false };
bool InputThread_finished { false };
bool TimerThread_finished { false };
bool GetCURLDataThread_finished { false };
bool PlaySongThread_finished { false };
bool LoadArtworkThread_finished { false };
bool debug_song_nums { false };
bool no_db_refresh { false };
bool force_db_refresh { false };
bool no_splash { false };
bool dump_title_strips { false };
bool command_line_music_path { false };
bool ini_file_music_path { false };
sound_t camera_shutter_click {};
ConfigClass *Config {};
PlayQueueClass *PlayQueue {};
AudioClass *Audio {};
InputClass *Input {};
GpioClass *Gpio {};
DatabaseClass *Database {};
EngineClass *Engine {};
DisplayClass *Display {};
DialogSkinChooserClass *SkinChooser {};
DialogProgressBarClass *ProgressBar {};

status_t status { };
string save_playlist_filename {};
string load_playlist_filename {};

void ShutDown(void)
{
  PlayQueue->Save(save_playlist_filename); // save playqueue before stopping song otherwise it will be excluded from the playlist
  PlayQueue->Clear();
  Audio->StopSong(false);

  while (1)
  {
    this_thread::sleep_for(chrono::milliseconds(100));

    if ((InputThread_finished == true) &&
        (TimerThread_finished == true) &&
        (GetCURLDataThread_finished == true) &&
        (PlaySongThread_finished == true) &&
        (LoadArtworkThread_finished == true))
    {
      break; // all threads have finished
    }
  }
  
  cout << endl << FRUITBOX_DONATE_LINE1 << endl << FRUITBOX_DONATE_LINE2 << endl;
  log_file << endl << FRUITBOX_DONATE_LINE1 << endl << FRUITBOX_DONATE_LINE2 << endl;

  log_file.close(); 

  if (Engine->power_off)
  {
    int s = system("sudo shutdown now");
    while (1);
  }
}

// void CleanUp(void)
// {
  // al_uninstall_keyboard();
  // if (Audio) delete (Audio);
  // if (Engine) delete (Engine);
  // if (Database) delete (Database);
  // if (PlayQueue) delete (PlayQueue);
  // if (Display) delete (Display);
// }

void error(vector<string> message)
{
  log_file << ERROR << message.at(0) << endl;
  cout << ERROR << message.at(0) << endl;

  for (int m = 1; m < message.size(); ++m)
  {
    log_file << HINT << message.at(m) << endl;
    cout << HINT << message.at(m) << endl;
  }
  
  if (Display)
  {
    if (Display->active)
    {
      DialogMessageClass *MessageDialog = new DialogMessageClass("ERROR");
      MessageDialog->show_on_draw = true;
      
      if (InputClass::running)
      {
        DialogBaseClass::ActivateTouchControls();
        MessageDialog->Draw(message);
        Input->raw_mode = true;
        Input->WaitForButtonPress();
      }
      else
      {
        MessageDialog->Draw(message);
        this_thread::sleep_for(chrono::milliseconds(5000));
      }
      delete MessageDialog;
    }
  }
  exit(-1);
}

void error(const char *fmt, ...)
{
  char s[512];
  va_list args;
  va_start(args, fmt);
  vsprintf(s, fmt, args);
  va_end(args);
  vector<string> message {};
  message.push_back(string(s));
  error(message);
}
  
void Help(void)
{
  uint32_t version = al_get_allegro_version();
  int major = version >> 24;
  int minor = (version >> 16) & 255;
  int revision = (version >> 8) & 255;
  int release = version & 255;
  cout << endl << FRUITBOX_DESCRIPTION << endl;
  cout << FRUITBOX_SUMMARY << endl;
  cout << FRUITBOX_NON_COMMERCIAL << endl;
  cout << endl << "Command line arguments..." << endl << endl;
  cout << commandLineArgVersion         << commandLineOptVersion         << ": version number" << endl;
  cout << commandLineArgSkin            << commandLineOptSkin            << ": select (skin) configuration file" << endl;
  cout << commandLineArgMusicPath       << commandLineOptMusicPath       << ": select music path (overrides skin cfg MusicPath)" << endl;
  cout << commandLineArgUserGuide       << commandLineOptUserGuide       << ": creates the user guide (\"userguide.txt\" file)" << endl;
  cout << commandLineArgSavePlaylist    << commandLineOptSavePlaylist    << ": on exit, save the current playlist to <filename>" << endl;
  cout << commandLineArgLoadPlaylist    << commandLineOptLoadPlaylist    << ": load the playlist from <filename>" << endl;
  cout << commandLineArgDebugSongNums   << commandLineOptDebugSongNums   << ": show song/albums numbers next to songs to help identify them" << endl;
  cout << commandLineArgNoDbRefresh     << commandLineOptNoDbRefresh     << ": Disable update of database if out of date" << endl;
  cout << commandLineArgForceDbRefresh  << commandLineOptForceDbRefresh  << ": Force update of database" << endl;
  cout << commandLineArgNoScale         << commandLineOptNoScale         << ": Don't scale the skin to fit the display" << endl;
  cout << commandLineArgRotate          << commandLineOptRotate          << ": Rotate the display by <angle> degrees clockwise" << endl;
  cout << commandLineArgIniFile         << commandLineOptIniFile         << ": Initialisation file (default fruitbox.ini)" << endl;
  cout << commandLineArgDumpTitleStrips << commandLineOptDumpTitleStrips << ": Dump title strips to output image file(s)" << endl;
  cout << commandLineArgDisplaySize     << commandLineOptDisplaySize     << ": Display size in pixels" << endl;
  cout << endl << endl << "Acknowledgments..." << endl << endl;
  cout << "Allegro v" << major << "." << minor << "." << revision << "[" << release << "] Game Programming library for Graphics and Sound." << endl;
  cout << "libmpg123 v1.29.3 for MP3 decoding." << endl;
  cout << "DWJukebox for inspiration!" << endl << endl;
  cout << FRUITBOX_DONATE_LINE1 << endl << FRUITBOX_DONATE_LINE2 << endl;
}

void GetPiVersion(void)
{
  ifstream version_file {};
  string line {};
  size_t pos {};

  version_file.open("/sys/firmware/devicetree/base/model", ios::in);
  if (!version_file.is_open()) return;

  while (getline(version_file, line))
  {

    if ((pos = line.find("Raspberry Pi")) != string::npos)
    {
      pos += 12; // skip over "Raspberry Pi"
      if (pos < line.size())
      {
        PiVersion = static_cast<uint32_t>(strtol(&line.at(pos), nullptr, 10));
      }
    }
  }

  log_file << "Raspberry Pi Hardware version " << PiVersion << " detected" << endl;

  version_file.close();
}

int32_t main(int32_t argc, char *argv[])
{
  bool quit { false };
  struct timeval t1;
  string skin_file { };
  
  log_file.open("fruitbox.log");
  
  log_file << endl << FRUITBOX_DESCRIPTION << endl;
  log_file << FRUITBOX_SUMMARY << endl;
  log_file << FRUITBOX_NON_COMMERCIAL << endl;

  GetPiVersion();

  Config = new ConfigClass();

  // parse the command line options...
  if (argc > 1)
  {
    int32_t ac = argc - 1;
    char **av = &argv[1];
    #define NEXT_ARG if (ac) {*av++;ac--;}
    #define PREV_ARG {ac++;*av--;}
    while (ac--)
    {
      if (strcmp(*av, "--help") == 0)
      {
        Help();
        exit(-1);
      }

      if (strcmp(*av, commandLineArgUserGuide) == 0)
      {
        UserGuide();
        exit(-1);
      }

      if (strcmp(*av, commandLineArgVersion) == 0)
      {
        cout << FRUITBOX_VERSION_NUMBER << endl;
        exit(-1);
      }

      if (strcmp(*av, commandLineArgSkin) == 0)
      {
        NEXT_ARG; skin_file = *av;
      }

      if (strcmp(*av, commandLineArgCfg) == 0) // hidden for backwards compatibility
      {
        NEXT_ARG; skin_file = *av;
      }

      if (strcmp(*av, commandLineArgSavePlaylist) == 0)
      {
        NEXT_ARG;
        save_playlist_filename = *av;
      }

      if (strcmp(*av, commandLineArgNoSplash) == 0)
      {
        no_splash = true;
      }

      if (strcmp(*av, commandLineArgMusicPath) == 0)
      {
        command_line_music_path = true;
        NEXT_ARG;
        Config->skin_general->music_path.push_back(*av);
        log_file << NOTE << "MusicPath '" << *av << "' will override MusicPath in ini file and/or skin config file" << endl;
      }

      if (strcmp(*av, commandLineArgLoadPlaylist) == 0)
      {
        NEXT_ARG;
        load_playlist_filename = *av;
      }

      if (strcmp(*av, commandLineArgDebugSongNums) == 0)
      {
        debug_song_nums = true;
      }

      if (strcmp(*av, commandLineArgNoDbRefresh) == 0)
      {
        no_db_refresh = true;
      }

      if (strcmp(*av, commandLineArgForceDbRefresh) == 0)
      {
        force_db_refresh = true;
      }

      if (strcmp(*av, commandLineArgNoScale) == 0)
      {
        Config->no_scale = true;
      }

      if (strcmp(*av, commandLineArgRotate) == 0)
      {
        NEXT_ARG;
        Config->rotate = static_cast<float>(atoi(*av)) * ALLEGRO_PI / 180.0;
      }

      if (strcmp(*av, commandLineArgIniFile) == 0)
      {
        NEXT_ARG;
        Config->ini_filename = string(*av);
      }

      if (strcmp(*av, commandLineArgDumpTitleStrips) == 0)
      {
        dump_title_strips = true;
      }

      if (strcmp(*av, commandLineArgDisplaySize) == 0)
      {
        NEXT_ARG; display_width = atoi(*av);
        NEXT_ARG; display_height = atoi(*av);
      }

      *av++;
    }
  }

  cout << endl << FRUITBOX_DESCRIPTION << endl;
  cout << FRUITBOX_SUMMARY << endl;
  cout << FRUITBOX_NON_COMMERCIAL << endl;
  
  /////////////////////////////////////////////////////////////////////////////
  // Initialise Allegro...

  if (!al_init()) error("Failed to initialize Allegro");
  al_init_font_addon();
  al_init_primitives_addon();
  al_init_ttf_addon();
  al_init_image_addon();

  if (!al_install_audio()) error("Couldn't install audio");
  if (!al_init_acodec_addon()) error("Couldn't init acodec addon");
  if (!al_init_video_addon()) error("Couldn't init video addon");

  gettimeofday(&t1, nullptr); // generate time-based seed for random song play...
  // srand(t1.tv_usec * t1.tv_sec);
  fast_random::init(static_cast<uint32_t>(t1.tv_sec));

  /////////////////////////////////////////////////////////////////////////////
  // Create input instance...

  Input = new InputClass();

  /////////////////////////////////////////////////////////////////////////////
  // Create display...

  Display = new DisplayClass(display_width, display_height);

  /////////////////////////////////////////////////////////////////////////////
  // Create the GPIO object...

  Gpio = new GpioClass();

  /////////////////////////////////////////////////////////////////////////////
  // Load fruitbox ini configuration...

  Config->LoadIni();

  /////////////////////////////////////////////////////////////////////////////
  // Create progess bar...

  ProgressBar = new DialogProgressBarClass();
  ProgressBar->show_on_draw = true;

  /////////////////////////////////////////////////////////////////////////////
  // Display the splash screen (spinning fruitbox logo)...
  
  if (no_splash == false)
  {
    DialogSplashScreenClass *SplashScreen = new DialogSplashScreenClass();
    SplashScreen->show_on_draw = true;
    while (SplashScreen->Run() == false) {}; // repeat until splash screen done
    delete SplashScreen;
  }

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the song play queue...

  PlayQueue = new PlayQueueClass();

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the input and start separate thread for it...

  ProgressBar->Draw("Initialising Inputs", 10);
  Input->Start();

  /////////////////////////////////////////////////////////////////////////////
  // Create on-screen menus...

  menus::CreateMainMenu();
  
  /////////////////////////////////////////////////////////////////////////////
  // Run touch screen calibration if we have a touch screen but it's not been calibrated
  // yet (i.e. there are no calibration values in the ini file)...

  if (Input->touch_active && !Config->touch_screen->calibrated)
  {
    while (menus::RunCalibrateTouch(1) == false) {}; // repeat until calibration done
    Config->SaveIni();
  }
  
  Config->ConfigureDisplayTouch();
  
  /////////////////////////////////////////////////////////////////////////////
  // Skin chooser menu...

  if (skin_file.size() == 0) // no '--skin' or '--cfg' command line argument specified, so enable skin chooser...
  {
    SkinChooser = new DialogSkinChooserClass();
    // SkinChooser->show_on_draw = true;

    skin_file = SkinChooser->Run();
    delete SkinChooser;
  }

  /////////////////////////////////////////////////////////////////////////////
  // Load skin configuration...

  ProgressBar->Draw("Loading Skin", 20);
  if (Config->LoadSkin(skin_file) == false) exit(-1);
  Config->ConfigureSkinTouch();
  menus::CreateAboutMenu(); // can now access skin name etc.

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the audio...

  ProgressBar->Draw("Initialising Audio", 30);
  Audio = new AudioClass();

  /////////////////////////////////////////////////////////////////////////////
  // Initialise the jukebox engine...

  ProgressBar->Draw("Initialising engine", 40);
  Engine = new EngineClass();

  /////////////////////////////////////////////////////////////////////////////
  // Load / Create / Refresh the database...

  Database = new DatabaseClass();
  menus::CreateSearchMenu(); // can now reference Database parameters in menu

  /////////////////////////////////////////////////////////////////////////////
  // load playqueue...

  ProgressBar->Draw("Loading Playlist", 80);
  PlayQueue->Load(load_playlist_filename);

  /////////////////////////////////////////////////////////////////////////////
  // Pre-run checks...

  ProgressBar->Draw("Checking Skin", 90);

  Config->PostProcess();

  /////////////////////////////////////////////////////////////////////////////
  // delete the dialog backdrop bitmap (if created by the skin chooser)
  if (DialogBaseClass::backdrop_bm)
  {
    al_destroy_bitmap(DialogBaseClass::backdrop_bm);
    DialogBaseClass::backdrop_bm = nullptr;
  }

  /////////////////////////////////////////////////////////////////////////////
  // Dump Title Strip bitmaps to external files...
  
  if (dump_title_strips)
  {
    Database->DumpTitleStrips();
    exit(-1);
  }
  
  /////////////////////////////////////////////////////////////////////////////
  // Main loop...

  Engine->Run();

  /////////////////////////////////////////////////////////////////////////////
  // Tidy up...

  ShutDown();

  // while (1)
  // {
    
    // this_thread::sleep_for(chrono::milliseconds(100));
    
    // if ((InputThread_finished == true) &&
        // (TimerThread_finished == true) &&
        // (GetCURLDataThread_finished == true) &&
        // (PlaySongThread_finished == true) &&
        // (LoadArtworkThread_finished == true))
        // {
          // break; // all threads have finished
        // }
  // }
  
  // cout << endl << FRUITBOX_DONATE_LINE1 << endl << FRUITBOX_DONATE_LINE2 << endl;
  // log_file << endl << FRUITBOX_DONATE_LINE1 << endl << FRUITBOX_DONATE_LINE2 << endl;

  // log_file.close(); 

  return 0;

}

