#include "fruitbox.hpp"

using namespace std;

bool main_menu_active { false };
bool search_menu_active { false };

////////////////////////////////////////////////////////////////
// Button functions........


void ProcessButtonLeft(EngineClass *engine)
{
  engine->screen_jump = 1;
  if (Config->skin_general->select_mode == select_mode_e::JoyStick)
  {
    if (engine->joy_x > 0)
    {
      engine->joy_x--;
      engine->UpdateJoystickPositions(engine->joy_x, engine->joy_y);
    }
    else if (Config->joystick->disable_title_strip_flip == false)
    {
      engine->title_strip_turn_left = true;
    }
  }
  else
  {
    engine->title_strip_turn_left = true;
  }
}


void ProcessButtonRight(EngineClass *engine)
{
  engine->screen_jump = 1;
  if (Config->skin_general->select_mode == select_mode_e::JoyStick)
  {
    if (engine->joy_x < Config->skin_general->num_title_strips - 1)
    {
      engine->joy_x++;
      engine->UpdateJoystickPositions(engine->joy_x, engine->joy_y);
    }
    else if (Config->joystick->disable_title_strip_flip == false)
    {
      engine->title_strip_turn_right = true;
    }
  }
  else
  {
    engine->title_strip_turn_right = true;
  }
}

void ProcessButtonLeftScreen(EngineClass *engine)
{
  engine->screen_jump = Config->skin_general->screen_jump;
  engine->title_strip_turn_left = true;
}

void ProcessButtonRightScreen(EngineClass *engine)
{
  engine->screen_jump = Config->skin_general->screen_jump;
  engine->title_strip_turn_right = true;
}

void ProcessButtonLeftSort(EngineClass *engine)
{
  if (Database->jump_sort_title_strip.size() > 1)
  {
    uint32_t i;
    if (engine->start_title_strip == 0)
    {
      i = Database->jump_sort_title_strip.size() -1 ;
    }
    else
    {
      for (i = 1; i < Database->jump_sort_title_strip.size(); ++i)
      {
        if (Database->jump_sort_title_strip[i] >= engine->start_title_strip)
        {
          i--;
          break;
        }
      }
      if (i == Database->jump_sort_title_strip.size()) i = 0;
    }

    int32_t jump = abs(static_cast<int32_t>(Database->jump_sort_title_strip[i]) -  static_cast<int32_t>(engine->start_title_strip));
    engine->screen_jump = static_cast<uint32_t>(jump) / Config->skin_general->num_title_strips;
    engine->title_strip_turn_left = true;
  }
}

void ProcessButtonRightSort(EngineClass *engine)
{
  if (Database->jump_sort_title_strip.size() > 1)
  {
    uint32_t i;
    for (i = 0; i < Database->jump_sort_title_strip.size(); ++i)
    {
      if ((Database->jump_sort_title_strip[i] > engine->start_title_strip)) // && (Database->jump_sort_title_strip.at(i+1) < start_title_strip))
      {
        break;
      }
    }

    if (i == Database->jump_sort_title_strip.size()) i = 0;
    int32_t jump = abs(static_cast<int32_t>(engine->start_title_strip) - static_cast<int32_t>(Database->jump_sort_title_strip[i]));
    engine->screen_jump = static_cast<uint32_t>(jump) / Config->skin_general->num_title_strips;
    engine->title_strip_turn_right = true;
  }
}

void ProcessButtonUp(EngineClass *engine)
{
  if (Config->skin_general->select_mode == select_mode_e::JoyStick)
  {
    if (engine->joy_y > 0)
    {
      engine->joy_y--;
      engine->UpdateJoystickPositions(engine->joy_x, engine->joy_y);
    }
  }
}

void ProcessButtonDown(EngineClass *engine)
{
  if (Config->skin_general->select_mode == select_mode_e::JoyStick)
  {
    if (Config->skin_general->album_mode == false) // y_pos stays at zero in albums mode
    {
      if (engine->joy_y < Config->skin_general->songs_per_title_strip - 1)
      {
        engine->joy_y++;
        engine->UpdateJoystickPositions(engine->joy_x, engine->joy_y);
      }
    }
  }
}

void ProcessButtonSelect(EngineClass *engine)
{
  if (Config->skin_general->auto_select && (Config->skin_general->select_mode == select_mode_e::SelectCode)) return;
  engine->CheckAndAddSelection();
}

void ProcessButtonSkip(EngineClass *engine) { Audio->StopSong(true); }

void ProcessButtonPause(EngineClass *engine) { Audio->PauseSong(); }

void ProcessButtonScreenshot(EngineClass *engine)
{
  string screenshot_filename { Config->filename.substr(0, Config->filename.find_last_of("/")) + "/" + Config->skin_general->screenshot };
  
  Audio->PlaySound(camera_shutter_click);
  al_save_bitmap(screenshot_filename.c_str(), Display->jukebox);
  string message { "Screenshot saved to file '" + screenshot_filename + "'" };
  log_file << message << endl;

  ALLEGRO_BITMAP *current_backdrop_bm { DialogBaseClass::backdrop_bm }; // save current backdrop
  DialogBaseClass::backdrop_bm  = Display->jukebox;
  DialogMessageClass *MessageDialog = new DialogMessageClass("Screenshot Captured");
  MessageDialog->show_on_draw = true;
  MessageDialog->Draw(message);
  Input->raw_mode = true;
  Input->WaitForButtonPress(); // release of screenshot button press
  Input->WaitForButtonPress(); // wait for another key
  Input->raw_mode = false;
  DialogBaseClass::backdrop_bm = current_backdrop_bm; // restore current backdrop
};

void ProcessButtonClearQueue(EngineClass *engine) { PlayQueue->Clear(); }

