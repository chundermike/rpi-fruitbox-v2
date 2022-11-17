#include "fruitbox.hpp"
// #include <termios.h>

#define ABS_CENTRE_LO     112
#define ABS_CENTRE_HI     144
#define ABS_LEFT_UP_HI    32
#define ABS_RIGHT_DOWN_LO 224

#define BLOCK_SIZE (4*1024)

constexpr char ButtonTestTitleStr[]             { "Button Test" };
constexpr char ButtonTestBodyStr[]              { "Press any input button ... " };
constexpr char ButtonTestMessageStr[]           { "... press keyboard <ESC> to finish ..." };
constexpr char ConfigureButtonsTitleStr[]       { "Configure Buttons" };
constexpr char ConfigureButtonsStartStr[]       { "... press any key to start ..." };
constexpr char ConfigureButtonsMessageStr[]     { "... press keyboard <ESC> to skip this button ..." };

bool InputClass::running { false };

InputClass::InputClass(void)
{
}

InputClass::~InputClass()
{
  for (auto &d : input_device)
  {
    if ( d.type == input_type_e::Key )
    {
      ioctl(d.fd, EVIOCGRAB, 0);
    }
  }
  // for (auto &d : input_device)
  // {
    // tcflush(d.fd, TCIFLUSH);
  // }
}

