#pragma once

#include "fruitbox.hpp"

using namespace std;

class JoystickDisplayClass : public DisplayBaseClass {
public:

  JoystickDisplayClass()
  {
    supports_dynamics = false;
  }

  void init(const dynamics2_t sze, const uint32_t emsk);

  void cfgRead(string line) {
    // DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Enable, enabled)) return;
    if (GetParam(line, cfgKeyword_DisableTitleStripFlip, disable_title_strip_flip)) return;
    if (GetParam(line, cfgKeyword_Bitmap, bitmap_name, false))return;
    if (GetParam(line, cfgKeyword_Size, size)) return;
    if (GetParam(line, cfgKeyword_Angle, angle)) return;
    if (GetParam(line, cfgKeyword_Tint, tint))
    {
      tint_defined = true;
      return;
    }
    if (GetParam(line, cfgKeyword_HorzFlip, horzflip)) return;
    if (GetParam(line, cfgKeyword_VertFlip, vertflip)) return;
    if (GetParam(line, cfgKeyword_Offset, offset)) return;
  }

  void cfgWrite(ofstream &strm)
  {
    PutParam(strm, cfgKeyword_Enable, enabled);
    PutParam(strm, cfgKeyword_DisableTitleStripFlip, disable_title_strip_flip);
    PutParam(strm, cfgKeyword_Bitmap, bitmap_name);
    PutParam(strm, cfgKeyword_Size, size);
    PutParam(strm, cfgKeyword_Angle, angle);
    PutParam(strm, cfgKeyword_Tint, tint);
    PutParam(strm, cfgKeyword_HorzFlip, horzflip);
    PutParam(strm, cfgKeyword_VertFlip, vertflip);
    PutParam(strm, cfgKeyword_Offset, offset);
  }

  virtual JoystickDisplayClass* clone() const { return new JoystickDisplayClass(*this); }

  virtual void DescribeParams(ofstream &strm, const char *indent) {
    DescribeParam(strm, indent, cfgKeyword_Enable                , cfgKeywordDesc_JoystickEnable        , false);
    DescribeParam(strm, indent, cfgKeyword_DisableTitleStripFlip , cfgKeywordDesc_DisableTitleStripFlip , false);
    DescribeParam(strm, indent, cfgKeyword_Bitmap                , cfgKeywordDesc_Bitmap                , false);
    DescribeParam(strm, indent, cfgKeyword_Size                  , cfgKeywordDesc_Size                  , false);
    DescribeParam(strm, indent, cfgKeyword_Angle                 , cfgKeywordDesc_Angle                 , false);
    DescribeParam(strm, indent, cfgKeyword_Tint                  , cfgKeywordDesc_Tint                  , false);
    DescribeParam(strm, indent, cfgKeyword_HorzFlip              , cfgKeywordDesc_HorzFlip              , false);
    DescribeParam(strm, indent, cfgKeyword_VertFlip              , cfgKeywordDesc_VertFlip              , false);
    DescribeParam(strm, indent, cfgKeyword_Offset                , cfgKeywordDesc_JoystickOffset        , false);
  }

  void SetPositionToTitleStrip(const uint32_t x, const uint32_t y)
  {
    // here, the base class position is an offset to the calculated position...
    position.x.val = static_cast<uint32_t>(static_cast<int32_t>(title_strip_position.at(x).at(y).x));
    position.y.val = static_cast<uint32_t>(static_cast<int32_t>(title_strip_position.at(x).at(y).y));
  }

  vector< vector<uints2_t> > title_strip_position { };

  ints2_t offset {};

  virtual void draw(void);
  bool enabled { false };
  bool disable_title_strip_flip { false };

private:
  string bitmap_name {};
};