void ProcessButtonSelect0(EngineClass *engine) { engine->UpdateSelectCode('0'); }
void ProcessButtonSelect1(EngineClass *engine) { engine->UpdateSelectCode('1'); }
void ProcessButtonSelect2(EngineClass *engine) { engine->UpdateSelectCode('2'); }
void ProcessButtonSelect3(EngineClass *engine) { engine->UpdateSelectCode('3'); }
void ProcessButtonSelect4(EngineClass *engine) { engine->UpdateSelectCode('4'); }
void ProcessButtonSelect5(EngineClass *engine) { engine->UpdateSelectCode('5'); }
void ProcessButtonSelect6(EngineClass *engine) { engine->UpdateSelectCode('6'); }
void ProcessButtonSelect7(EngineClass *engine) { engine->UpdateSelectCode('7'); }
void ProcessButtonSelect8(EngineClass *engine) { engine->UpdateSelectCode('8'); }
void ProcessButtonSelect9(EngineClass *engine) { engine->UpdateSelectCode('9'); }
void ProcessButtonSelectA(EngineClass *engine) { engine->UpdateSelectCode('A'); }
void ProcessButtonSelectB(EngineClass *engine) { engine->UpdateSelectCode('B'); }
void ProcessButtonSelectC(EngineClass *engine) { engine->UpdateSelectCode('C'); }
void ProcessButtonSelectD(EngineClass *engine) { engine->UpdateSelectCode('D'); }
void ProcessButtonSelectE(EngineClass *engine) { engine->UpdateSelectCode('E'); }
void ProcessButtonSelectF(EngineClass *engine) { engine->UpdateSelectCode('F'); }
void ProcessButtonSelectG(EngineClass *engine) { engine->UpdateSelectCode('G'); }
void ProcessButtonSelectH(EngineClass *engine) { engine->UpdateSelectCode('H'); }
void ProcessButtonSelectI(EngineClass *engine) { engine->UpdateSelectCode('I'); }
void ProcessButtonSelectJ(EngineClass *engine) { engine->UpdateSelectCode('J'); }
void ProcessButtonSelectK(EngineClass *engine) { engine->UpdateSelectCode('K'); }
void ProcessButtonSelectL(EngineClass *engine) { engine->UpdateSelectCode('L'); }
void ProcessButtonSelectM(EngineClass *engine) { engine->UpdateSelectCode('M'); }
void ProcessButtonSelectN(EngineClass *engine) { engine->UpdateSelectCode('N'); }
void ProcessButtonSelectO(EngineClass *engine) { engine->UpdateSelectCode('O'); }
void ProcessButtonSelectP(EngineClass *engine) { engine->UpdateSelectCode('P'); }
void ProcessButtonSelectQ(EngineClass *engine) { engine->UpdateSelectCode('Q'); }
void ProcessButtonSelectR(EngineClass *engine) { engine->UpdateSelectCode('R'); }
void ProcessButtonSelectS(EngineClass *engine) { engine->UpdateSelectCode('S'); }
void ProcessButtonSelectT(EngineClass *engine) { engine->UpdateSelectCode('T'); }
void ProcessButtonSelectU(EngineClass *engine) { engine->UpdateSelectCode('U'); }
void ProcessButtonSelectV(EngineClass *engine) { engine->UpdateSelectCode('V'); }
void ProcessButtonSelectW(EngineClass *engine) { engine->UpdateSelectCode('W'); }
void ProcessButtonSelectX(EngineClass *engine) { engine->UpdateSelectCode('X'); }
void ProcessButtonSelectY(EngineClass *engine) { engine->UpdateSelectCode('Y'); }
void ProcessButtonSelectZ(EngineClass *engine) { engine->UpdateSelectCode('Z'); }

void ProcessButtonInsertCoin(EngineClass *engine, uint32_t coin)
{
  if (!Config->ini_general->free_play)
  {
    status.credits += Config->ini_general->credits_per_coin[coin];
    engine->status_event |= StatusEvent_CreditsChange;
  }
}

void ProcessButtonInsertCoin1(EngineClass *engine) { ProcessButtonInsertCoin(engine, 0); }
void ProcessButtonInsertCoin2(EngineClass *engine) { ProcessButtonInsertCoin(engine, 1); }
void ProcessButtonInsertCoin3(EngineClass *engine) { ProcessButtonInsertCoin(engine, 2); }
void ProcessButtonInsertCoin4(EngineClass *engine) { ProcessButtonInsertCoin(engine, 3); }
void ProcessButtonInsertCoin5(EngineClass *engine) { ProcessButtonInsertCoin(engine, 4); }
void ProcessButtonInsertCoin6(EngineClass *engine) { ProcessButtonInsertCoin(engine, 5); }

void ProcessButtonVolUp(EngineClass *engine) { Audio->VolumeUp(Config->ini_general->song_volume); }
void ProcessButtonVolDown(EngineClass *engine) { Audio->VolumeDown(Config->ini_general->song_volume); }

void ProcessButtonMute(EngineClass *engine)
{
  if (Audio->muted)
  {
    Audio->UnMute();
  }
  else
  {
    Audio->Mute();
  }
}

void ProcessButtonAddRandom(EngineClass *engine) {
  if (Config->skin_general->instant_play) // instant play, so clear out playqueue and stop current song
  {
    PlayQueue->Clear();
    Audio->StopSong(true);
    while (PlayQueue->NumSongsTotal()); // wait until queue is empty before adding another
  }
  PlayQueue->Add(Database->GetSong(), play_type_e::CreditPlay);
}

void ProcessButtonAttractModeTog(EngineClass *engine)
{
  if (++Config->attract_mode_select == Config->skin_general->attract_mode.size()) Config->attract_mode_select = 0;
  if (Config->skin_general->attract_mode[Config->attract_mode_select] == GenreOffStr) // turn off attract mode
  {
    Config->ini_attract->enable = false;
    engine->attract_timer = 0;
  }
  else // turn on attract mode
  {
    Config->ini_attract->enable = true;
    if (!PlayQueue->NumSongsTotal())
    {
      engine->attract_timer = 1 + Config->ini_attract->interval.ticks; // if queue empty, start attract timer if attract mode enabled (add 1 because 0 is disabled)
    }
  }
  engine->status_event |= StatusEvent_AttractModeModeChange;
}

void ProcessButtonLoopQueueTog(EngineClass *engine)
{
  if (Config->skin_general->no_duplicates == false) { // can only change loop mode if no_duplicates is disabled
    Config->ini_general->loop_playqueue = !Config->ini_general->loop_playqueue;
    engine->status_event |= StatusEvent_LoopModeChange;
  }
}

void ProcessButtonFlag(EngineClass *engine, uint32_t flag)
{
  Config->status_flag[flag] = !Config->status_flag[flag];
  engine->status_event |= StatusEvent_FlagChange;
}

void ProcessButtonFlag1(EngineClass *engine) { ProcessButtonFlag(engine, 1); }
void ProcessButtonFlag2(EngineClass *engine) { ProcessButtonFlag(engine, 2); }
void ProcessButtonFlag3(EngineClass *engine) { ProcessButtonFlag(engine, 3); }
void ProcessButtonFlag4(EngineClass *engine) { ProcessButtonFlag(engine, 4); }

void ProcessButtonFreeplayTog(EngineClass *engine)
{
  // NOTE ANY CHANGES IN THIS FUNCTION MUST ALSO BE MADE IN MainMenuSettings_EditFreeplay()
  Config->ini_general->free_play = !Config->ini_general->free_play;
  // if playing in freeplay mode, credits_per_coin will be zero, so set it to 1 (because when we subsequently enter
  // credit mode, inserting coins won't increase our song plays)
  // for (auto p = 0; p < Config->ini_general->credits_per_coin.size(); ++p)
  // {
    // if (Config->ini_general->credits_per_coin[p] == 0) Config->ini_general->credits_per_coin[p] = 1;
    // Config->ini_general->credits_per_coin_str[p] = to_string(Config->ini_general->credits_per_coin[p]);
  // }
  engine->status_event |= StatusEvent_FreeplayModeChange;
}

void ProcessButtonMouse(EngineClass *engine) { }

void ProcessButtonMenu(EngineClass *engine) {
  main_menu_active = true;
  DialogBaseClass::ActivateTouchControls();
  MainMenu->Draw();
  engine->ClrButtonBit(BUTTON_MENU);
}