void InputClass::openDevices(void)
{
  string line {};
  string name {};
  string phys {};
  size_t pos {};
  ifstream devices_file {};
  int fd {};

  log_file << "Detecting input devices..." << endl;
  
  devices_file.open("/proc/bus/input/devices", ios::in);
  if (!devices_file.is_open()) return;

  while (getline(devices_file, line))
  {
    input_device_t device {};
    // search for our device...
    // istringstream ss { line };
    // find name and save for later after Handler field extracted...
    if ((pos = line.find("Name=")) != string::npos)
    {
      pos += 5; // skip over "Name="
      if (pos < line.size())
      {
        name = &line.at(pos);
      }
    }

    // find phys and save for later after Handler field extracted...
    if ((pos = line.find("Phys=")) != string::npos)
    {
      pos += 5; // skip over "Phys="
      if (pos < line.size())
      {
        phys = &line.at(pos);
        if ((pos = phys.find_first_of(FILE_SEPARATOR)) != string::npos)
        {
          phys.erase(pos, phys.back());
        }
      }
    }

    // check if we have a full-blown keyboard...
    if ((pos = line.find("EV=")) != string::npos)
    {
      stringstream ss;
      uint32_t ev;
      pos += 3; // skip over "EV="
      ss << std::hex << line.substr(pos);
      ss >> ev;
      if ((ev & 0x120013) == 0x120013)
      {
        keyboard_installed = true;
        log_file << "  ...keyboard detected" << endl;
      }
    }

    // Extract handler event number
    if (line.find("Handlers=") != string::npos)
    {
      if ((pos = line.find("event")) != string::npos)
      {
        string event_path {"/dev/input/"};

        event_path.append(&line.at(pos));
        if ((pos = event_path.find_first_not_of(' ')) != string::npos)
        {
          event_path.erase(0, pos);
        }
        if ((pos = event_path.find_first_of(' ')) != string::npos)
        {
          event_path.erase(pos, event_path.back());
        }
        device.name = name;
        device.event_path = event_path;
        name.clear();

        device.phys = phys;
        phys.clear();

        // we then try and open this device file...
        if ((device.fd = open(event_path.c_str(), O_RDONLY | O_RSYNC | O_NONBLOCK) ) == -1)
        {
          log_file << "  " << WARNING << "Couldn't Open ";
        }
        else
        {
          // check for keyboard device type...
          if ((pos = line.find("kbd")) != string::npos)
          {
            ioctl(device.fd, EVIOCGRAB, 1);
            device.type = input_type_e::Key;
            device.handler_num = 0;
          }

          // check for mouse device type (touchscreen or touchpad, or mouse) and extract number (if any)...
          // Touch devices support EV_ABS events
          // mice support EV_REL events
          else if ((pos = line.find("mouse")) != string::npos)
          {
            try { device.handler_num = static_cast<uint32_t>(stoi(line.substr(pos+5))); }
            catch (const std::invalid_argument &err) { }
            catch (const std::out_of_range &err) { }
            // cout << "openDevices mouse handler_num = " << device.handler_num << endl;

            // check for touch (EV_ABS) or mouse (EV_REL) support...
            {
              unsigned long evbit { 0 };
              ioctl(device.fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
              if (evbit & (1 << EV_ABS))
              {
                device.type = input_type_e::Touch;
                device.state = input_device_state_e::idle;
                touch_installed = true;
                log_file << "  ...touchscreen detected" << endl;
              }
              if (evbit & (1 << EV_REL))
              {
                device.type = input_type_e::Touch;
                device.state = input_device_state_e::idle;
                mouse_installed = true;
                log_file << "  ...mouse detected" << endl;
              }
            }
          }

          // check for joystick device type and extract number (if any)...
          else if ((pos = line.find("js")) != string::npos)
          {
            device.type = input_type_e::JoyStick;
            try { device.handler_num = static_cast<uint32_t>(stoi(line.substr(pos+2))); }
            catch (const std::invalid_argument &err) { }
            catch (const std::out_of_range &err) { }
            // cout << "openDevices joystick handler_num = " << device.handler_num << endl;
          }

          // now check out device.name against all previous device names found (input_device array)
          // ...if any names match then we assign it a unique instance number (the last one in the array)
          // for (auto &d : input_device)
          // {
            // cout << "Comparing " << d.name << " with " << device.name << endl;
            // if (d.name == device.name) // && NEED TO COMPARE SOMETHING ELSE TOO - Handlers= AND/OR KEY= maybe?
            // {
              // device.instance = d.instance + 1;
            // }
          // }
          
          // save the opened device to the vector list...
          log_file << "  Opened ";
          input_device.push_back(device);
        }
        log_file << device.name << " (" << device.event_path << ")" << endl;
        // cout << device.name << " (" << device.event_path << ") " << device.handler_num << endl;
      }
    }
  }
  devices_file.close();

  if (Config->touch_screen->enabled)
  {
    if (touch_installed)
    {
      touch_active = true;
    }
    else
    {
      log_file << WARNING << "Touchscreen Enable requested but no touch screen detected" << endl;
    }
  }
  
  if (Config->mouse->enabled)
  {
    if (mouse_installed)
    {
      mouse_active = true;
      Config->mouse->init(StatusEvent_None);
    }
    else
    {
      log_file << WARNING << "Mouse Enable requested but no mouse detected" << endl;
    }
  }

  #ifdef _RPI
  // now add gpio to device vector...
  input_device_t device {};
  device.type = input_type_e::GPIO;
  device.name = "GPIO";
  device.event_path = "";
  device.fd = 0;
  input_device.push_back(device);
  log_file << "  Opened GPIO" << endl;
  #endif


  // If we have multiple joysticks of the same type, the joystick buttons will map to the same Key codes,
  // so we must uniquely identify them.  This already happens automatically for Joysticks, through the js<x> handler field,
  // but joystick buttons map to kbd codes.
  // To overcome this, we now try and associate joystick buttons with the joystick device, by scanning all the devices we have...
  // Each time we find a device with a handler_num != -1, we try and find a matching phys string with another device.
  // If we find one, this is the device which holds the joystick buttons, so we change its handler_num to be the same
  for (auto &d : input_device)
  {
    if (d.phys.size() == 0) continue;
    if (d.handler_num == UNDEFINED_HANDLER_NUM) continue;
    for (auto &d2 : input_device)
    {
      if (d2.phys.size() == 0) continue;
      if ((d2.handler_num == UNDEFINED_HANDLER_NUM) && (d.phys == d2.phys)) // d2 is not allocated a joystick number (so it must be a joystick kbd) d1 and d2 are the same device pair
      {
        d2.handler_num = d.handler_num;
        // if (d.type == input_type_e::JoyStick) // check because it could be a keyboard/keyboard pair
        // {
          // d2.type = input_type_e::JoyButton;
        // }
        log_file << "  ...paired " << d2.event_path << " with " << d.event_path << endl;
      }
    }
  }

  log_file << endl;
}

void InputClass::Start(void)
{
  // struct termios raw;
  // tcgetattr(STDIN_FILENO, &raw);
  // raw.c_lflag &= ~(ECHO | ECHOE);
  // tcsetattr(STDIN_FILENO, TCSANOW, &raw);

  openDevices();

  // start the input thread which reads input devices and processes button presses using FindButton()
  // FindButton() either places button matches on the Input button queue, or processes the input events
  // directly in test_buttons or config_buttons mode(s).

  thread InputThread { &InputClass::InputThread, this };
  InputThread.detach();

  InputClass::running = true;
}

/*
raw_t* InputClass::WaitForRawButtonPress(void)
// don't return until *any* input event has occurred (i.e. not just fruitbox-specific button codes)
{
  raw_t *r;
  do
  {
    r = CheckForRawButtonPress();
  } while (r->event.type == input_type_e::None);

  return r;
}

raw_t* InputClass::CheckForRawButtonPress(void)
// check for *any* input event has occurred (i.e. not just fruitbox-specific button codes)
{
  unique_lock<mutex> raw_guard(raw.mtx);
  raw.enable = true;
  if (raw.valid.wait_for(raw_guard, chrono::milliseconds(1000)) == cv_status::timeout)
  {
    raw.event.type = input_type_e::None;
  }
  raw.enable = false;
  raw_guard.unlock();
  return &raw;
}
*/
uint32_t InputClass::WaitForButtonPress(void)
// wait until a recognisable button has been pressed (or released), and then return it's value
{
  volatile uint32_t button;
  
  do
  {
    button = CheckForButtonPress();
    this_thread::sleep_for(chrono::milliseconds(1));
  } while (button == BUTTON_NONE);

  return button;
}

volatile uint32_t InputClass::CheckForButtonPress(void)
// check if a recognisable button has been pressed or released, and if so return it's value (and RELEASE flag if released), else return BUTTON_NONE
{
  // cout << "CheckForButtonPress " << endl;
  if (queue.size())
  {
    queue_mtx.lock();
    uint32_t event_code = queue.front();
    queue.pop_front();
    queue_mtx.unlock();
    return event_code;
  }
  return BUTTON_NONE;
}

void InputClass::scanGPIO(input_event_t &event)
{
  event.type = input_type_e::None;
  for (uint32_t pin = 0; pin < NUM_GPIO; ++pin)
  {
    gpio_input_state_e pin_state { Gpio->DebounceInput(pin) };
    if (pin_state != gpio_input_state_e::NoChange)
    {
      event.type = input_type_e::GPIO;
      event.param[EVENT_PARAM_ID] = 0;
      event.param[EVENT_PARAM_VAL1] = pin; // GPIO pin number
      event.param[EVENT_PARAM_PRESSED] = static_cast<int32_t>(pin_state); // gpio_input_state_e::NotPressed = 0, gpio_input_state_e::Pressed = 1
      FindButton(event);
    }
  }
}

uint32_t InputClass::MouseXToSkinX(float val)
// convert display co-ordinates to skin co-ordinates (for mouse)
{
  if (DialogBaseClass::touch_menu_active) return static_cast<uint32_t>(val); // mouse on menu (i.e. display)
  
  return static_cast<uint32_t>(Display->scale_display_to_skin_x * val); // mouse on skin
}

uint32_t InputClass::MouseYToSkinY(float val)
{  
  if (DialogBaseClass::touch_menu_active) return static_cast<uint32_t>(val); // mouse on menu (i.e. display)
  
  return static_cast<uint32_t>(Display->scale_display_to_skin_y * val); // mouse on skin
}

uint32_t InputClass::TouchXToSkinX(int32_t val)
// convert touchscreen co-ordinates to skin co-ordinates (for touchscreen control)
{
  if (calibrating_touch) return static_cast<uint32_t>(val); // unprocessed co-ordinates needed during calibration

  // we transform the touch co-ordinates by first adding the user defined offsets, and then scaling by the user defined scale...
  int32_t value { reversed_touch ? static_cast<int32_t>(ConfigBaseClass::touch_br.x + ConfigBaseClass::touch_tl.x - val) : static_cast<int32_t>(val) };

  if (DialogBaseClass::touch_menu_active)
  {
    return static_cast<uint32_t>(Display->scale_touch_to_display_x * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_x))); // touch on menu
  }
  else
  {  
    return static_cast<uint32_t>(Display->scale_touch_to_skin_x * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_x))); // touch on skin
  }
}

