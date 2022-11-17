#include "fruitbox.hpp"

dialog_list_item_label_t BlankListItem             {"", nullptr, nullptr, 0, nullptr};

constexpr char MainMenu_Name[]                     { "Main Menu" };
constexpr char SettingsMenu_Name[]                 { "Settings" };
constexpr char ControlsMenu_Name[]                 { "Controls" };
constexpr char SearchMenu_Name[]                   { "Search" };
constexpr char ControlsChangedMessage_Name[]       { "Controls have been changed" };
constexpr char ControlsChangedMessage_Body[]       { "Changes will take effect the next time fruitbox is started" };
constexpr char ConfigureButtonsMenu_Name[]         { "Configure Buttons" };
constexpr char ResetButtons_Name[]                 { "Reset Button Mappings" };
constexpr char ResetSearch_Name[]                  { "Reset Search Fields" };
constexpr char CalibrateTouch_Name[]               { "Calibrate Touchscreen" };
constexpr char AboutMenu_Name[]                    { "About" };
constexpr char UpdateMenu_Name[]                   { "Software Update" };
constexpr char PowerOffMenu_Name[]                 { "Power Off" };

constexpr char ConfirmResetButtons_Name[]          { "Reset all button mappings to defaults?" };
constexpr char ConfirmResetSearch_Name[]           { "Reset all search fields?" };
constexpr char ConfirmPowerOff_Name[]              { "Power Off?" };
                                                 
constexpr char ControlsMenu_Mouse[]                { "Mouse" };
constexpr char ControlsMenu_JoystickMode[]         { "Joystick Mode" };
constexpr char ControlsMenu_TouchScreen[]          { "TouchScreen" };

constexpr char SettingsMenu_FreePlay[]             { "Free Play" };
constexpr char SettingsMenu_LoopPlayQueue[]        { "Loop Play Queue" };
constexpr char SettingsMenu_CreditsPerCoin1[]      { "Credits Per Coin Slot 1" };
constexpr char SettingsMenu_CreditsPerCoin2[]      { "Credits Per Coin Slot 2" };
constexpr char SettingsMenu_CreditsPerCoin3[]      { "Credits Per Coin Slot 3" };
constexpr char SettingsMenu_CreditsPerCoin4[]      { "Credits Per Coin Slot 4" };
constexpr char SettingsMenu_CreditsPerCoin5[]      { "Credits Per Coin Slot 5" };
constexpr char SettingsMenu_CreditsPerCoin6[]      { "Credits Per Coin Slot 6" };
constexpr char SettingsMenu_CreditsPerSong[]       { "Credits Per Song" };
constexpr char SettingsMenu_AttractMode[]          { "Attract Mode" };
constexpr char SettingsMenu_AttractModeChoice[]    { "Attract Mode Choice" };
constexpr char SettingsMenu_SongVolume[]           { "Song Volume" };
constexpr char SettingsMenu_SongVolumeStep[]       { "Song Volume Step" };
constexpr char SettingsMenu_MaxPlayQueueLength[]   { "Play Queue Size" };

constexpr char SearchMenu_Title[]                  { "Song Title" };
constexpr char SearchMenu_Artist[]                 { "Song Artist" };
constexpr char SearchMenu_Album[]                  { "Album" };
constexpr char SearchMenu_AlbumArtist[]            { "Album Artist" };
constexpr char SearchMenu_Genre[]                  { "Genre" };
constexpr char SearchMenu_Year[]                   { "Year" };

DialogSelectableListClass *MainMenu {};
DialogSelectableListClass *SearchMenu {};

namespace menus
{
  DialogMessageClass *AboutMenu {};
  DialogMessageClass *ControlsChangedMessage {};
  DialogMessageClass *PowerOffMenu {};
  DialogMessageClass *ResetSearchMenu {};
  DialogMessageClass *ResetButtonsMenu {};
  DialogSoftwareUpdateClass *UpdateMenu {};
  DialogSelectableListClass *SettingsMenu {};
  DialogSelectableListClass *ControlsMenu {};
  DialogSelectableListClass *ConfigureButtonsMenu {};
  DialogCalibrateTouchClass *CalibrateTouch {};
  vector<string> about_info {};
  vector<string> update_info {};

