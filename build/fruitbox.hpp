#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <sys/mman.h>
#include <signal.h>
#include <ctime>
#include <cmath>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <iomanip>
#include <functional>
#include <condition_variable>
// #include <bitset>
#include <poll.h>
#include <linux/input.h>
// #ifdef _RPI
// #include "bcm_host.h"
// #endif

#ifdef _RPI
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  #include "bcm_host.h"
  #pragma GCC diagnostic pop
#endif

#include <mpg123.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>

// extern uint32_t bitmaps_created;
extern std::ofstream log_file;
extern int display_refresh_rate;
extern double spectrum_analyser_band[2][32]; // defined in libmpg123/equalizer.c
extern uint32_t refresh_spectrum_analyser_band; // defined in libmpg123/equalizer.c
extern bool command_line_music_path;
extern bool ini_file_music_path;
extern uint32_t PiVersion;

#include "fruitbox_types.hpp"
#include "fast_random.hpp"
#include "input_event_labels.hpp"
#include "gpio.hpp"
#include "input.hpp"
#include "status_events.hpp"
#include "config_base.hpp"
#include "display_base.hpp"
#include "playqueue.hpp"
#include "engine.hpp"
#include "title_strips.hpp"
#include "menus.hpp"
#include "dialog.hpp"
#include "display.hpp"
#include "bitmap.hpp"
#include "mouse.hpp"
#include "joystick.hpp"
#include "touch_areas.hpp"
#include "spectrum_analyser.hpp"
#include "status.hpp"
#include "audio.hpp"
#include "config.hpp"
#include "database.hpp"
#include "userguide.hpp"

// A note of version number... x.yz :
// x = major release
// y = minor release
// z = beta/bug fix release
// ONLY USE NUMERIC REPRESENTATIONS (E.G. NOT 2.00BETA)

#ifndef _RPI4
  #define FRUITBOX_BUILD "Pi(0-3) 32-bit Lite (non-Desktop)"
#else
  #ifdef _RPI4_32
    #define FRUITBOX_BUILD "Pi4 32-bit Desktop"
  #else
    #define FRUITBOX_BUILD "Pi4 64-bit Desktop"
  #endif
#endif
#define FRUITBOX_VERSION_NUMBER               "2.04"
#define FRUITBOX_VERSION                      "fruitbox version " FRUITBOX_VERSION_NUMBER
#define FRUITBOX_AUTHOR                       "Mike Kingsley"
#define FRUITBOX_DESCRIPTION                  FRUITBOX_VERSION " (" FRUITBOX_BUILD ", " __DATE__ ", " __TIME__ ") by " FRUITBOX_AUTHOR
#define FRUITBOX_SUMMARY                      "A customisable MP3/OGV Jukebox for the Raspberry Pi."
#define FRUITBOX_DONATE_LINE1                 "To encourage future development, please consider making"
#define FRUITBOX_DONATE_LINE2                 "a donation to the author at https://paypal.me/rpifruitbox"
#define FRUITBOX_NON_COMMERCIAL               "Free for non-commercial use"

void error(const char *fmt, ...);
void error(vector<string> message);

extern status_t status;
extern bool Engine_finished, InputThread_finished, TimerThread_finished, GetCURLDataThread_finished, PlaySongThread_finished, LoadArtworkThread_finished;
extern bool debug_song_nums;
extern bool no_db_refresh;
extern bool force_db_refresh;
extern ALLEGRO_DISPLAY *display;
extern string save_playlist_filename;
extern string load_playlist_filename;
extern ConfigClass *Config;
extern AudioClass *Audio;
extern InputClass *Input;
extern DatabaseClass *Database;
extern PlayQueueClass *PlayQueue;
extern EngineClass *Engine;
extern DisplayClass *Display;
extern DialogSelectableListClass *MainMenu;
extern DialogSelectableListClass *SearchMenu;
extern DialogProgressBarClass *ProgressBar;
extern sound_t camera_shutter_click;

extern GpioClass *Gpio;