void ProcessButtonSearch(EngineClass *engine)
{
  search_menu_active = true;
  DialogBaseClass::ActivateTouchControls();
  SearchMenu->Draw();
  engine->ClrButtonBit(BUTTON_SEARCH);
}

void ProcessButtonQuit(EngineClass *engine) { engine->Quit(false); }

void ProcessButtonPowerOff(EngineClass *engine) { engine->Quit(true); }

////////////////////////////////////////////////////////////////
// Engine class........

EngineClass::EngineClass()
{
  int32_t sel {};
  int32_t i {};

  ProcessButton.at(BUTTON_LEFT) = ProcessButtonLeft;
  ProcessButton.at(BUTTON_RIGHT) = ProcessButtonRight;
  ProcessButton.at(BUTTON_LEFT_SCREEN) = ProcessButtonLeftScreen;
  ProcessButton.at(BUTTON_RIGHT_SCREEN) = ProcessButtonRightScreen;
  ProcessButton.at(BUTTON_LEFT_SORT) = ProcessButtonLeftSort;
  ProcessButton.at(BUTTON_RIGHT_SORT) = ProcessButtonRightSort;
  ProcessButton.at(BUTTON_UP) = ProcessButtonUp;
  ProcessButton.at(BUTTON_DOWN) = ProcessButtonDown;
  ProcessButton.at(BUTTON_SELECT) = ProcessButtonSelect;
  ProcessButton.at(BUTTON_SKIP) = ProcessButtonSkip;
  ProcessButton.at(BUTTON_PAUSE) = ProcessButtonPause;
  ProcessButton.at(BUTTON_SCREENSHOT) = ProcessButtonScreenshot;
  ProcessButton.at(BUTTON_CLEARQUEUE) = ProcessButtonClearQueue;
  ProcessButton.at(BUTTON_0) = ProcessButtonSelect0;
  ProcessButton.at(BUTTON_1) = ProcessButtonSelect1;
  ProcessButton.at(BUTTON_2) = ProcessButtonSelect2;
  ProcessButton.at(BUTTON_3) = ProcessButtonSelect3;
  ProcessButton.at(BUTTON_4) = ProcessButtonSelect4;
  ProcessButton.at(BUTTON_5) = ProcessButtonSelect5;
  ProcessButton.at(BUTTON_6) = ProcessButtonSelect6;
  ProcessButton.at(BUTTON_7) = ProcessButtonSelect7;
  ProcessButton.at(BUTTON_8) = ProcessButtonSelect8;
  ProcessButton.at(BUTTON_9) = ProcessButtonSelect9;
  ProcessButton.at(BUTTON_A) = ProcessButtonSelectA;
  ProcessButton.at(BUTTON_B) = ProcessButtonSelectB;
  ProcessButton.at(BUTTON_C) = ProcessButtonSelectC;
  ProcessButton.at(BUTTON_D) = ProcessButtonSelectD;
  ProcessButton.at(BUTTON_E) = ProcessButtonSelectE;
  ProcessButton.at(BUTTON_F) = ProcessButtonSelectF;
  ProcessButton.at(BUTTON_G) = ProcessButtonSelectG;
  ProcessButton.at(BUTTON_H) = ProcessButtonSelectH;
  ProcessButton.at(BUTTON_I) = ProcessButtonSelectI;
  ProcessButton.at(BUTTON_J) = ProcessButtonSelectJ;
  ProcessButton.at(BUTTON_K) = ProcessButtonSelectK;
  ProcessButton.at(BUTTON_L) = ProcessButtonSelectL;
  ProcessButton.at(BUTTON_M) = ProcessButtonSelectM;
  ProcessButton.at(BUTTON_N) = ProcessButtonSelectN;
  ProcessButton.at(BUTTON_O) = ProcessButtonSelectO;
  ProcessButton.at(BUTTON_P) = ProcessButtonSelectP;
  ProcessButton.at(BUTTON_Q) = ProcessButtonSelectQ;
  ProcessButton.at(BUTTON_R) = ProcessButtonSelectR;
  ProcessButton.at(BUTTON_S) = ProcessButtonSelectS;
  ProcessButton.at(BUTTON_T) = ProcessButtonSelectT;
  ProcessButton.at(BUTTON_U) = ProcessButtonSelectU;
  ProcessButton.at(BUTTON_V) = ProcessButtonSelectV;
  ProcessButton.at(BUTTON_W) = ProcessButtonSelectW;
  ProcessButton.at(BUTTON_X) = ProcessButtonSelectX;
  ProcessButton.at(BUTTON_Y) = ProcessButtonSelectY;
  ProcessButton.at(BUTTON_Z) = ProcessButtonSelectZ;
  ProcessButton.at(BUTTON_INSERT_COIN1) = ProcessButtonInsertCoin1;
  ProcessButton.at(BUTTON_INSERT_COIN2) = ProcessButtonInsertCoin2;
  ProcessButton.at(BUTTON_INSERT_COIN3) = ProcessButtonInsertCoin3;
  ProcessButton.at(BUTTON_INSERT_COIN4) = ProcessButtonInsertCoin4;
  ProcessButton.at(BUTTON_INSERT_COIN5) = ProcessButtonInsertCoin5;
  ProcessButton.at(BUTTON_INSERT_COIN6) = ProcessButtonInsertCoin6;
  ProcessButton.at(BUTTON_VOL_UP) = ProcessButtonVolUp;
  ProcessButton.at(BUTTON_VOL_DOWN) = ProcessButtonVolDown;
  ProcessButton.at(BUTTON_MUTE) = ProcessButtonMute;
  ProcessButton.at(BUTTON_ADD_RANDOM) = ProcessButtonAddRandom;
  ProcessButton.at(BUTTON_ATTRACT_TOG) = ProcessButtonAttractModeTog;
  ProcessButton.at(BUTTON_LOOPQUEUE_TOG) = ProcessButtonLoopQueueTog;
  ProcessButton.at(BUTTON_FLAG_1) = ProcessButtonFlag1;
  ProcessButton.at(BUTTON_FLAG_2) = ProcessButtonFlag2;
  ProcessButton.at(BUTTON_FLAG_3) = ProcessButtonFlag3;
  ProcessButton.at(BUTTON_FLAG_4) = ProcessButtonFlag4;
  ProcessButton.at(BUTTON_FREEPLAY_TOG) = ProcessButtonFreeplayTog;
  ProcessButton.at(BUTTON_MENU) = ProcessButtonMenu;
  ProcessButton.at(BUTTON_SEARCH) = ProcessButtonSearch;
  ProcessButton.at(BUTTON_MOUSE) = ProcessButtonMouse;
  ProcessButton.at(BUTTON_QUIT) = ProcessButtonQuit;
  ProcessButton.at(BUTTON_POWER_OFF) = ProcessButtonPowerOff;

  song_video.event_queue = al_create_event_queue();
  if (song_video.event_queue == nullptr) error("Couldn't create song video event queue");
  auto_title_strip_turn_timer = Config->skin_general->auto_title_strip_turn_time.ticks;
  attract_timer = Config->ini_attract->enable ? 1 + Config->ini_attract->interval.ticks : 0;

  if (Config->ini_attract->fade_in_position.ticks < 0)
  {
    Config->ini_attract->fade_in_position.ticks = 0; // prevent negative fade in time
  }

  if (Config->ini_attract->fade_out_position.ticks <= Config->ini_attract->fade_in_position.ticks)
  {
    Config->ini_attract->fade_out_position.ticks = 0; // prevent fade out if stop time is earlier than start time (so will then play until end of song instead)
  }

  if (Config->ini_attract->max_volume > MaxSongVolume) Config->ini_attract->max_volume = MaxSongVolume;
  attract_max_volume_factor = Config->ini_attract->max_volume / 100.0;

  if (Config->ini_attract->fade_in.ticks)
  {
    attract_fade_in_step = 1 / static_cast<float>(Config->ini_attract->fade_in.ticks);
  }

  if (Config->ini_attract->fade_out.ticks)
  {
    attract_fade_out_step = 1 / static_cast<float>(Config->ini_attract->fade_out.ticks);
  }

  if (Config->skin_general->album_mode == false)
  {
    max_select_code = Config->skin_general->songs_per_title_strip * Config->skin_general->num_title_strips;
  }
  else
  {
    max_select_code = Config->skin_general->num_title_strips;
  }
}

