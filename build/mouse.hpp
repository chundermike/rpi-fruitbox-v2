#pragma once

#include "fruitbox.hpp"

using namespace std;

class MouseDisplayClass : public DisplayBaseClass {
public:

  MouseDisplayClass()
  {
    supports_dynamics = false;
  }

  void init(const uint32_t emsk);

  void cfgRead(string line) {
    // cout <<" Mouse cfgread" << endl;
    if (GetParam(line, cfgKeyword_Enable, enabled)) return;
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
    if (GetParam(line, cfgKeyword_HotSpot, offset)) return;
    if (GetParam(line, cfgKeyword_MouseSensitivity, sensitivity)) return;
    if (GetParam(line, cfgKeyword_HideAfter, hide_after)) return;
  }

  void cfgWrite(ofstream &strm)
  {
    PutParam(strm, cfgKeyword_Enable, enabled);
    PutParam(strm, cfgKeyword_Bitmap, bitmap_name);
    PutParam(strm, cfgKeyword_Size, size);
    PutParam(strm, cfgKeyword_Angle, angle);
    PutParam(strm, cfgKeyword_Tint, tint);
    PutParam(strm, cfgKeyword_HorzFlip, horzflip);
    PutParam(strm, cfgKeyword_VertFlip, vertflip);
    PutParam(strm, cfgKeyword_HotSpot, offset);
    PutParam(strm, cfgKeyword_MouseSensitivity, sensitivity);
    PutParam(strm, cfgKeyword_HideAfter, hide_after);
  }

  virtual MouseDisplayClass* clone() const { return new MouseDisplayClass(*this); }

  virtual void DescribeParams(ofstream &strm, const char *indent) {
    DescribeParam(strm, indent, cfgKeyword_Enable           , cfgKeywordDesc_MouseEnable      , false);
    DescribeParam(strm, indent, cfgKeyword_Bitmap           , cfgKeywordDesc_Bitmap           , false);
    DescribeParam(strm, indent, cfgKeyword_Size             , cfgKeywordDesc_Size             , false);
    DescribeParam(strm, indent, cfgKeyword_Angle            , cfgKeywordDesc_Angle            , false);
    DescribeParam(strm, indent, cfgKeyword_Tint             , cfgKeywordDesc_Tint             , false);
    DescribeParam(strm, indent, cfgKeyword_HorzFlip         , cfgKeywordDesc_HorzFlip         , false);
    DescribeParam(strm, indent, cfgKeyword_VertFlip         , cfgKeywordDesc_VertFlip         , false);
    DescribeParam(strm, indent, cfgKeyword_HotSpot          , cfgKeywordDesc_MouseHotSpot     , false);
    DescribeParam(strm, indent, cfgKeyword_MouseSensitivity , cfgKeywordDesc_MouseSensitivity , false);
    DescribeParam(strm, indent, cfgKeyword_HideAfter        , cfgKeywordDesc_HideAfter        , false);
  }

  bool enabled { false };
  float sensitivity { 1.0 };
  ints2_t offset {};
  time_unit_t hide_after { TimeUnitFiveSeconds };

private:
  string bitmap_name {};
};

