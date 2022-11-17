#pragma once

#include "fruitbox.hpp"

using namespace std;

class DisplayBaseClass : public ConfigBaseClass {

public:

  void ResetBaseParams(void);
  void ResetDynamic(dynamic_t &var, int32_t val);
  void ResetDynamic(dynamics2_t &var, int32_t val1, int32_t val2);
  void ResetDynamic(dynamics4_t &var, int32_t val1, int32_t val2, int32_t val3, int32_t val4);
  void InitDynamic(dynamic_t &var);
  void InitDynamics(void);
  void UpdateDynamic(dynamic_t &var, const uint32_t event);
  void UpdateDynamics(const uint32_t event);

  virtual void init(const dynamics2_t sze, const uint32_t emsk) {
    // visible = true;
    size = sze;
    event_mask = emsk;
    bitmap = al_create_bitmap(size.x.val, size.y.val);
    // bitmaps_created++; log_file << "al_create_bitmap(" << size.x.val << "," << size.y.val << ") - " << bitmaps_created << " display_base::init" << endl;
    if (bitmap == nullptr) error("Couldn't create %d x %d display object bitmap", size.x.val, size.y.val);
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    InitDynamics();
    // if (!tint_defined) ResetDynamic(tint, 255, 255, 255, 255);
    tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
  }

  virtual void init(const dynamics2_t sze, const uint32_t emsk, const string bitmap_name) {
    // visible = true;
    size = sze;
    event_mask = emsk;
    if (bitmap_name.size() == 0) return;
    bitmap = al_load_bitmap(bitmap_name.c_str());
    if (bitmap == nullptr) error("Couldn't load bitmap '%s'", bitmap_name.c_str());
    if (size.x.val == 0) size.x.val = al_get_bitmap_width(bitmap); // if not specified, use bitmap size
    if (size.y.val == 0) size.y.val = al_get_bitmap_height(bitmap); // if not specified, use bitmap size
    InitDynamics();
    // if (!tint_defined) ResetDynamic(tint, 255, 255, 255, 255);
    tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
  }

  virtual bool update(const uint32_t event)
  {
    uint32_t evnt { event_mask & event };
    if (!evnt) return false; // don't do anything if no incoming events match any of bitmap objects's events
    UpdateDynamics(evnt);
    return true;
  }

  virtual void renew(void) {
    ResetBaseParams();
  };