EngineClass::~EngineClass()
{
#if 1
  // al_destroy_event_queue(EventQueue);
#endif
}

void EngineClass::Quit(bool p_off)
{
  quit = true;
  power_off = p_off;
};

// BPM_IDX indexes a button code into one of the two (64-bit) button_pressed_mask elements
// BPM_BIT specifies the bit position of the button in the 64-bit mask element

#define BPM_IDX(A) (A & static_cast<uint64_t>(1))
#define BPM_BIT(A) (static_cast<uint64_t>(1) << (A >> static_cast<uint64_t>(1)))

// when setting a button bit, we clear all the other button bits (so can only have one active button at any one time)
void EngineClass::SetButtonBit(uint32_t button)
{
  uint64_t b { static_cast<uint64_t>(button) };
  // cout << "SetButtonBit " << dec << button << " " << b << " " << BPM_IDX(b) << " " << hex << BPM_BIT(b) << endl;
  uint32_t idx { BPM_IDX(b) };
  button_pressed_mask[idx] = BPM_BIT(b);
  button_pressed_mask[1-idx] = 0;
}

// when clearing a button bit, we clear all the other button bits too
void EngineClass::ClrButtonBit(uint32_t button)
{
  uint64_t b { static_cast<uint64_t>(button) };
  // cout << "ClrButtonBit " << dec << button << " " << b << " " << BPM_IDX(b) << " " << hex << BPM_BIT(b) << endl;
  button_pressed_mask[0] = button_pressed_mask[1] = 0;
}

bool EngineClass::IsButtonBitSet(uint32_t button)
{
// cout << "IsButtonBitSet " << dec << button << " " << setw(16) << hex << button_pressed_mask[1] << " " << button_pressed_mask[0] << endl;
  if (button == BUTTON_ANY)
  {
    uint64_t b { button_pressed_mask[0] | button_pressed_mask[1] };
    if (b)
    {
      return true;
    }
  }

  else 
  {
    uint64_t b { static_cast<uint64_t>(button) };
    if (button_pressed_mask[BPM_IDX(b)] & BPM_BIT(b))
    {
      return true;
    }
  }
  
  return false;
}

void EngineClass::UpdateSelectCode
(
  const uint32_t title_strip,
  const uint32_t entry
)
{
  uint32_t sel_num { };

  if (Config->skin_general->album_mode == false)
  {
    sel_num = entry + (Config->skin_general->songs_per_title_strip * title_strip);
  }
  else
  {
    sel_num = entry + title_strip;
  }

  status.select_code_str = IntToSel(sel_num);
  status_event |= StatusEvent_SelCodeChange;
}

void EngineClass::UpdateSelectCode
(
  const char c
)
{
  if (Config->skin_general->select_mode == select_mode_e::JoyStick) return; // select code is persistent in joystick mode

  if (c == undefinedSelectDigit) // blank select code (for both SelectCode and TouchSong modes)
  {
    status.select_code_str.assign(Config->skin_general->select_buttons.size(), undefinedSelectDigit);
    select_code_digit = 0;
    status_event |= StatusEvent_SelCodeChange;
    return;
  }

  if ((Config->ini_general->free_play == false) && (status.credits < Config->ini_general->credits_per_song)) return; // no money left!

  if (Config->skin_general->select_mode == select_mode_e::TouchSong) return; // don't check keys in touch song mode

  char k {};
  for (auto &key : Config->skin_general->select_buttons.at(select_code_digit))
  {
    if (c == toupper(key))
    {
      k = key;
      break;
    }
  }

  if (k)
  { // pressed key within range, so update the corresponding digit of the select code string, and decide if any action needed
    status.select_code_str.at(select_code_digit) = k;
    if (select_code_digit == Config->skin_general->select_buttons.size() - 1) // last digit
    {
      select_code_digit = 0; // so move to first digit for next time
      if (Config->skin_general->auto_select)
      {
        CheckAndAddSelection(); // don't need to press SELECT key in this mode
      }
      else
      {
        EngineThread_event |= EventToTimerThread_StartSelCodeTimer; // start timer ... if user doesn't press Select key within a certain time we clear the select code
      }
    }
    else
    {
      select_code_digit++; // move to next digit for next time
      for (auto d = select_code_digit; d < Config->skin_general->select_buttons.size(); d++)  status.select_code_str.at(d) = undefinedSelectDigit;  // reset all select digits to the right of current one
      EngineThread_event |= EventToTimerThread_StartSelCodeTimer; // start timer ... if user doesn't press second digit within a certain time we clear the select code
    }

  }
  // set StatusEvent_SelCodeChange in both status_event and TimerThread_status_event as 
  status_event |= StatusEvent_SelCodeChange;
  TimerThread_status_event |= StatusEvent_SelCodeChange;
}

///////////////////////////////////////////////////////////////////////////////
// SelectSong()
// convert (joystick) x and y into title_strip and entry, then retrieve song from database

song_t* EngineClass::SelectSong
(
  const uint32_t x,
  const uint32_t y
)
{
  uint32_t title_strip = start_title_strip + x;
  uint32_t entry = y;

  selected_song_title_strip = title_strip;

  if (title_strip >= Database->number_of_title_strips) return nullptr;

  return Database->GetSong(title_strip, entry);
}

///////////////////////////////////////////////////////////////////////////////
// SelectSong()
// convert 2-digit select code to title_strip and entry, then retrieve song from database