  ///////////////////////////////////////////////////////////////////////////////

  void CreateAboutMenu(void)
  {
    if (AboutMenu == nullptr)
    {
      string skin { Config->skin_general->skin_name };
      if (Config->skin_general->skin_version.size())
      {
        skin += " (" + Config->skin_general->skin_version + ")";
      }

      AboutMenu = new DialogMessageClass(FRUITBOX_DESCRIPTION);
      about_info.push_back(FRUITBOX_SUMMARY);
      about_info.push_back(FRUITBOX_NON_COMMERCIAL);
      about_info.push_back("");
      about_info.push_back("Skin : " + skin);
      for (auto &sd : Config->skin_general->skin_desc)
      {
        about_info.push_back("            ... " + sd);
      }
      about_info.push_back("");
      about_info.push_back(FRUITBOX_DONATE_LINE1);
      about_info.push_back(FRUITBOX_DONATE_LINE2);
      about_info.push_back("");
      about_info.push_back("Please read 'userguide.txt' for help");
    }
  }

  bool RunAboutMenu(uint32_t param)
  {
    AboutMenu->Draw(about_info);
    return AboutMenu->Run();
  }

  ///////////////////////////////////////////////////////////////////////////////

  void CreateUpdateMenu(void)
  {
    if (UpdateMenu == nullptr)
    {
      UpdateMenu = new DialogSoftwareUpdateClass(UpdateMenu_Name);
    }
  }

  bool RunUpdateMenu(uint32_t param)
  {
    return UpdateMenu->Run();
  }

  ///////////////////////////////////////////////////////////////////////////////

  void CreatePowerOffMenu(void)
  {
    if (PowerOffMenu == nullptr)
    {
      PowerOffMenu = new DialogYesNoQuestionClass(ConfirmPowerOff_Name);
    }
  }

