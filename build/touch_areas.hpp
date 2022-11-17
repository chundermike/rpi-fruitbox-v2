#pragma once

#include "fruitbox.hpp"

using namespace std;

class TouchSongDisplayClass : public JoystickDisplayClass {
public:

  TouchSongDisplayClass() { supports_dynamics = false; }  

  void cfgRead(string line);

  void DescribeParams(ofstream &strm, const char *indent) {
    DescribeParam(strm, indent, cfgKeyword_Bitmap,   cfgKeywordDesc_TouchSongBitmap, false);
    DescribeParam(strm, indent, cfgKeyword_Offset,   cfgKeywordDesc_TouchSongOffset, false);
    DescribeParam(strm, indent, cfgKeyword_Size,     cfgKeywordDesc_JoystickSize, false);
    DescribeParam(strm, indent, cfgKeyword_Angle,    cfgKeywordDesc_Angle, false);
    DescribeParam(strm, indent, cfgKeyword_HorzFlip, cfgKeywordDesc_HorzFlip, false);
    DescribeParam(strm, indent, cfgKeyword_VertFlip, cfgKeywordDesc_VertFlip, false);
    DescribeParam(strm, indent, cfgKeyword_Tint,     cfgKeywordDesc_Tint, false);
  }

  TouchSongDisplayClass* clone() const { return new TouchSongDisplayClass(*this); }
  // TouchSongDisplayClass* clone() { return this; } // this class only supports one instance

  // we don't want to inherit the JoystickDisplayClass methods as they are specific to joysticks
  void init(const dynamics2_t sze, const uint32_t emsk);
  void draw(void);
  // void renew(void) {}; // do nothing as this class only supports one instance

  bool enabled { false };
  bool title_strip_pressed_draw_en { false };
  // bitmap_t title_strip_bm {};
  // uints2_t title_strip_size {};
  // uints2_t title_strip_pos {};
private:
  string bitmap_name {};
};

class TouchButtonsDisplayClass : public JoystickDisplayClass {
public:

  TouchButtonsDisplayClass() { supports_dynamics = false; }  

  void cfgRead(string line);

  void DescribeParams(ofstream &strm, const char *indent) {
    for (auto b = 0; b < NUM_BUTTONS; ++b)
    {
      DescribeParam(strm, indent, default_button[b].name, cfgKeyword_ButtonTouchArea, false);
    }
  }

  TouchButtonsDisplayClass* clone() const { return new TouchButtonsDisplayClass(*this); }
  // TouchButtonsDisplayClass* clone() { return this; } // this class only supports one instance

  // we don't want to inherit the JoystickDisplayClass methods as they are specific to joysticks
  void init(const dynamics2_t sze, const uint32_t emsk);
  void draw(void);
  // void renew(void) {}; // do nothing as this class only supports one instance
  
  uint32_t button_pressed { NUM_BUTTONS };
};