  virtual void draw(void) {
    if (no_draw || !visible) return;
    if (bitmap != nullptr) {
      int flags { 0 };
      if (vertflip) flags |= ALLEGRO_FLIP_VERTICAL;
      if (horzflip) flags |= ALLEGRO_FLIP_HORIZONTAL;
      if (clipped)
      {
        al_set_clipping_rectangle(clip.x.val, clip.y.val, clip.w.val, clip.h.val);
      }
      else
      {
        al_reset_clipping_rectangle();
      }
      if (angle.val)
      {
        float ang = static_cast<float>(angle.val) * (ALLEGRO_PI / 180.0);
        int bw { al_get_bitmap_width(bitmap) };
        int bh { al_get_bitmap_height(bitmap) };
        float cx { static_cast<float>(bw >> 1) };
        float cy { static_cast<float>(bh >> 1) };
        float sx { static_cast<float>(size.x.val) / static_cast<float>(bw) };
        float sy { static_cast<float>(size.y.val) / static_cast<float>(bh) };
        al_draw_tinted_scaled_rotated_bitmap(bitmap, tint_colour, cx, cy, position.x.val + (size.x.val >> 1), position.y.val + (size.y.val >> 1), sx, sy, ang, flags);
      }
      else
      {
        al_draw_tinted_scaled_bitmap(bitmap, tint_colour, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), position.x.val, position.y.val, size.x.val, size.y.val, flags);
      }
    }
  }

  void cfgRead(string line) {
    if (GetParam(line, cfgKeyword_Visible, visible)) return;
    if (GetParam(line, cfgKeyword_Size, size)) return;
    if (GetParam(line, cfgKeyword_Position, position)) return;
    if (GetParam(line, cfgKeyword_Clip, clip))
    {
      clipped = true;
      return;
    }
    if (GetParam(line, cfgKeyword_Angle, angle)) return;
    if (GetParam(line, cfgKeyword_Tint, tint))
    {
      tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
      tint_defined = true;
      return;
    }
    if (GetParam(line, cfgKeyword_HorzFlip, horzflip)) return;
    if (GetParam(line, cfgKeyword_VertFlip, vertflip)) return;
    if (GetParam(line, cfgKeyword_DynamicFlagEn, dynamic_flag_en)) return;
  }

  void cfgWrite(ofstream &strm)
  {
    PutParam(strm, cfgKeyword_Visible, visible);
    PutParam(strm, cfgKeyword_Size, size);
    PutParam(strm, cfgKeyword_Position, position);
    PutParam(strm, cfgKeyword_Clip, clip);
    PutParam(strm, cfgKeyword_Angle,angle);
    PutParam(strm, cfgKeyword_Tint, tint);
    PutParam(strm, cfgKeyword_HorzFlip, horzflip);
    PutParam(strm, cfgKeyword_VertFlip, vertflip);
    PutParam(strm, cfgKeyword_DynamicFlagEn, dynamic_flag_en);
  }
  
  void DescribeParams(ofstream &strm, const char *indent) {
    if (supports_dynamics)
    {
      DescribeParam(strm, indent, cfgKeyword_Visible       , cfgKeywordDesc_Visible        , false);
      DescribeParam(strm, indent, cfgKeyword_Size          , cfgKeywordDesc_SizeDynamic    , false);
      DescribeParam(strm, indent, cfgKeyword_Position      , cfgKeywordDesc_PositionDynamic, false);
      DescribeParam(strm, indent, cfgKeyword_Clip          , cfgKeywordDesc_ClipDynamic    , false);
      DescribeParam(strm, indent, cfgKeyword_Angle         , cfgKeywordDesc_AngleDynamic   , false);
      DescribeParam(strm, indent, cfgKeyword_Tint          , cfgKeywordDesc_TintDynamic    , false);
      DescribeParam(strm, indent, cfgKeyword_DynamicFlagEn , cfgKeywordDesc_DynamicFlagEn  , false);
    }
    else
    {
      DescribeParam(strm, indent, cfgKeyword_Visible , cfgKeywordDesc_Visible , false);
      DescribeParam(strm, indent, cfgKeyword_Size    , cfgKeywordDesc_Size    , false);
      DescribeParam(strm, indent, cfgKeyword_Position, cfgKeywordDesc_Position, false);
      DescribeParam(strm, indent, cfgKeyword_Clip    , cfgKeywordDesc_Clip    , false);
      DescribeParam(strm, indent, cfgKeyword_Angle   , cfgKeywordDesc_Angle   , false);
      DescribeParam(strm, indent, cfgKeyword_Tint    , cfgKeywordDesc_Tint    , false);
    }
    DescribeParam(strm, indent, cfgKeyword_HorzFlip, cfgKeywordDesc_HorzFlip, false);
    DescribeParam(strm, indent, cfgKeyword_VertFlip, cfgKeywordDesc_VertFlip, false);
  }

  virtual DisplayBaseClass* clone() const = 0;

  dynamics2_t size {};
  dynamics2_t position {};
  dynamics4_t clip {};
  dynamic_t angle { };
  dynamics4_t tint {
    { &DynamicParameterNone, 255, 255, 255, false, 0 },
    { &DynamicParameterNone, 255, 255, 255, false, 0 },
    { &DynamicParameterNone, 255, 255, 255, false, 0 },
    { &DynamicParameterNone, 255, 255, 255, false, 0 }
  };
  ALLEGRO_COLOR tint_colour {};
  bool tint_defined { false };
  bool horzflip { false };
  bool vertflip { false };
  bool no_draw { false };
  bool supports_dynamics { false };
  bool has_dynamics { false };
  bool clipped { false };
  bool visible { true };
  dynamic_flag_en_e dynamic_flag_en { dynamic_flag_en_e::None };
  ALLEGRO_BITMAP *bitmap {};

protected:
  // ALLEGRO_BITMAP *bitmap {};
  uint32_t event_mask { StatusEvent_InitEmpty };
};
