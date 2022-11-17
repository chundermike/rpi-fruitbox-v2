#pragma once

#include "fruitbox.hpp"

#define BUTTON_QUIT              0
#define BUTTON_INSERT_COIN1      1
#define BUTTON_INSERT_COIN2      2
#define BUTTON_INSERT_COIN3      3
#define BUTTON_INSERT_COIN4      4
#define BUTTON_INSERT_COIN5      5
#define BUTTON_INSERT_COIN6      6
#define BUTTON_VOL_UP            7
#define BUTTON_VOL_DOWN          8
#define BUTTON_ADD_RANDOM        9
#define BUTTON_SELECT            10
#define BUTTON_SKIP              11
#define BUTTON_PAUSE             12
#define BUTTON_UP                13
#define BUTTON_DOWN              14
#define BUTTON_LEFT              15
#define BUTTON_RIGHT             16
#define BUTTON_LEFT_SCREEN       17
#define BUTTON_RIGHT_SCREEN      18
#define BUTTON_LEFT_SORT         19
#define BUTTON_RIGHT_SORT        20
#define BUTTON_ATTRACT_TOG       21    
#define BUTTON_LOOPQUEUE_TOG     22    
#define BUTTON_FREEPLAY_TOG      23    
#define BUTTON_CLEARQUEUE        24    
#define BUTTON_MUTE              25    
#define BUTTON_POWER_OFF         26
#define BUTTON_0                 27    
#define BUTTON_1                 28    
#define BUTTON_2                 29    
#define BUTTON_3                 30    
#define BUTTON_4                 31    
#define BUTTON_5                 32    
#define BUTTON_6                 33    
#define BUTTON_7                 34    
#define BUTTON_8                 35    
#define BUTTON_9                 36    
#define BUTTON_A                 37    
#define BUTTON_B                 38    
#define BUTTON_C                 39    
#define BUTTON_D                 40    
#define BUTTON_E                 41    
#define BUTTON_F                 42    
#define BUTTON_G                 43    
#define BUTTON_H                 44    
#define BUTTON_I                 45    
#define BUTTON_J                 46  
#define BUTTON_K                 47
#define BUTTON_L                 48
#define BUTTON_M                 49
#define BUTTON_N                 50
#define BUTTON_O                 51
#define BUTTON_P                 52
#define BUTTON_Q                 53
#define BUTTON_R                 54
#define BUTTON_S                 55
#define BUTTON_T                 56
#define BUTTON_U                 57
#define BUTTON_V                 58
#define BUTTON_W                 59
#define BUTTON_X                 60
#define BUTTON_Y                 61
#define BUTTON_Z                 62
#define BUTTON_FLAG_1            63
#define BUTTON_FLAG_2            64
#define BUTTON_FLAG_3            65
#define BUTTON_FLAG_4            66
#define BUTTON_MENU              67
#define BUTTON_SEARCH            68
#define BUTTON_MOUSE             69
#define BUTTON_SCREENSHOT        70
#define NUM_BUTTONS              71
#define BUTTON_ANY               72
#define BUTTON_NONE              73

#define BUTTON_MASK              0x00ffffff
#define BUTTON_RAW_DEV_BIT_SHIFT 24
#define BUTTON_RAW_DEV_BIT_MASK  0x00000007
#define BUTTON_RELEASED          0x80000000
#define TOUCH_SONG               0x40000000
#define BUTTON_RAW_TOUCH         0x40000000
#define BUTTON_RAW               0x20000000
#define BUTTON_RAW_GPIO          0x10000000
#define BUTTON_RAW_DEV_BIT2      0x04000000
#define BUTTON_RAW_DEV_BIT1      0x02000000
#define BUTTON_RAW_DEV_BIT0      0x01000000
#define BUTTON_RAW_XTOUCH_MASK   0x00003fff /* 0..16383 touch range */
#define BUTTON_RAW_YTOUCH_MASK   0x00003fff /* 0..16383 touch range */
#define BUTTON_RAW_YTOUCH_SHIFT  14

#define SONG_TITLE_STRIP_POS     8
#define SONG_ENTRY_POS           16
#define SONG_POS_MASK            0xff

#define EVENT_PARAM_ID           0
#define EVENT_PARAM_VAL1         1
#define EVENT_PARAM_VAL2         2
#define EVENT_PARAM_PRESSED      3

#define UNDEFINED_HANDLER_NUM    0xffff

enum class input_device_state_e
{
  idle,
  waiting_for_elo_touch_btn_left,
  waiting_for_touch_abs_x,
  waiting_for_touch_abs_y,
  waiting_for_touch_release
};

struct input_device_t
{
  input_type_e type { input_type_e::None };
  // uint32_t instance  { 0 };
  string name {};
  string phys {};
  string event_path {};
  input_device_state_e state {input_device_state_e::idle};
  bool joystick_moved { false };
  uint32_t joystick_moved_code { 0 };
  int fd;
  uint32_t handler_num { UNDEFINED_HANDLER_NUM };
  uint32_t abs_x {}, abs_y {};
};

// struct raw_t
// {
  // mutex mtx;
  // bool enable { false };
  // condition_variable valid;
  // input_event_t event {};
  // string str;
  // volatile bool kbd_esc_pressed { false };
// };

class InputClass
{
public:
  // InputClass(bool i_config_buttons, bool i_test_buttons);
  InputClass(void);
  void Start(void);
  ~InputClass();
  // raw_t* WaitForRawButtonPress(void);
  // raw_t* CheckForRawButtonPress(void);
  uint32_t WaitForButtonPress(void);
  volatile uint32_t CheckForButtonPress(void);
  string RawKeyName(const uint32_t b);
  deque<uint32_t> queue { };
  std::mutex queue_mtx {};
  bool keyboard_installed {false};
  bool touch_installed {false};
  bool mouse_installed {false};
  bool touch_active {false};
  bool mouse_active {false};
  // bool joystick_installed {false};
  int32_t touch_offset_x { 0 };
  int32_t touch_offset_y { 0 };
  float mouse_pointer_x {0};
  float mouse_pointer_y {0};
  bool reversed_touch {false};
  static bool running;
  atomic<int32_t>status_event {};
  bool calibrating_touch {false};
  bool raw_mode {false};
  uint32_t touch_button_pressed { NUM_BUTTONS };
private:
  void openDevices(void);
  void scanGPIO(input_event_t &event);
  void scanDevice(input_device_t &device, input_event_t &event);
  uint32_t MouseXToSkinX(float val);
  uint32_t MouseYToSkinY(float val);
  uint32_t TouchXToSkinX(int32_t val);
  uint32_t TouchYToSkinY(int32_t val);
  vector <input_device_t> input_device {};
  // raw_t raw {};
  // bool config_buttons {false};
  // bool test_buttons {false};
  bool FindButton(const input_event_t &event);
  // void CalibrateTouch(void);
  void InputThread(void);
};