uint32_t InputClass::TouchYToSkinY(int32_t val)
{
  if (calibrating_touch) return static_cast<uint32_t>(val); // unprocessed co-ordinate needed during calibration

  // we transform the touch co-ordinates by first adding the user defined offsets, and then scaling by the user defined scale...
  int32_t value { reversed_touch ? static_cast<int32_t>(ConfigBaseClass::touch_br.y + ConfigBaseClass::touch_tl.y - val) : static_cast<int32_t>(val) };

  if (DialogBaseClass::touch_menu_active)
  {
    return static_cast<uint32_t>(Display->scale_touch_to_display_y * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_y))); // touch on menu
  }
  else
  {  
    return static_cast<uint32_t>(Display->scale_touch_to_skin_y * static_cast<double>(static_cast<uint32_t>(static_cast<int32_t>(value) - touch_offset_y))); // touch on skin
  }
}

void InputClass::scanDevice(input_device_t &device, input_event_t &event)
{
  struct input_event ev[64];
  
  int rb {read(device.fd, ev, sizeof(struct input_event)*64)};

  if (rb != -1) // data available
  {
    for (auto i = 0;  i < (rb / sizeof(struct input_event)); ++i)
    {
      event.type = input_type_e::None;

      switch (device.state)
      {
        case input_device_state_e::idle :
          if (ev[i].type == EV_KEY)
          {
            if (ev[i].code == BTN_TOUCH)
            {
              event.param[EVENT_PARAM_PRESSED] = ev[i].value;
              if (ev[i].value == 1) // pressed (touched)
              {
                device.state = input_device_state_e::waiting_for_touch_abs_x;
              }
            }
            else // keyboard or joystick button press/release
            {
              if ((ev[i].value == 0) || (ev[i].value == 1)) // released or pressed (i.e. not autorepeat)
              {
                if ((ev[i].code == Config->buttons->button[BUTTON_MOUSE].param[EVENT_PARAM_VAL1]) && mouse_active && !raw_mode) // left mouse button
                {
                  status_event |= EventToTimerThread_MouseMove; // ensure mouse is visible
                // cout << "Mouse " << mouse_pointer_x << " " << mouse_pointer_y << endl ;
                // cout << "Scaled " << MouseXToSkinX(mouse_pointer_x) << " " << MouseYToSkinY(mouse_pointer_y) << endl ;
                  event.type = input_type_e::Touch;
                  // cout << "MOUSE" << endl;
                  event.param[EVENT_PARAM_VAL1] = MouseXToSkinX(mouse_pointer_x);
                  event.param[EVENT_PARAM_VAL2] = MouseYToSkinY(mouse_pointer_y);
                  event.param[EVENT_PARAM_PRESSED] = ev[i].value;
                  if (ev[i].value == 0) // released
                  {
                    Config->skin_touch_song->title_strip_pressed_draw_en = false;
                  }
                }
                else
                {
                  event.type = input_type_e::Key;
                  // cout << "KEY device.handler_num = " << device.handler_num << endl;
                  // event.param[EVENT_PARAM_ID] = device.instance;
                  event.param[EVENT_PARAM_ID] = device.handler_num;
                  event.param[EVENT_PARAM_VAL1] = ev[i].code;
                  event.param[EVENT_PARAM_VAL2] = 0;
                  event.param[EVENT_PARAM_PRESSED] = ev[i].value;
                }
                // if (device.type == input_type_e::Key)
                // {
                  // event.type = input_type_e::Key;
                // }
                // else if (device.type == input_type_e::JoyStick)
                // {
                  // event.type = input_type_e::JoyButton;
                  // event.param[EVENT_PARAM_ID] = device.handler_num;
                // }

              }
            }
          }
          else if (ev[i].type == EV_ABS) // (non-btn_touch touch) or analogue (joy)stick movement event...
          {
            if (device.type == input_type_e::Touch) // non-btn_touch (i.e. ELO) style touch device...
            {
              if (ev[i].code == ABS_X)
              {
                event.param[EVENT_PARAM_VAL1] = TouchXToSkinX(ev[i].value);
                // cout << "Raw X " << ev[i].value << " " << event.param[EVENT_PARAM_VAL1] << endl;
              }
              else if (ev[i].code == ABS_Y)
              {
                event.param[EVENT_PARAM_VAL2] = TouchYToSkinY(ev[i].value);
                // cout << "Raw Y " << ev[i].value << " " << event.param[EVENT_PARAM_VAL2] << endl;
                // cout << "debug1 " << event.param[EVENT_PARAM_VAL2] << endl;
                device.state = input_device_state_e::waiting_for_elo_touch_btn_left;
              }
/*              else if (ev[i].code == ABS_MISC)
              {
                event.type = input_type_e::Touch;
                event.param[EVENT_PARAM_ID] = 0;
                if (ev[i].value) // pressed
                {
                  event.param[EVENT_PARAM_PRESSED] = 1;
                  device.abs_x = event.param[EVENT_PARAM_VAL1]; // save for released event (as they may change)
                  device.abs_y = event.param[EVENT_PARAM_VAL2];
                  cout << "debug1 " << device.abs_x << " " << device.abs_y << endl;
                }
                else // released
                {
                  event.param[EVENT_PARAM_PRESSED] = 0;
                  cout << "debug2 " << device.abs_x << " " << device.abs_y << endl;

                  event.param[EVENT_PARAM_VAL1] = device.abs_x;
                  event.param[EVENT_PARAM_VAL2] = device.abs_y;
                  // if (Config->skin_general->select_mode == select_mode_e::TouchSong)
                  // {
                    Config->skin_touch_song->title_strip_pressed_draw_en = false;
                  // }
                }
              }
*/
            }
            else // joystick
            {
              bool is_stick { false };

              if (ev[i].code >= ABS_X && ev[i].code <= ABS_RZ) is_stick = true;
              else if (ev[i].code >= ABS_HAT0X && ev[i].code <= ABS_HAT3Y) is_stick = true;

              if (!is_stick) break;
// cout << "is_stick ";
              // get the min and max values
              int abs[6] = {0};
              int32_t abs_min {};
              int32_t abs_max {};
              int32_t abs_mid {};

              ioctl(device.fd, EVIOCGABS(ev[i].code), abs);

              abs_mid = abs[0];
              abs_min = abs[1];
              abs_max = abs[2];

              if (device.joystick_moved == false)
              {
                if (ev[i].value == abs_max)
                {
                  // event.type = input_type_e::Key;
                  // cout << "JOY ABS_MAX device.handler_num = " << device.handler_num << endl;
                  event.type = input_type_e::JoyStick;
                  event.param[EVENT_PARAM_ID] = device.handler_num;
                  event.param[EVENT_PARAM_VAL1] = ev[i].code;
                  event.param[EVENT_PARAM_VAL2] = input_event_labels::AbsHiOffset - input_event_labels::AbsLoOffset; // Label offset for HI
                  event.param[EVENT_PARAM_PRESSED] = 1;
                  device.joystick_moved_code = ev[i].code;
                  device.joystick_moved = true;
                  // cout << hex << "abs_max " << event.param[EVENT_PARAM_ID] << " " << event.param[EVENT_PARAM_VAL1] << " " << event.param[EVENT_PARAM_VAL2] << endl;
                }

                else if (ev[i].value == abs_min)
                {
                  // cout << "JOY ABS_MIN device.handler_num = " << device.handler_num << endl;
                  event.type = input_type_e::JoyStick;
                  // event.type = input_type_e::Key;
                  event.param[EVENT_PARAM_ID] = device.handler_num;
                  event.param[EVENT_PARAM_VAL1] = ev[i].code;
                  event.param[EVENT_PARAM_VAL2] = 0; // (No) offset for LO
                  event.param[EVENT_PARAM_PRESSED] = 1;
                  device.joystick_moved_code = ev[i].code;
                  device.joystick_moved = true;
                  // cout << hex << "abs_min " << event.param[EVENT_PARAM_ID] << " " << event.param[EVENT_PARAM_VAL1] << " " << event.param[EVENT_PARAM_VAL2] << endl;
                }

              }
              else
              {
                if (ev[i].value == abs_mid && ev[i].code == device.joystick_moved_code)
                {
                  // cout << "JOY device.handler_num = " << device.handler_num << endl;
                  // event.type = input_type_e::Key;
                  event.type = input_type_e::JoyStick;
                  event.param[EVENT_PARAM_ID] = device.handler_num;
                  event.param[EVENT_PARAM_PRESSED] = 0;
                  device.joystick_moved = false;
                }
              }
            }
          }
          else if (ev[i].type == EV_REL) // mouse movement event...
          {
            if (ev[i].code == REL_X)
            {
              status_event |= EventToTimerThread_MouseMove;
              // cout << "ev[i].value, mouse_pointer_x = " << ev[i].value << ", " << mouse_pointer_x << ", " << Config->mouse->sensitivity << endl;
              mouse_pointer_x += static_cast<float>(ev[i].value) * Config->mouse->sensitivity;
              if (mouse_pointer_x < 0.0)
              {
                mouse_pointer_x = 0.0;
              }
              else if (static_cast<uint32_t>(mouse_pointer_x) > Display->display_size.width)
              {
                mouse_pointer_x = static_cast<float>(Display->display_size.width);
              }
              Config->mouse->position.x.val = static_cast<int32_t>(mouse_pointer_x) - Config->mouse->offset.x; // position for Config->mouse->Draw()
              
            }
            else if (ev[i].code == REL_Y)
            {
              status_event |= EventToTimerThread_MouseMove;
              // cout << "ev[i].value, mouse_pointer_y = " << ev[i].value << ", " << mouse_pointer_y << ", " << Config->mouse->sensitivity << endl;
              mouse_pointer_y += static_cast<float>(ev[i].value) * Config->mouse->sensitivity; // position for Config->mouse->Draw()
              if (mouse_pointer_y < 0.0)
              {
                mouse_pointer_y = 0.0;
              }
              else if (static_cast<uint32_t>(mouse_pointer_y) > Display->display_size.height)
              {
                mouse_pointer_y = static_cast<float>(Display->display_size.height);
              }
              Config->mouse->position.y.val = static_cast<int32_t>(mouse_pointer_y) - Config->mouse->offset.y;
            }
          }
          break;

        // states for detecting BTN_LEFT for ELO touchscreen after ABS_X and ABS_Y...
        case input_device_state_e::waiting_for_elo_touch_btn_left :
          if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_LEFT))
          {
            event.type = input_type_e::Touch;
            event.param[EVENT_PARAM_ID] = 0;
            if (ev[i].value) // pressed
            {
              event.param[EVENT_PARAM_PRESSED] = 1;
              device.abs_x = event.param[EVENT_PARAM_VAL1]; // save for released event (as they may change)
              device.abs_y = event.param[EVENT_PARAM_VAL2];
              // cout << "Touch at (" << device.abs_x << ", " << device.abs_y << ")" << endl;
            }
            else // released
            {
              event.param[EVENT_PARAM_PRESSED] = 0;
              // cout << "debug2 " << device.abs_x << " " << device.abs_y << endl;

              event.param[EVENT_PARAM_VAL1] = device.abs_x;
              event.param[EVENT_PARAM_VAL2] = device.abs_y;
              // if (Config->skin_general->select_mode == select_mode_e::TouchSong)
              // {
              Config->skin_touch_song->title_strip_pressed_draw_en = false;
              // }
            }
            device.state = input_device_state_e::idle;
          }
          break;

        // states for detecting ABS_X and ABS_Y immediately following a BTN_TOUCH (touchscreen) event...
        case input_device_state_e::waiting_for_touch_abs_x :
          if ((ev[i].type == EV_ABS) && (ev[i].code == ABS_X))
          {
            device.abs_x = event.param[EVENT_PARAM_VAL1] = TouchXToSkinX(ev[i].value);
            // cout << "debug3 " << device.abs_x << " " << device.abs_y << endl;
            device.state = input_device_state_e::waiting_for_touch_abs_y;
          }
          break;

        case input_device_state_e::waiting_for_touch_abs_y :
          if ((ev[i].type == EV_ABS) && (ev[i].code == ABS_Y))
          {
            device.abs_y = event.param[EVENT_PARAM_VAL2] = TouchYToSkinY(ev[i].value);
            // cout << "debug4 " << device.abs_x << " " << device.abs_y << endl;
            event.param[EVENT_PARAM_ID] = 0;
            event.param[EVENT_PARAM_PRESSED] = 1; // pressed
            event.type = input_type_e::Touch;
            device.state = input_device_state_e::waiting_for_touch_release;
          }
          break;

        case input_device_state_e::waiting_for_touch_release :
          if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 0))
          {
            device.state = input_device_state_e::idle;
          }
          break;

        default :
          device.state = input_device_state_e::idle;
          break;
      }

      // we check for button release outside of state machine so we can use it to resync the state machine if x/y not received after button press...
      if ((ev[i].type == EV_KEY) && (ev[i].code == BTN_TOUCH) && (ev[i].value == 0))
      {
        event.type = input_type_e::Touch;
        event.param[EVENT_PARAM_ID] = 0;
        event.param[EVENT_PARAM_PRESSED] = 0; // released
        event.param[EVENT_PARAM_VAL1] = device.abs_x;
        event.param[EVENT_PARAM_VAL2] = device.abs_y;
        Config->skin_touch_song->title_strip_pressed_draw_en = false;
        device.state = input_device_state_e::idle;
      }

      if (event.type != input_type_e::None)
      {
        if (FindButton(event) == false)
        {
          // no button match found, so if the event is a touch, and we are in TouchSong selection mode (and not in a menu),
          // we check to see if the touch is inside any of the song title areas (which include cfg offset and size)...
          // (Note don't bother checking if the playqueue is full)
          if ((PlayQueue->full == false) && (Config->skin_general->select_mode == select_mode_e::TouchSong) && (event.type == input_type_e::Touch) && (DialogBaseClass::touch_menu_active == false))
          {
            uint32_t song_entry {};
            uint32_t song_title_strip {};
            uint32_t sw {Config->skin_touch_song->size.x.val};
            uint32_t sh {Config->skin_touch_song->size.y.val};
            bool done { false };
            for (song_title_strip=0; song_title_strip < Config->skin_touch_song->title_strip_position.size(); ++song_title_strip)
            {
              for (song_entry=0; song_entry < Config->skin_touch_song->title_strip_position[song_title_strip].size(); ++song_entry)
              {
                uint32_t sx {Config->skin_touch_song->title_strip_position[song_title_strip][song_entry].x};
                uint32_t sy {Config->skin_touch_song->title_strip_position[song_title_strip][song_entry].y};
                if (event.param[EVENT_PARAM_VAL1] < sx) continue;       // touch x < song title region x
                if (event.param[EVENT_PARAM_VAL2] < sy) continue;       // touch y < song title region y
                if (event.param[EVENT_PARAM_VAL1] >= (sx+sw)) continue; // touch x >= song title region (x+w)
                if (event.param[EVENT_PARAM_VAL2] >= (sy+sh)) continue; // touch y >= song title region (y+h)
                // if we get here then the touch is inside the song title touch area...
                if (event.param[EVENT_PARAM_PRESSED] == 1)
                {
                  Config->skin_touch_song->position.x.val = sx;
                  Config->skin_touch_song->position.y.val = sy;
                  Config->skin_touch_song->title_strip_pressed_draw_en = true;
                  uint32_t button { TOUCH_SONG | (song_entry << SONG_ENTRY_POS) | (song_title_strip << SONG_TITLE_STRIP_POS) };
                  queue_mtx.lock();
                  queue.push_back(button); // button code
                  queue.push_back(BUTTON_SELECT); // select song immediately
                  queue_mtx.unlock();
                }
                done = true;
                break;
              }
              if (done) break;
            }
          }
        }
      }
    }
  }
}

