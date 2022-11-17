#include "fruitbox.hpp"

using namespace std;

void SpectrumAnalyserDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(size, emsk); // use objects size (from reading config file)
  if (band.size() == 0) // no bands defined, so make them all active...
  {
    band_gain_t b {};
    for (uint32_t i = 0; i < spectrum_analyser_bands; ++i)
    {
      b.num = i;
      band.push_back(b);
    }
  }

  // scale individual bands gains relative to size of bitmap, averaging constant, etc...

  for (auto &b : band)
  {
    b.gain *= static_cast<double>(al_get_bitmap_height(bitmap));
    // cout << "GAIN = " << b.gain << endl;
    // b.gain /= spectrum_analyser_max_av_len;
  }

  Audio->spectrum_analyser = true; // enables hacked equaliser in libmpg123/equalizer.c
}

void SpectrumAnalyserDisplayClass::renew(void)
{
  band.clear();
  decay = 0;
  mode = spectrum_analyser_mode_e::Scaled;
  channel = spectrum_analyser_channel_e::Both;
  band_bm.handle = nullptr;
  // ResetBaseParams();
  DisplayBaseClass::renew();
}

bool SpectrumAnalyserDisplayClass::update
(
  const uint32_t event
)
{
  if (DisplayBaseClass::update(event) == false) return false;

  // Display->redraw = true;

  if (band_bm.handle == nullptr) return false; // no band bitmaps defined

  al_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  uint32_t num_bands { band.size() };
  uint32_t bitmap_w  { static_cast<uint32_t>(al_get_bitmap_width(bitmap)) };
  uint32_t bitmap_h  { static_cast<uint32_t>(al_get_bitmap_height(bitmap)) };
  uint32_t band_bm_w { static_cast<uint32_t>(al_get_bitmap_width(band_bm.handle)) };
  uint32_t band_bm_h { static_cast<uint32_t>(al_get_bitmap_height(band_bm.handle)) };
  uint32_t band_width { bitmap_w / num_bands };
  uint32_t band_xpos { 0 };

  for (auto &b : band)
  {
    uint32_t val;

    if (channel == spectrum_analyser_channel_e::Left)
    {
      val = static_cast<uint32_t>(spectrum_analyser_band[0][b.num] * b.gain);
      // cout << "left gain " << b.gain << " " << spectrum_analyser_band[0][b.num] << " " << val << endl;
    }
    else if (channel == spectrum_analyser_channel_e::Right)
    {
      val = static_cast<uint32_t>(spectrum_analyser_band[1][b.num] * b.gain);
      // cout << "right gain " << b.gain << " " << spectrum_analyser_band[1][b.num] << " " << val << endl;
    }
    else // Both
    {
      val = static_cast<uint32_t>((spectrum_analyser_band[0][b.num] + spectrum_analyser_band[1][b.num]) * b.gain) / 2;
      // cout << "both gain " << b.gain << " " << spectrum_analyser_band[0][b.num] << " " << spectrum_analyser_band[1][b.num] << " " << val << endl;
    }

// void Decay(band_gain_t b, const uint32_t val);
    if (decay)
    {
      if (val >= b.val) // new band value is greater than current value
      {
        b.val = val; // so reset current value to the new (higher) value
      }
      else // new band value is smaller, so just decay current value
      {
        uint32_t delta_val { b.val - val };
        if (delta_val < decay)
        // if the difference between current and new value is less than the decay value,
        // then we just reduce by the difference (this prevents jittering on slow decreases)
        {
          if (b.val >= delta_val) b.val -= delta_val;
        }
        else
        {
          if (b.val >= decay) b.val -= decay;
        }
      }
    }
    else // not decay mode
    {
      b.val = val;
    }
  }

  switch (mode)
  {
    case spectrum_analyser_mode_e::Scaled :
      for (auto &b : band)
      {
        int32_t y = bitmap_h - b.val - b.offset.y;
        if (y < 0) y = 0;
        // al_draw_scaled_bitmap(band_bm.handle, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, y, band_width, b.val, 0);
        al_draw_tinted_scaled_bitmap(band_bm.handle, b.tint, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, y, band_width, b.val, 0);
        band_xpos += band_width;
      }
    break;

    case spectrum_analyser_mode_e::Clipped :
      for (auto &b : band)
      {
        al_set_clipping_rectangle(0, bitmap_h - b.val, bitmap_w, b.val);
        // al_draw_scaled_bitmap(band_bm.handle, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, -b.offset.y, band_width, bitmap_h, 0);
        al_draw_tinted_scaled_bitmap(band_bm.handle, b.tint, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, -b.offset.y, band_width, bitmap_h, 0);
        band_xpos += band_width;
      }
      al_reset_clipping_rectangle();
    break;

    default : // Position
      for (auto &b : band)
      {
        int32_t y = bitmap_h - b.val - b.offset.y;
        if (y < 0) y = 0;
        // al_draw_scaled_bitmap(band_bm.handle, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, y, band_width, band_bm_h, 0);
        al_draw_tinted_scaled_bitmap(band_bm.handle, b.tint, 0, 0, band_bm_w, band_bm_h, band_xpos + b.offset.x, y, band_width, band_bm_h, 0);
        band_xpos += band_width;
      }
    break;
  }

  return true;
}
