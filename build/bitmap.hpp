#pragma once

#include "fruitbox.hpp"

using namespace std;

class BitmapDisplayClass : public DisplayBaseClass
{
public:

  BitmapDisplayClass() { supports_dynamics = true; }
  
  void init(const dynamics2_t sze, const uint32_t emsk);

  void cfgRead(string line)
  {
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_File, bitmap_name)) return;
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DisplayBaseClass::DescribeParams(strm, indent);
    DescribeParam(strm, indent, cfgKeyword_File, cfgKeywordDesc_Bitmap, false);
  }

  BitmapDisplayClass* clone() const { return new BitmapDisplayClass(*this); }

  void renew(void) { // ensure no parameters from a previous status object are inherited to the next status objects
    bitmap_name.clear();
    DisplayBaseClass::renew(); // ResetBaseParams();
  }

private:
  string bitmap_name {};
};

