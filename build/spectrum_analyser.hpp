#pragma once

#include "fruitbox.hpp"

using namespace std;

#define NUM_SUB_BANDS         (32)      /* from mpg123-1.25.13/src/libmpg123/equalizer.c */
// #define MAX_BAND_VALUE        (16384)   /* from mpg123-1.25.13/src/libmpg123/equalizer.c */
// #define AVERAGING_LENGTH      (64)      /* from mpg123-1.25.13/src/libmpg123/equalizer.c */

// constexpr uint32_t spectrum_analyser_max_av_len { MAX_BAND_VALUE * AVERAGING_LENGTH };
constexpr uint32_t spectrum_analyser_bands { NUM_SUB_BANDS };

class SpectrumAnalyserDisplayClass : public DisplayBaseClass
{
public:

  SpectrumAnalyserDisplayClass() { supports_dynamics = true; }

  bool update(const uint32_t event) override;

  void init(const dynamics2_t sze, const uint32_t emsk);

  void renew(void);

  void cfgRead(string line)
  {
    band_gain_t b {};
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_Bitmap, band_bm)) return;
    if (GetParam(line, cfgKeyword_SpectrumAnalyserBand, b))
    {
      if (b.num < spectrum_analyser_bands) band.push_back(b);
      return;
    }
    if (GetParam(line, cfgKeyword_SpectrumAnalyserMode, mode)) return;
    if (GetParam(line, cfgKeyword_SpectrumAnalyserChannel, channel)) return;
    if (GetParam(line, cfgKeyword_SpectrumAnalyserDecay, decay)) return;
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    DisplayBaseClass::DescribeParams(strm, indent);
    DescribeParam(strm, indent, cfgKeyword_Bitmap, cfgKeywordDesc_SpectrumAnalyserBitmap, false);
    DescribeParam(strm, indent, cfgKeyword_SpectrumAnalyserBand, cfgKeywordDesc_SpectrumAnalyserBand, true);
    DescribeParam(strm, indent, cfgKeyword_SpectrumAnalyserMode, cfgKeywordDesc_SpectrumAnalyserMode, false);
    DescribeParam(strm, indent, cfgKeyword_SpectrumAnalyserChannel, cfgKeywordDesc_SpectrumAnalyserChannel, false);
    DescribeParam(strm, indent, cfgKeyword_SpectrumAnalyserDecay, cfgKeywordDesc_SpectrumAnalyserDecay, false);
  }

  SpectrumAnalyserDisplayClass* clone() const { return new SpectrumAnalyserDisplayClass(*this); }

private:
  bitmap_t band_bm { }; 
  uint32_t decay { 0 }; 
  vector<band_gain_t> band { };
  spectrum_analyser_mode_e mode { spectrum_analyser_mode_e::Scaled };
  spectrum_analyser_channel_e channel { spectrum_analyser_channel_e::Both };
};