  bool RunPowerOffMenu(uint32_t param)
  {
    PowerOffMenu->Draw();

    if (PowerOffMenu->Run()) // answer given
    {
      if (PowerOffMenu->Buttons->choice == BUTTON_Y) // yes
      {
        Engine->Quit(true);
      }
      return true;
    }

    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////

  void CreateResetButtonsMenu(void)
  {
    if (ResetButtonsMenu == nullptr)
    {
      ResetButtonsMenu = new DialogYesNoQuestionClass(ConfirmResetButtons_Name);
    }
  }

  bool RunResetButtons(uint32_t param)
  {
    ResetButtonsMenu->Draw();

    if (ResetButtonsMenu->Run()) // answer given
    {
      if (ResetButtonsMenu->Buttons->choice == BUTTON_Y) // yes
      {
        Config->buttons->ResetToDefaults();
        // if we have a touch screen or mouse and any touch areas are defined, then force those buttons to be of touch input type...
        if (Input->touch_active || Input->mouse_active)
        {
          Config->buttons->RegisterTouchAreas();
        }
        ControlsMenu->changed = true; // force a SaveIni() when we exit from the parent (Controls) menu

        return true;
      }
      return true;
    }

    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////

  void CreateCalibrateTouch(void)
  {
    if (CalibrateTouch == nullptr)
    {
      CalibrateTouch = new DialogCalibrateTouchClass(CalibrateTouch_Name);
    }
  }

  bool RunCalibrateTouch(uint32_t param)
  {
    // CalibrateTouch->show_on_draw = param ? true : false;

    if (CalibrateTouch->Run()) // ready to exit from the calibrate touch menu
    {
      ControlsMenu->changed = param ? false : true; // force a SaveIni() when we exit from the parent (Controls) menu (param = 0)
      return true;
    }
    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////

  void ConfigureButtonsMenu_Init(void)
  {
    Input->raw_mode = true;
  }
  
  void ConfigureButtonsMenu_Exit(void)
  {
    Input->raw_mode = false;
  }
  
  bool ConfigureButtonsMenu_ConfigButton(uint32_t param)
  {
    return ConfigureButtonsMenu->ConfigButton(param);
  }

  void CreateConfigureButtonsMenu(void)
  {
    if (ConfigureButtonsMenu == nullptr)
    {
      ConfigureButtonsMenu = new DialogSelectableListClass(ConfigureButtonsMenu_Name);

      for (uint32_t b = 0; b < Config->buttons->button.size(); ++b)
      {
        ConfigureButtonsMenu->AddListItem({string(Config->buttons->button[b].name), ConfigureButtonsMenu_Init, ConfigureButtonsMenu_ConfigButton, b, ConfigureButtonsMenu_Exit}, {value_type_e::Button, nullptr, 0, 0 });
      }
    }
  }

  bool RunConfigureButtonsMenu(uint32_t param)
  {
    static bool setup_gpio { true };
    if (setup_gpio)
    {
      for (uint32_t pin = 0; pin < NUM_GPIO; ++pin) // setup all GPIO pins as inputs...
      {
        if (Gpio->direction[pin] != gpio_e::Reserved) Gpio->ConfigurePinAsInput(pin);
      }
      setup_gpio = false;
    }
    
    ConfigureButtonsMenu->Draw();

    if (ConfigureButtonsMenu->Run() == true) // finished
    {

      for (uint32_t pin = 0; pin < NUM_GPIO; ++pin) // restore any gpio outputs to actual outputs
      {
        if (Gpio->direction[pin] == gpio_e::Output)
        {
          Gpio->ConfigurePinAsOutput(pin);
        }
      }
      if (ConfigureButtonsMenu->changed)
      {
        ConfigureButtonsMenu->changed = false;
        ControlsMenu->changed = true;
      }

      setup_gpio = true; // for next time
      return true;
    }

    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////

  enum class controls_menu_state_t
  {
    run_controls,
    run_message
  };

  bool ControlsMenu_EditBool(uint32_t param)
  {
    bool ret = ControlsMenu->Edit<bool>();
    Engine->status_event |= param;
    return ret;
  }

  void CreateControlsMenu(void)
  {
    if (ControlsMenu == nullptr)
    {
      ControlsMenu = new DialogSelectableListClass(ControlsMenu_Name);
      
      /* 0 */ ControlsMenu->AddListItem({string(ConfigureButtonsMenu_Name) , nullptr, RunConfigureButtonsMenu, 0, nullptr});
      /* 1 */ ControlsMenu->AddListItem({string(ControlsMenu_TouchScreen)  , nullptr, ControlsMenu_EditBool, StatusEvent_None, nullptr}, {value_type_e::Bool, reinterpret_cast<void*>(&Config->touch_screen->enabled), 0, 0});
      /* 2 */ ControlsMenu->AddListItem({string(ControlsMenu_Mouse)        , nullptr, ControlsMenu_EditBool, StatusEvent_None, nullptr}, {value_type_e::Bool, reinterpret_cast<void*>(&Config->mouse->enabled)      , 0, 0});
      /* 3 */ ControlsMenu->AddListItem({string(ControlsMenu_JoystickMode) , nullptr, ControlsMenu_EditBool, StatusEvent_None, nullptr}, {value_type_e::Bool, reinterpret_cast<void*>(&Config->joystick->enabled)   , 0, 0});
      /* 4 */ ControlsMenu->AddListItem({string(CalibrateTouch_Name)       , nullptr, RunCalibrateTouch, 0, nullptr});
      /* 5 */ ControlsMenu->AddListItem({string(ResetButtons_Name)         , nullptr, RunResetButtons, 0, nullptr});
      ControlsMenu->EnableListItem(1, Input->touch_installed); // enable or disable touchscreen depending on if touchscreen is installed 
      ControlsMenu->EnableListItem(2, Input->mouse_installed); // enable or disable mouse depending on if mouse is installed 
      ControlsMenu->EnableListItem(4, Input->touch_installed); // enable or disable calibrate touch depending on if touchscreen is installed 

      if (Input->touch_installed)
      {
        CreateCalibrateTouch();
      }

      ControlsChangedMessage = new DialogMessageClass(ControlsChangedMessage_Name);
    }
  }

  bool RunControlsMenu(uint32_t param)
  {
    static controls_menu_state_t state { controls_menu_state_t::run_controls };
    
    switch (state)
    {
      case controls_menu_state_t::run_controls :
        ControlsMenu->Draw();
        if (ControlsMenu->Run() == true) // true means finished
        {
          if (ControlsMenu->changed)
          {
            ControlsMenu->changed = false;
            Config->SaveIni();
            state = controls_menu_state_t::run_message;
          }
          else return true; // finished
        }
        break;

      case controls_menu_state_t::run_message :
        ControlsChangedMessage->Draw(string(ControlsChangedMessage_Body));
        if (ControlsChangedMessage->Run())
        {
          state = controls_menu_state_t::run_controls;
          return true; // finished
        }
        break;
    }

    return false;
  }
  
  ///////////////////////////////////////////////////////////////////////////////

  bool SettingsMenu_EditVolume(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<uint32_t>();
    uint32_t *v { reinterpret_cast<uint32_t*>(SettingsMenu->list.at(SettingsMenu->selected_item).param.value) };
    Audio->SetVolume(*v, true);
    return ret;
  }
  
  bool SettingsMenu_EditCreditsPerCoin(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<uint32_t>();
    uint32_t *v { reinterpret_cast<uint32_t*>(SettingsMenu->list.at(SettingsMenu->selected_item).param.value) };
    uint32_t p { reinterpret_cast<uint32_t>(SettingsMenu->list.at(SettingsMenu->selected_item).label.run_func_param) };
    Config->ini_general->credits_per_coin_str.at(p) = to_string(*v);
    return ret;
  }

  bool SettingsMenu_EditCreditsPerSong(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<uint32_t>();
    uint32_t *v { reinterpret_cast<uint32_t*>(SettingsMenu->list.at(SettingsMenu->selected_item).param.value) };
    uint32_t p { reinterpret_cast<uint32_t>(SettingsMenu->list.at(SettingsMenu->selected_item).label.run_func_param) };
    Config->ini_general->credits_per_coin_str.at(p) = to_string(*v);
    return ret;
  }

  bool SettingsMenu_EditAttractModeChoice(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<uint32_t>();
    return ret;
  }

  bool SettingsMenu_EditAttractMode(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<bool>();
    bool *v { reinterpret_cast<bool*>(SettingsMenu->list.at(SettingsMenu->selected_item).param.value) };
    if (*v == false) // attract mode turned off
    {
      Engine->attract_timer = 0;
    }
    else
    {
      if (!PlayQueue->NumSongsTotal())
      {
        Engine->attract_timer = 1 + Config->ini_attract->interval.ticks; // if queue empty, start attract timer if attract mode enabled (add 1 because 0 is disabled)
      }
    }
    SettingsMenu->EnableListItem(1, *v); // enable or disable choice menu entry accordingly
    Engine->status_event |= param;
    return ret;
  }

  bool SettingsMenu_EditBool(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<bool>();
    Engine->status_event |= param;
    return ret;
  }

  void SetCreditsPerCoinsMenuEntries(void)
  // enable/disable CreditsPerCoin menu entries depending on value of freeplay parameter...
  {
    bool en = !Config->ini_general->free_play;

    SettingsMenu->EnableListItem( 7, en); // CreditsPerCoin0
    SettingsMenu->EnableListItem( 8, en); // CreditsPerCoin1
    SettingsMenu->EnableListItem( 9, en); // CreditsPerCoin2
    SettingsMenu->EnableListItem(10, en); // CreditsPerCoin3
    SettingsMenu->EnableListItem(11, en); // CreditsPerCoin4
    SettingsMenu->EnableListItem(12, en); // CreditsPerCoin5
    SettingsMenu->EnableListItem(13, en); // CreditsPerSong

  }

  bool SettingsMenu_EditFreePlay(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<bool>();

    SetCreditsPerCoinsMenuEntries();
    Engine->status_event |= param;
    return ret;
  }

  bool SettingsMenu_EditUint32(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<uint32_t>();
    Engine->status_event |= param;
    return ret;
  }

  bool SettingsMenu_EditFloat(uint32_t param)
  {
    bool ret = SettingsMenu->Edit<float>();
    Engine->status_event |= param;
    return ret;
  }

  void CreateSettingsMenu(void)
  {
    if (SettingsMenu == nullptr) // destroy previous dialog
    {
      SettingsMenu = new DialogSelectableListClass(SettingsMenu_Name);

      /*  0 */ SettingsMenu->AddListItem({string(SettingsMenu_AttractMode       ) , nullptr, SettingsMenu_EditAttractMode,        StatusEvent_AttractModeModeChange, nullptr}, {value_type_e::Bool,          reinterpret_cast<void*>(&Config->ini_attract->enable)             , 0,                        0                        });
      /*  1 */ SettingsMenu->AddListItem({string(SettingsMenu_AttractModeChoice ) , nullptr, SettingsMenu_EditAttractModeChoice,  StatusEvent_AttractModeModeChange, nullptr}, {value_type_e::AttractChoice, reinterpret_cast<void*>(&Config->ini_attract->choice)             , static_cast<uint32_t>(attract_choice_e::Random), static_cast<uint32_t>(attract_choice_e::Sorted) });
      /*  2 */ SettingsMenu->AddListItem({string(SettingsMenu_MaxPlayQueueLength) , nullptr, SettingsMenu_EditUint32,             StatusEvent_PlayQueueChange      , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->max_playqueue_length), MinPlayQueueLength,       MaxPlayQueueLength       });
      /*  3 */ SettingsMenu->AddListItem({string(SettingsMenu_LoopPlayQueue     ) , nullptr, SettingsMenu_EditBool,               StatusEvent_LoopModeChange       , nullptr}, {value_type_e::Bool,          reinterpret_cast<void*>(&Config->ini_general->loop_playqueue)      , 0,                        0                        });
      /*  4 */ SettingsMenu->AddListItem({string(SettingsMenu_SongVolume        ) , nullptr, SettingsMenu_EditVolume,             StatusEvent_None                 , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->song_volume)        , MinSongVolume,            MaxSongVolume            });
      /*  5 */ SettingsMenu->AddListItem({string(SettingsMenu_SongVolumeStep    ) , nullptr, SettingsMenu_EditUint32,             StatusEvent_None                 , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->song_volume_step)   , MinSongVolumeStep,        MaxSongVolumeStep        });
      /*  6 */ SettingsMenu->AddListItem({string(SettingsMenu_FreePlay          ) , nullptr, SettingsMenu_EditFreePlay,           StatusEvent_FreeplayModeChange   , nullptr}, {value_type_e::Bool,          reinterpret_cast<void*>(&Config->ini_general->free_play)          , 0,                        0                        });
      /*  7 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin1   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     0                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[0]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /*  8 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin2   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     1                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[1]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /*  9 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin3   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     2                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[2]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /* 10 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin4   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     3                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[3]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /* 11 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin5   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     4                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[4]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /* 12 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerCoin6   ) , nullptr, SettingsMenu_EditCreditsPerCoin,     5                                , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_coin[5]), MinCreditsPerCoin,        MaxCreditsPerCoin        });
      /* 13 */ SettingsMenu->AddListItem({string(SettingsMenu_CreditsPerSong    ) , nullptr, SettingsMenu_EditCreditsPerSong,     StatusEvent_None                 , nullptr}, {value_type_e::Uint32,        reinterpret_cast<void*>(&Config->ini_general->credits_per_song)   , MinCreditsPerSong,        MaxCreditsPerSong        });
      SetCreditsPerCoinsMenuEntries();
      SettingsMenu->EnableListItem(1, Config->ini_attract->enable); // enable or disable choice menu entry accordingly
      SettingsMenu->EnableListItem(3, !Config->skin_general->no_duplicates); // enable or disable loop menu depending on skin NoDuplicates 
    }
  }

  bool RunSettingsMenu(uint32_t param)
  {
    SettingsMenu->Draw();
    if (SettingsMenu->Run())
    {
      Config->SaveIni();
      return true;
    }
    return false;
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Song Search Menu...

  bool RunResetSearchMenu(uint32_t param)
  {
    ResetSearchMenu->Draw();

    if (ResetSearchMenu->Run()) // answer given
    {
      if (ResetSearchMenu->Buttons->choice == BUTTON_Y) // yes, so clear the database search fields
      {
        Database->search_filter_Title.clear();
        Database->search_filter_Artist.clear();
        Database->search_filter_Album.clear();
        Database->search_filter_AlbumArtist.clear();
        Database->search_filter_Genre.clear();
        Database->search_filter_Year.clear();
        SearchMenu->changed = true;
      }
      return true;
    }
    
    return false;
  }

  void Search_EditStringInit(void)
  {
    SearchMenu->EnableVirtualKeyboard();
  }
  
  void Search_EditStringExit(void)
  {
    SearchMenu->DisableVirtualKeyboard();
  }
  
  bool Search_EditString(uint32_t param)
  {
    return SearchMenu->EditString();

    // SettingsMenu->Draw();
    // if (SettingsMenu->Run())
    // {
      // Config->SaveIni();
      // return true;
    // }
    // return false;
  }
  
  void CreateSearchMenu(void)
  {
    if (SearchMenu == nullptr)
    {
      ResetSearchMenu = new DialogYesNoQuestionClass(ConfirmResetSearch_Name);
      
      SearchMenu = new DialogSelectableListClass(SearchMenu_Name);

      SearchMenu->AddListItem({string(SearchMenu_Title      ), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_Title), 0, 32});
      SearchMenu->AddListItem({string(SearchMenu_Artist     ), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_Artist), 0, 32});
      SearchMenu->AddListItem({string(SearchMenu_Album      ), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_Album), 0, 32});
      SearchMenu->AddListItem({string(SearchMenu_AlbumArtist), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_AlbumArtist), 0, 32});
      SearchMenu->AddListItem({string(SearchMenu_Genre      ), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_Genre), 0, 32});
      SearchMenu->AddListItem({string(SearchMenu_Year       ), Search_EditStringInit, Search_EditString, StatusEvent_None, Search_EditStringExit}, {value_type_e::String,   reinterpret_cast<void*>(&Database->search_filter_Year), 0, 32});
      // SearchMenu->AddListItem(BlankListItem); // blank line
      SearchMenu->AddListItem({string(ResetSearch_Name), nullptr, RunResetSearchMenu, 0, nullptr});
    }
  }

  ///////////////////////////////////////////////////////////////////////////////

  void CreateMainMenu(void)
  {
    CreateUpdateMenu();
    CreateSettingsMenu();
    CreateConfigureButtonsMenu();
    CreateControlsMenu();
    CreatePowerOffMenu();
    CreateResetButtonsMenu();

    // CreateSearchMenu called after Database object is created
    // CreateAboutMenu called after skin is loaded

    MainMenu = new DialogSelectableListClass(MainMenu_Name);
    MainMenu->AddListItem({string(SettingsMenu_Name), nullptr, RunSettingsMenu, 0, nullptr});
    MainMenu->AddListItem({string(ControlsMenu_Name), nullptr, RunControlsMenu, 0, nullptr});
    MainMenu->AddListItem({string(AboutMenu_Name), nullptr, RunAboutMenu, 0, nullptr});
    MainMenu->AddListItem({string(UpdateMenu_Name), nullptr, RunUpdateMenu, 0, nullptr});
    MainMenu->AddListItem({string(PowerOffMenu_Name), nullptr, RunPowerOffMenu, 0, nullptr});
  }
}