song_t* EngineClass::SelectSong
(
  const string &sel_code
)
{
  song_t *song;
  uint32_t entry;

  int32_t sel_num_in_title_strip_group = static_cast<int32_t>(SelToInt(sel_code));

  if (sel_num_in_title_strip_group == -1) return nullptr;

  if (sel_num_in_title_strip_group >= max_select_code) return nullptr;

  if (Config->skin_general->album_mode == false)
  {
    selected_song_title_strip = start_title_strip + (sel_num_in_title_strip_group / Config->skin_general->songs_per_title_strip);
    entry = sel_num_in_title_strip_group % Config->skin_general->songs_per_title_strip;
  }
  else
  {
    selected_song_title_strip = start_title_strip + sel_num_in_title_strip_group;
    entry = 0;
  }

  if (selected_song_title_strip >= Database->number_of_title_strips) return nullptr;

  return Database->GetSong(selected_song_title_strip, entry);
}

string EngineClass::IntToSel
(
  const int32_t selection
)
{
  string code {};
  uint32_t sel = selection;

  if (Config->skin_general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
  {
    for (auto dig = 0; dig < Config->skin_general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      code += Config->skin_general->select_buttons[dig].at(sel / Config->select_digit_base.at(dig));
      sel = sel % Config->select_digit_base.at(dig);
    }
  }
  else
  {
    for (auto dig = 0; dig < Config->skin_general->select_buttons.size(); ++dig) // for each select button digit string...
    {
       code += Config->skin_general->select_buttons[dig].at(sel % Config->skin_general->select_buttons.at(dig).size());
       sel = sel / Config->skin_general->select_buttons.at(dig).size();
    }
  }
  return code;
}

uint32_t EngineClass::SelToInt
(
  const string &sel_code
)
{
  uint32_t sel_num_in_title_strip_group;

  if (sel_code.size() != Config->skin_general->select_buttons.size()) return -1; // number of select code characters doesn't match number of select_buttons digits

  // search each select_buttons string and update select_digit_value array
  // each element select_digit_value array holds the position (value) or the sel_code button press for that digit

  if (Config->skin_general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
  {
    sel_num_in_title_strip_group = 0;
    for (auto dig = 0; dig < Config->skin_general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      size_t val { static_cast<size_t>(Config->skin_general->select_buttons[dig].find_first_of(sel_code.at(dig))) };
      if (val == string::npos) return -1; // invalid character
      sel_num_in_title_strip_group += val * Config->select_digit_base.at(dig);
    }
  }
  else
  {
    sel_num_in_title_strip_group = 0;
    for (auto dig = 0; dig < Config->skin_general->select_buttons.size(); ++dig) // for each select button digit string...
    {
      size_t val { static_cast<size_t>(Config->skin_general->select_buttons[dig].find_first_of(sel_code.at(dig))) };
      if (val == string::npos) return -1; // invalid character
      sel_num_in_title_strip_group += val * Config->select_digit_base.at(dig);
    }
  }

  return sel_num_in_title_strip_group;
}


///////////////////////////////////////////////////////////////////////////////
// CheckAndAddSelection()
// checks if a valid song is at the selected slot, and if so adds it to the playqueue
//

void EngineClass::CheckAndAddSelection(void)
{
  song_t *song { };

  if (Config->skin_general->select_mode == select_mode_e::SelectCode)
  {
    song = SelectSong(status.select_code_str);
  }
  else // Joystick or TouchSong
  {
    song = SelectSong(joy_x, joy_y);
  }

  invalid_choice = false; // assume user has made a valid choice

  if (song == nullptr)
  {
    invalid_choice = true;
  }
  else
  {
    if (Config->skin_general->instant_play) // instant play, so clear out playqueue
    {
      PlayQueue->Clear();
      Audio->StopSong(true);
      while (PlayQueue->NumSongsTotal()); // wait until queue is empty before adding another
    }

    // add song to playqueue (if it's not in the history and we're in song_history_include_user_selection mode)
    if (Config->skin_general->album_mode == false)
    {
      if ((Database->SongIsInHistory(song) == false) || (Config->ini_general->song_history_include_user_selection == false))
      {
        duplicate_choice = PlayQueue->Add(song, play_type_e::CreditPlay);
      }
    }
    else // add all songs in the album, i.e. from this song to all others following it on the rest of the title_strip...
    {
      for (uint32_t s = 0; s < Config->skin_general->songs_per_title_strip; ++s)
      {
        song = SelectSong(selected_song_title_strip - start_title_strip, s);
        if (song == nullptr) break;
        if ((Database->SongIsInHistory(song) == false) || (Config->ini_general->song_history_include_user_selection == false))
        {
          duplicate_choice = PlayQueue->Add(song, play_type_e::CreditPlay);
        }
      }
    }

  }

  if (Config->skin_general->auto_select)
  {
    EngineThread_event |= EventToTimerThread_StartSelCodeTimerHold; // start timer ... hold the selected code for a short while
  }
  else
  {
    EngineThread_event |= EventToTimerThread_ClearSelectCode; // clear the selected code immediately Select is pressed
  }

  status_event |= StatusEvent_ChooseSong;
}

void EngineClass::UpdateJoystickPositions
(
  const uint32_t x,
  const uint32_t y
)
{
  Config->joystick->SetPositionToTitleStrip(x, y);
  UpdateSelectCode(x, y);
}

void EngineClass::TimerThread(void)
{
  time_t time_prev { };
  float song_load_delta { };
  ALLEGRO_TIMER *timer = al_create_timer(1.0 / static_cast<float>(display_refresh_rate));
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_EVENT event;

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_start_timer(timer);
  
  mouse_move_timer = Config->mouse->hide_after.ticks; // ensures mouse blanks correctly if it's never moved

  while (Engine_finished == false)
  {
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER)
    {
      #ifdef _RPI4
      TimerThread_event |= EventFromTimerThread_VideoTick;
      #endif
      
      { // first check main engine -> timer thread comms events ...
        uint32_t engine_event = EngineThread_event.fetch_and(0) | Input->status_event.fetch_and(0);
        if (engine_event)
        {
          if (engine_event & EventToTimerThread_MouseMove)
          {
            mouse_move_timer = Config->mouse->hide_after.ticks;
            TimerThread_event |= EventFromTimerThread_ShowMouse;
          }
          
          if (engine_event & EventToTimerThread_AutoPageTurnRestart)
          {
            auto_title_strip_turn_timer = Config->skin_general->auto_title_strip_turn_time.ticks;
          }
 
          if (engine_event & EventToTimerThread_StartSelCodeTimer)
          {
            sel_code_timer = Config->skin_general->select_timeout.ticks;
          }

          if (engine_event & EventToTimerThread_StopSong)
          {
            attract_fading_in = attract_fading_out = attract_fade_out = false; // ensure fading stopped when song finishes for a different reason (i.e. reaches natural end)
          }

          if (engine_event & EventToTimerThread_StartSong)
          {
            attract_fading_in = attract_fading_out = attract_fade_out = false;

            if (status.now_playing->play_type == play_type_e::AttractMode)
            {
              if (Config->ini_attract->fade_in.ticks)
              {
                attract_fading_in = true;
                attract_fade_in_factor = 0.0; // silent at the start
                TimerThread_volume = 0;
                TimerThread_event |= EventFromTimerThread_SetVolume;
                // Audio->SetVolume(0.0);
              }

              if (Config->ini_attract->fade_out_position.ticks)
              {
                attract_fade_out = true;
              }
            }
            else
            {
              TimerThread_volume = Config->ini_general->song_volume;
              TimerThread_event |= EventFromTimerThread_SetVolume;
            }
          }

          if (engine_event & EventToTimerThread_SongLoad)
          {
            status.now_playing_time_remaining_scale = 0.0;
            status.song_load_position = 0.0;
            song_load_delta = 1.0 / (float)(Config->skin_general->song_load_time.ticks);
          }

          if (engine_event & EventToTimerThread_SongUnload)
          {
            // status.now_playing_time_remaining_scale = 1.0;
            // status.song_load_position = 1.0;
            song_load_delta = 1.0 / (float)(Config->skin_general->song_unload_time.ticks);
          }

          if (engine_event & EventToTimerThread_StartSelCodeTimerHold)
          {
            sel_code_timer = Config->skin_general->select_hold_timeout.ticks;
          }

          if (engine_event & EventToTimerThread_ClearSelectCode)
          {
            sel_code_timer = 1;
          }

        }
      }

      ///////////////////////////////////////////////////////////////////////////
      // update timers .. timers expressed in video frames (not seconds)

      TimerThread_status_event |= (StatusEvent_TimerChange | StatusEvent_ScrollText);

      if (Audio->spectrum_analyser) TimerThread_status_event |= StatusEvent_AudioBandsChange;

      if (sel_code_timer)
      {
        if (--sel_code_timer == 0) {
          TimerThread_event |= EventFromTimerThread_ClearSelectCode;
        }
      }

      if (attract_timer)
      {
        if (--attract_timer == 0)
        { // attract mode gap elapsed, so start a random song
          TimerThread_event |= EventFromTimerThread_AddAttractSong;
        }
      }

      if (mouse_move_timer)
      {
        if (--mouse_move_timer == 0) // make mouse invisible
        {
          TimerThread_event |= EventFromTimerThread_HideMouse;
        }
      }

      if (auto_title_strip_turn_timer)
      {
        if (--auto_title_strip_turn_timer == 0) // move title_strip right
        {
          screen_jump = 1;
          TimerThread_event |= EventFromTimerThread_AutoPageTurn;
        }
      }

      time_t time_now { time(nullptr) };
      if (time_now != time_prev) // one second elapsed since last check
      {
        time_prev = time_now;
        TimerThread_status_event |= StatusEvent_OneSecondChange;
      }

      ///////////////////////////////////////////////////////////////////////////
      // Attract mode fade in / out

      // increase song volume for attract mode fade in (attract_fade_in_factor goes from 0.0 to 1.0 over the user specified time)
      if (attract_fading_in)
      {
        if (attract_fade_in_factor >= 1.0)
        {
          attract_fading_in = false; // finished fading in
        }
        else
        {
          attract_fade_in_factor += attract_fade_in_step;
          TimerThread_volume = static_cast<uint32_t>(attract_fade_in_factor * attract_max_volume_factor * Config->ini_general->song_volume);
          TimerThread_event |= EventFromTimerThread_SetVolume;
        }
      }

      // song load position (for loading and unloading)
      
      if (Audio->song_play_state == song_play_state_e::loading)
      {
        status.song_load_position += song_load_delta;
      }
      
      if (Audio->song_play_state == song_play_state_e::unloading)
      {
        status.song_load_position -= song_load_delta;
      }
          
      // decrease song volume for attract mode fade out (attract_fade_out_factor goes from 1.0 to 0.0 over the user specified time)
      if (attract_fading_out)
      {
        if (attract_fade_out_factor <= 0.0) // faded out, so stop song
        {
          TimerThread_event |= EventFromTimerThread_StopSong;
          attract_fading_out = false;
        }
        attract_fade_out_factor -= attract_fade_out_step;
        TimerThread_volume = attract_fade_out_factor * attract_max_volume_factor * Config->ini_general->song_volume;
        TimerThread_event |= EventFromTimerThread_SetVolume;
      }

      TimerThread_event |= EventFromTimerThread_CheckVideo;

    }
  }
  
  TimerThread_finished = true;
  al_destroy_timer(timer);
}

void EngineClass::Run(void)
{
  static bool title_strip_prev_idle { false };

  bool refresh_display { true };
  
  thread TimerThread { &EngineClass::TimerThread, this };
  TimerThread.detach();

  Audio->SetVolume(Config->ini_general->song_volume, true);

  log_file << "Let's Rock!" << endl;

  Audio->Run();

  // clear the input button queue before we start...
  Input->queue_mtx.lock();
  Input->queue.clear();
  Input->queue_mtx.unlock();

  while (quit == false)
  {
    ///////////////////////////////////////////////////////////////////////////
    // check for button events


    if (main_menu_active)
    {
      if (MainMenu->Run()) // ready to exit from the Main menu
      {
        main_menu_active = false;
        DialogBaseClass::DeActivateTouchControls();
        // button_pressed_mask.reset(BUTTON_MENU);
        // ClrButtonBit(BUTTON_MENU);
      }
    }
    else if (search_menu_active)
    {
      SearchMenu->Draw();

      if (SearchMenu->Run()) // ready to exit from the Search menu
      {
        if (SearchMenu->changed)
        {
          Database->Filter(); // do the search
          SearchMenu->changed = false;
        }
        search_menu_active = false;
        DialogBaseClass::DeActivateTouchControls();
        // button_pressed_mask.reset(BUTTON_SEARCH);
        // ClrButtonBit(BUTTON_SEARCH);
      }
    }
    else
    {
      if (Input->queue.size()) // user input controls jukebox itself
      {
        Input->queue_mtx.lock();
        uint32_t event_code = Input->queue.front();
        uint32_t keycode = event_code & BUTTON_MASK;
        Input->queue.pop_front();
        Input->queue_mtx.unlock();
        if (event_code & BUTTON_RELEASED)
        {
          // button_pressed_mask &= ~(static_cast<uint64_t>(1) << static_cast<uint64_t>(keycode));
          // button_pressed_mask.reset(keycode);
          ClrButtonBit(keycode);
        }
        else
        {
          if (event_code & TOUCH_SONG)
          {
            joy_x = (event_code >> SONG_TITLE_STRIP_POS) & SONG_POS_MASK;
            joy_y = (event_code >> SONG_ENTRY_POS) & SONG_POS_MASK;
            UpdateSelectCode(joy_x, joy_y);
          }
          else
          {
            // button_pressed_mask.set(keycode);
            SetButtonBit(keycode);
            
            if (keycode < NUM_BUTTONS)
            {
              ProcessButton.at(keycode)(this);
            }
          }
        }
        status_event |= StatusEvent_ButtonChange;
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    // update certain status strings depending on certain status events...

    // gather status flags from other threads...
    status_event |= Audio->SongPlayThread_status_event.fetch_and(0);
    status_event |= Audio->LoadArtworkThread_status_event.fetch_and(0);
    status_event |= AudioClass::GetCURLDataThread_status_event.fetch_and(0);
    status_event |= TimerThread_status_event.fetch_and(0);
    status_event |= PlayQueue->status_event.fetch_and(0);

    if (quit)
    {
      status_event |= StatusEvent_SongVideoStop;
    }
    
    { // timer thread -> engine thread comms... 
      uint32_t timer_event = TimerThread_event.fetch_and(0);
      if (timer_event)
      {
        #ifdef _RPI4
        if (timer_event & EventFromTimerThread_VideoTick)
        {
          refresh_display = true;
        }
        #endif
        
        if (timer_event & EventFromTimerThread_HideMouse)
        {
          Config->mouse->visible = false;
        }
        
        if (timer_event & EventFromTimerThread_ShowMouse)
        {
          Config->mouse->visible = true;
        }
        
        if (timer_event & EventFromTimerThread_ClearSelectCode)
        {
          UpdateSelectCode(undefinedSelectDigit); // timeout for partially selected code
        }

        if (timer_event & EventFromTimerThread_AddAttractSong)
        {
          if (Config->ini_attract->choice == attract_choice_e::Random)
          {
            PlayQueue->Add(Database->GetGenreSong(Config->skin_general->attract_mode[Config->attract_mode_select]), play_type_e::AttractMode);
          }
          else // add next song from sorted list
          {
            PlayQueue->Add(Database->GetNextSong(), play_type_e::AttractMode);
          }
        }

        if (timer_event & EventFromTimerThread_AutoPageTurn)
        {
          title_strip_turn_right = true; // will restart timer later in code
        }
        
        if (timer_event & EventFromTimerThread_SetVolume)
        {
          Audio->SetVolume(TimerThread_volume);
        }

        if (timer_event & EventFromTimerThread_StopSong)
        {
          Audio->StopSong(false);
        }

        if (timer_event & EventFromTimerThread_CheckVideo)
        {
          if (song_video.handle)
          {
            if ((AudioClass::paused == true) && (al_is_video_playing(song_video.handle)))
            {
              al_set_video_playing(song_video.handle, false); // pause video
            }
            else if ((AudioClass::paused == false) && (!al_is_video_playing(song_video.handle)))
            {
              al_set_video_playing(song_video.handle, true); // un-pause video
            }
          }

          if (al_get_next_event(song_video.event_queue, &song_video.event))
          {
            switch (song_video.event.type)
            {
              // case ALLEGRO_EVENT_VIDEO_FRAME_SHOW :
                // status_event |= StatusEvent_SongVideoShow;
                // break;

              case ALLEGRO_EVENT_VIDEO_FINISHED :
                Audio->StopSong(false);
                break;
            }
          }

          if (song_video.playing)
          {
            status_event |= StatusEvent_SongVideoShow;
          }
        }
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    // update title_strip event status if title_strip turn initiated...

    if (status_event & StatusEvent_NewDatabaseSearch)
    { // pages have been rebuilt, so reset visible page back to the first
      start_title_strip = 0;
      screen_jump = 0;
      title_strip_turn_right = true;
    }

    // status.title_strips_moving = false; // assume title_strips idle

    if (title_strip_turn_right)
    {
      if (TitleStripDisplayClass::idle)
      {
        title_strip_turn_right = false;
        if (Database->number_of_title_strips > Config->skin_general->num_title_strips || (screen_jump == 0)) // don't draw if not enough title_strips (unless redrawing after database search (screen_jump == 0))
        {
          start_title_strip += screen_jump * Config->skin_general->num_title_strips;
          if (start_title_strip >= Database->number_of_title_strips) start_title_strip = 0;

          TitleStripDisplayClass::start_title_strip = start_title_strip;
          status.first_visible_title_strip_str = to_string(1 + TitleStripDisplayClass::start_title_strip);
          status.last_visible_title_strip_str = to_string(TitleStripDisplayClass::start_title_strip + Config->skin_general->num_title_strips);
          // status.title_strips_moving = true;
          TitleStripDisplayClass::move_direction = title_strip_move_direction_e::Right;
          status_event |= StatusEvent_TitleStripMoveChange;
          EngineThread_event |= EventToTimerThread_AutoPageTurnRestart; // for timer thread to restart auto timer
        }
      }
    }
    else if (title_strip_turn_left)
    {
      if (TitleStripDisplayClass::idle)
      {
        title_strip_turn_left = false;
        if (Database->number_of_title_strips > Config->skin_general->num_title_strips) // don't draw if not enough title_strips
        {
          start_title_strip -= screen_jump * Config->skin_general->num_title_strips;
          if (start_title_strip < 0) start_title_strip = Config->skin_general->num_title_strips * ((Database->number_of_title_strips - 1) / Config->skin_general->num_title_strips);

          TitleStripDisplayClass::start_title_strip = start_title_strip;
          status.first_visible_title_strip_str = to_string(1 + TitleStripDisplayClass::start_title_strip);
          status.last_visible_title_strip_str = to_string(TitleStripDisplayClass::start_title_strip + Config->skin_general->num_title_strips);
          // status.title_strips_moving = true;
          TitleStripDisplayClass::move_direction = title_strip_move_direction_e::Left;
          status_event |= StatusEvent_TitleStripMoveChange;
          EngineThread_event |= EventToTimerThread_AutoPageTurnRestart; // for timer thread to restart auto timer
        }
      }
    }

    if (status_event)
    {
      
      if (status_event & StatusEvent_SongStop)
      {
        EngineThread_event |= EventToTimerThread_StopSong;
      }

      if (status_event & StatusEvent_SongStart)
      {
        now_playing_paused_time = 0;
        EngineThread_event |= EventToTimerThread_StartSong;
      }

      if (status_event & StatusEvent_SongVideoStop)
      {
        if (song_video.handle)
        {
          al_set_video_playing(song_video.handle, false);
          al_close_video(song_video.handle);
          al_unregister_event_source(song_video.event_queue, al_get_video_event_source(song_video.handle));
          song_video.handle = nullptr;
        }
        song_video.playing = false;
      }

      if (status_event & StatusEvent_SongVideoStart)
      {
        song_video.handle = al_open_video(status.now_playing->filename.c_str());
        if (song_video.handle == nullptr)
        {
          log_file << WARNING << "Can't open Video file '" << status.now_playing->filename << "'" << endl;
          Audio->StopSong(false);
        }
        else
        {
          al_register_event_source(song_video.event_queue, al_get_video_event_source(song_video.handle));
          al_start_video(song_video.handle, AudioClass::songs_mixer );
          al_set_video_playing(song_video.handle, true); // un-pause video
          song_video.playing = true;
        }
      }

      if (status_event & StatusEvent_OneSecondChange)
      {
        if (Audio->song_play_state == song_play_state_e::playing)
        {
          time_t time_now { time(nullptr) };
          uint32_t l { status.now_playing->length };
          if (AudioClass::paused) now_playing_paused_time++;
          uint32_t et { static_cast<uint32_t>(time_now - static_cast<time_t>(status.now_playing_start_time) - now_playing_paused_time) };
          status.now_playing_elapsed_time_str = StrMinSec(et);

          if (l == 0) // undefined time (ogv or url)
          {
            status.now_playing_length_str = invalidTimeMS;
            status.now_playing_time_remaining_str = invalidTimeMS;
            status.now_playing_time_remaining_scale = 0.0;
          }
          else // defined length
          {
            uint32_t tr { l - et };
            status.now_playing_length_str = StrMinSec(l);
            status.now_playing_time_remaining_str = StrMinSec(tr);
            status.now_playing_time_remaining_scale = 1.0 - (static_cast<float>(tr) / static_cast<float>(l));
          }

          if (attract_fade_out)
          {
            if (et >= Config->ini_attract->fade_out_position.ticks / display_refresh_rate) // start the fade out...
            {
              attract_fade_out = false;
              attract_fading_out = true;
              attract_fade_out_factor = attract_fade_in_factor; // start fading out from last fade in point (to prevent volume step if fade in didn't finish before fade out started)
            }
          }

        }
      }

      if (status_event & StatusEvent_StopAttractModeTimer)
      {
        attract_timer = 0; // cancel any pending attract mode addition
      }
      
      if (status_event & StatusEvent_StartAttractModeTimer)
      {
        attract_timer = 1 + Config->ini_attract->interval.ticks; // if queue empty, start attract timer if attract mode enabled (add 1 because 0 is disabled)
      }

      if (status_event & StatusEvent_PlayQueueChange)
      {
        status.coming_up_num_songs_str = PlayQueue->NumSongsComingUpStr();
        status.coming_up_total_length_str = PlayQueue->TotalTimeComingUp();
        status.playqueue_space_str = PlayQueue->RemainingSpaceStr();
        // if (Config->ini_attract->enable && !PlayQueue->NumSongsTotal())
        // {
          // attract_timer = 1 + Config->ini_attract->interval.ticks; // if queue empty, start attract timer if attract mode enabled (add 1 because 0 is disabled)
        // }
      }

      if (status_event & StatusEvent_SongLoad)
      {
        EngineThread_event |= EventToTimerThread_SongLoad;
      }

      if (status_event & StatusEvent_SongUnload)
      {
        EngineThread_event |= EventToTimerThread_SongUnload;
      }
      
      if (status_event & StatusEvent_CreditsChange)
      {
        // work out how many somgs we can choose to play from the total number of credits inserted...
        status.songs_credited = status.credits / Config->ini_general->credits_per_song;

        {
          stringstream s {};
          s << setfill('0') << setw(2) << status.credits;
          status.credits_str = s.str();
        }

        {
          stringstream s {};
          s << setfill('0') << setw(2) << status.songs_credited;
          status.songs_credited_str = s.str();
        }
      }

      if (status_event & StatusEvent_ICYDataReady)
      {
        string str { reinterpret_cast< char const* >(AudioClass::curl_icy.metadata) };
        size_t pos;
        
        // Search for StreamTitle and then put quoted string into status.now_playing->stream_title
        if ((pos = str.find("StreamTitle='")) != string::npos)
        {
          string ss { str.substr(pos+13, string::npos) }; // jump over "StreamTitle='"
          size_t closing_quote { ss.find_first_of("'") };
          if (closing_quote != string::npos) ss.erase(closing_quote);
          getline(istringstream(ss), status.now_playing->stream_title);
        }

        // Search for StreamUrl and then put quoted string into status.now_playing->stream_url
        if ((pos = str.find("StreamUrl='")) != string::npos)
        {
          string ss { str.substr(pos+11, string::npos) }; // jump over "StreamUrl='"
          size_t closing_quote { ss.find_first_of("'") };
          if (closing_quote != string::npos) ss.erase(closing_quote);
          getline(istringstream(ss), status.now_playing->stream_url);
        }
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    // update all display objects...

    if (refresh_display) // Pi4 vsync doesn't work?
    {
      // refresh_spectrum_analyser_band = 1;
      
      TitleStripDisplayClass::title_strip_offset = 0; // first title_strip in display is zero
      title_strip_prev_idle = TitleStripDisplayClass::idle;
      TitleStripDisplayClass::idle = true; // assume all title_strips are idle (update(s) below will change this flag if any title_strip not idle)

      // reset status counters for coming up lists...
      StatusDisplayClass::if_song_coming_ups          = 0;
      StatusDisplayClass::coming_up_song_title        = 0;
      StatusDisplayClass::coming_up_song_artist       = 0;
      StatusDisplayClass::coming_up_song_year         = 0;
      StatusDisplayClass::coming_up_song_genre        = 0;
      StatusDisplayClass::coming_up_song_album        = 0;
      StatusDisplayClass::coming_up_song_length       = 0;
      StatusDisplayClass::coming_up_song_album_artist = 0;
      StatusDisplayClass::coming_up_song_track_number = 0;
      StatusDisplayClass::coming_up_song_publisher    = 0;
      StatusDisplayClass::coming_up_song_isrc         = 0;
      StatusDisplayClass::coming_up_song_custom_tag   = 0;

      for (auto i : Config->skin_display_object)
      {
        i->update(status_event);
      }

      if (Config->joystick->enabled)
      {
        Config->joystick->update(status_event);
      }

      ///////////////////////////////////////////////////////////////////////////
      // render the display...

      // draw jukebox...
      Display->DrawJukebox();
      // draw active on-screen menu...
      if (main_menu_active)
      {
        MainMenu->Show(false);
      }
      else if (search_menu_active)
      {
        SearchMenu->Show(false);
      }

      // draw mouse pointer...
      if (Input->mouse_active)
      {
        Config->mouse->update(status_event);
        Config->mouse->draw();
      }

      // if (Config->ini_general->mouse_pointer_enabled)
      // {
        // bitmap_t *b { &Config->ini_general->mouse_pointer_bm };
        // al_draw_bitmap(b->handle, Input->mouse_pointer_x, Input->mouse_pointer_y, 0);
      // }

      al_flip_display();
      #ifdef _RPI4
      refresh_display = false;
      #endif

      // if title strips move status changes then trigger status flag for next update...
      if (title_strip_prev_idle != TitleStripDisplayClass::idle)
      {
        if (TitleStripDisplayClass::idle) // title strips have stopped moving
        {
          TitleStripDisplayClass::move_direction = title_strip_move_direction_e::None;
          next_status_event |= StatusEvent_TitleStripMoveChange;
        }
      }
      
      ///////////////////////////////////////////////////////////////////////////
      // clear status events for next loop...
      // next_status_event contains status which could have been generated by above update() calls
      
      status_event = next_status_event;
      next_status_event = 0;
    }
  }

  ///////////////////////////////////////////////////////////////////////////
  // finish up...
  Engine_finished = true;
}