void InputClass::InputThread(void)
{
  input_event_t event;
  while (Engine_finished == false)
  {
    for (auto &d : input_device)
    {
      if (d.type == input_type_e::GPIO)
      {
        scanGPIO(event); // scan and debounce GPIO inputs
      }
      else
      {
        scanDevice(d, event);
      }
    }
    this_thread::sleep_for(chrono::milliseconds(10)); // no point in scanning for buttons more than 100 times a second!
  }
  InputThread_finished = true;
}

string InputClass::RawKeyName(const uint32_t b)
{
  stringstream ss {};
  uint32_t v { b & BUTTON_MASK };
  uint32_t dev { (b >> BUTTON_RAW_DEV_BIT_SHIFT) & BUTTON_RAW_DEV_BIT_MASK };

  if (b & BUTTON_RAW_GPIO)
  {
    ss << ButtonTypeGPIOStr << v;
  }
  else
  {
    ss << input_event_labels::input_event_label.at(v);
    if (dev)
    {
      ss << " " << ButtonDeviceStr << dev << ButtonDeviceStrPost;
      // cout <<   "RawKeyName : " << input_event_labels::input_event_label.at(v) << " dev = " << dev << endl;
    }
  }

  return ss.str();
}

bool InputClass::FindButton(const input_event_t &event)
{
  if (raw_mode) // capture the raw button type and values rather than try and match it...
  {             // only check for key, btn and gpio. touch is ignored as these are set via skin [touch areas]
    // if (event.param[EVENT_PARAM_PRESSED] == 1) // only show pressed events (rather than released or repeated)
    // {
    volatile bool pressed { false };
    uint32_t b { BUTTON_RAW };
    auto v { event.param[EVENT_PARAM_VAL1] };
    if (event.param[EVENT_PARAM_PRESSED] == 0)
    {
      b |= BUTTON_RELEASED;
    }

    switch (event.type)
    {
      case input_type_e::Key :
        if (v < input_event_labels::NumInputKeys) // key code
        {
          b |= ((event.param[EVENT_PARAM_ID] & BUTTON_RAW_DEV_BIT_MASK) << BUTTON_RAW_DEV_BIT_SHIFT) | v;
        }
        pressed = true;
        break;

      case input_type_e::JoyStick :
        v += input_event_labels::AbsLoOffset + event.param[EVENT_PARAM_VAL2];
        if (v < input_event_labels::NumInputKeys) // label index
        {
          b |= ((event.param[EVENT_PARAM_ID] & BUTTON_RAW_DEV_BIT_MASK) << BUTTON_RAW_DEV_BIT_SHIFT) | v;
        }        
        pressed = true;
        break;

      case input_type_e::Touch :
        // if (calibrating_touch) // only register touch inputs if calibrating screen, not when detecting button presses
        // {
          b |= BUTTON_RAW_TOUCH;
          b |= event.param[EVENT_PARAM_VAL1] & BUTTON_RAW_XTOUCH_MASK;
          b |= (event.param[EVENT_PARAM_VAL2] & BUTTON_RAW_YTOUCH_MASK) << BUTTON_RAW_YTOUCH_SHIFT;
          pressed = true;
        // }
        break;

      case input_type_e::GPIO :
        b |= BUTTON_RAW_GPIO | v; // GPIO flag and GPIO pin number
        pressed = true;
        break;
    }

    if (pressed)
    {
      queue_mtx.lock();
      queue.push_back(b);
      queue_mtx.unlock();
      return true;
    }
  }
  else // try and find a user button that matches this event...
  {
    uint32_t b;
    bool done { false };
    touch_area_t *area;

    for (b = 0; b < NUM_BUTTONS; ++b)
    {
      if (Config->buttons->button[b].type == event.type)
      {
        switch (event.type)
        {
          case input_type_e::Touch : // need to check touch is within the size of the button area... (touch co-ordinates here are relative to skin)
            if (DialogBaseClass::touch_menu_active)
            {
              area = &Config->buttons->button[b].menu_touch_area;
            }
            else
            {
              area = &Config->buttons->button[b].skin_touch_area;
            }

            if (event.param[EVENT_PARAM_VAL1] < area->x) continue;       // touch x < button x
            if (event.param[EVENT_PARAM_VAL2] < area->y) continue;       // touch y < button y
            if (event.param[EVENT_PARAM_VAL1] >= (area->x + area->w)) continue; // touch x >= button (x+w)
            if (event.param[EVENT_PARAM_VAL2] >= (area->y + area->h)) continue; // touch y >= button (y+h)
            done = true; // touch inside button area :)
            break;

          case input_type_e::Key :
            if ((Config->buttons->button[b].param[EVENT_PARAM_ID] == event.param[EVENT_PARAM_ID]) &&
                (Config->buttons->button[b].param[EVENT_PARAM_VAL1] == event.param[EVENT_PARAM_VAL1]))
            {
              done = true;
            }
            break;

          case input_type_e::JoyStick :
            // cout << hex << "FindButton ";
            // cout << hex << Config->buttons->button[b].param[EVENT_PARAM_ID] << " ";
            // cout << hex << event.param[EVENT_PARAM_ID] << " ";
            // cout << hex << Config->buttons->button[b].param[EVENT_PARAM_VAL1] << " ";
            // cout << hex << event.param[EVENT_PARAM_VAL1] << " ";
            // cout << hex << Config->buttons->button[b].param[EVENT_PARAM_VAL2] << " ";
            // cout << hex << event.param[EVENT_PARAM_VAL2] << endl;
            
            if ((Config->buttons->button[b].param[EVENT_PARAM_ID] == event.param[EVENT_PARAM_ID]) && // device ID 
                (Config->buttons->button[b].param[EVENT_PARAM_VAL1] == event.param[EVENT_PARAM_VAL1]) && // event code
                (Config->buttons->button[b].param[EVENT_PARAM_VAL2] == event.param[EVENT_PARAM_VAL2])) // hi or lo
            {
              done = true;
            }
            break;

          case input_type_e::GPIO :
          // cout << "GPIO " << Config->buttons->button[b].param[EVENT_PARAM_VAL1] << " " << event.param[EVENT_PARAM_VAL1] << endl;
            if (Config->buttons->button[b].param[EVENT_PARAM_VAL1] == event.param[EVENT_PARAM_VAL1])
            {
              done = true;
            }
            break;

        }
      }
      if (done) break;
    }

    touch_button_pressed = b;

    if (b < NUM_BUTTONS) // recognised button has been pressed or released
    {
      if (event.param[EVENT_PARAM_PRESSED] == 0)
      {
        touch_button_pressed = NUM_BUTTONS; // released button
        b |= BUTTON_RELEASED;
      }
      queue_mtx.lock();
      queue.push_back(b);
      queue_mtx.unlock();
      return true;
    }
  }
  return false;
}
