#pragma once

#include "fruitbox.hpp"

constexpr uint32_t EventFromTimerThread_ClearSelectCode         { 0x00000001 };
constexpr uint32_t EventFromTimerThread_AddAttractSong          { 0x00000002 };
constexpr uint32_t EventFromTimerThread_AutoPageTurn            { 0x00000004 };
constexpr uint32_t EventFromTimerThread_StopSong                { 0x00000008 };
constexpr uint32_t EventFromTimerThread_SetVolume               { 0x00000010 };
constexpr uint32_t EventFromTimerThread_CheckVideo              { 0x00000020 };
constexpr uint32_t EventFromTimerThread_HideMouse               { 0x00000040 };
constexpr uint32_t EventFromTimerThread_ShowMouse               { 0x00000080 };
constexpr uint32_t EventFromTimerThread_VideoTick               { 0x00000100 };

constexpr uint32_t EventToTimerThread_AutoPageTurnRestart       { 0x00000001 };
constexpr uint32_t EventToTimerThread_StartSelCodeTimer         { 0x00000002 };
constexpr uint32_t EventToTimerThread_StartSelCodeTimerHold     { 0x00000004 };
constexpr uint32_t EventToTimerThread_ClearSelectCode           { 0x00000008 };
constexpr uint32_t EventToTimerThread_StopSong                  { 0x00000010 };
constexpr uint32_t EventToTimerThread_StartSong                 { 0x00000020 };
constexpr uint32_t EventToTimerThread_MouseMove                 { 0x00000040 };
constexpr uint32_t EventToTimerThread_SongLoad                  { 0x00000080 };
constexpr uint32_t EventToTimerThread_SongUnload                { 0x00000100 };


class EngineClass {
public:
  EngineClass();
  ~EngineClass();
  void Run(void);
  void Quit(bool p_off);
  void SetButtonBit(uint32_t button);
  void ClrButtonBit(uint32_t button);
  bool IsButtonBitSet(uint32_t button);
  string IntToSel(const int32_t selection);
  uint32_t SelToInt(const string &sel_code);
  uint32_t max_select_code;
  uint32_t sel_code_timer { };
  uint32_t auto_title_strip_turn_timer { };
  uint32_t mouse_move_timer { };
  uint32_t attract_timer { };
  uint32_t status_event { };
  uint32_t next_status_event { };
  uint32_t joy_x { };
  uint32_t joy_y { };
  bool invalid_choice { false };
  bool duplicate_choice { false };
  // bitset<NUM_BUTTONS + 1> button_pressed_mask { 0 };
  video_t song_video {};
  bool song_playing { false };
  void UpdateJoystickPositions(const uint32_t x, const uint32_t y);
  bool title_strip_turn_right {false};
  bool title_strip_turn_left {false};
  uint32_t screen_jump { 1 };
  int32_t start_title_strip { };
  void CheckAndAddSelection(void);
  void UpdateSelectCode(const uint32_t title_strip, const uint32_t entry);
  void UpdateSelectCode(const char c);
  bool power_off { false };
  
private:
  bool quit { false };
  void TimerThread(void);
  atomic<int32_t>TimerThread_status_event {};
  atomic<int32_t>TimerThread_event {};
  uint32_t TimerThread_volume {};
  atomic<int32_t>EngineThread_event {};
  array<void(*)(EngineClass *engine), NUM_BUTTONS> ProcessButton;
  song_t* SelectSong(const string &sel_code);
  song_t* SelectSong(const uint32_t x, const uint32_t y);
  uint64_t button_pressed_mask[2] { 0, 0 }; // each element holds max 64 buttons
  int32_t select_code_digit { };
  int32_t selected_song_title_strip { };
  uint32_t now_playing_paused_time { };
  bool attract_fading_in { false };
  bool attract_fade_out { false };
  bool attract_fading_out { false };
  float attract_fade_in_factor { 0.0 };
  float attract_fade_out_factor { 1.0 };
  float attract_fade_in_step { 1.0 };
  float attract_fade_out_step { 1.0 };
  float attract_max_volume_factor { 1.0 };
};
