#pragma once

#include "fruitbox.hpp"

using namespace std;

class DisplayClass {
public:
  DisplayClass(uint32_t width, uint32_t height);
  ~DisplayClass();
  void DrawJukebox(void);
  int32_t RenderText(ALLEGRO_BITMAP * &bitmap, const text_t text, const string &str);
  void DrawText(ALLEGRO_BITMAP *text_bitmap, ALLEGRO_BITMAP *target_bitmap, const text_t text, const int32_t align_width, const int32_t x, const int32_t y);
  void Text(ALLEGRO_BITMAP *bitmap, const text_t text, const int32_t align_width, const int32_t x, const int32_t y, const string &str);
  ALLEGRO_DISPLAY_MODE display_size {};
  ALLEGRO_BITMAP *fruitbox_logo_bm {};
  ALLEGRO_BITMAP *jukebox {};
  ALLEGRO_DISPLAY *display {};
  bool active { false };
  static bool jukebox_drawn;
  float scale_display_to_skin_x { 1.0 };
  float scale_display_to_skin_y { 1.0 };
  float scale_touch_to_display_x { 1.0 };
  float scale_touch_to_display_y { 1.0 };
  float scale_touch_to_skin_x { 1.0 };
  float scale_touch_to_skin_y { 1.0 };
private:
  ALLEGRO_BITMAP *text_bm {};
  // void CapitaliseAndQuote(string &str, const bool cap_en, const bool quo_en);
};

