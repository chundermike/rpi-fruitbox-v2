#pragma once

#include "fruitbox.hpp"

using namespace std;

constexpr uint32_t animation_title_strips       { 2 };
constexpr uint32_t num_title_strip_move_effects { 7 };

enum class animate_direction_e {
 animate_left,
 animate_right
};

struct ani_t {
  int32_t x, y, w, h, a;
};

struct animate_t {
  ani_t init;
  ani_t delta;
  int32_t fade;      // 0 = no fade, 1 = fade to/from black, 2 = fade to/from alpha
  int32_t top_layer; // title_strip drawn second
  int32_t horz;      // horizontal movement (needed for calculation of animation_steps)
};

enum class title_strip_state_t {
  init, idle, wait_move_delay, moving
};

class TitleStripDisplayClass : public DisplayBaseClass {
public:
  void init(const dynamics2_t sze, const uint32_t emsk);

  bool update(const uint32_t event) override;

  void cfgRead(string line) {
    DisplayBaseClass::cfgRead(line);
    if (GetParam(line, cfgKeyword_MoveDelay, move_delay)) return;
    if (GetParam(line, cfgKeyword_MoveReverse, move_reverse)) return;
  }

  void DescribeParams(ofstream &strm, const char *indent) {
    // DisplayBaseClass::DescribeParams(ofstream &strm, indent); // don't use this as don't use base class size (use Config->skin_general->title_strip_size instead)
    DescribeParam(strm, indent, cfgKeyword_Visible     , cfgKeywordDesc_Visible     , false);
    DescribeParam(strm, indent, cfgKeyword_Position    , cfgKeywordDesc_Position    , false);
    DescribeParam(strm, indent, cfgKeyword_Clip        , cfgKeywordDesc_Clip        , false);
    DescribeParam(strm, indent, cfgKeyword_Angle       , cfgKeywordDesc_Angle       , false);
    DescribeParam(strm, indent, cfgKeyword_MoveDelay   , cfgKeywordDesc_MoveDelay   , false);
    DescribeParam(strm, indent, cfgKeyword_MoveReverse , cfgKeywordDesc_MoveReverse , false);
    DescribeParam(strm, indent, cfgKeyword_HorzFlip    , cfgKeywordDesc_HorzFlip    , false);
    DescribeParam(strm, indent, cfgKeyword_VertFlip    , cfgKeywordDesc_VertFlip    , false);
    DescribeParam(strm, indent, cfgKeyword_Tint        , cfgKeywordDesc_Tint        , false);
  }

  TitleStripDisplayClass* clone() const { return new TitleStripDisplayClass(*this); }

  // remember that static class member variables are shared amongst all title_strip class instances...
  static uint32_t title_strip_offset; // title_strip offset within display
  static uint32_t start_title_strip;  // start title_strip in database
  static bool idle;  // true if all title_strips idle
  static title_strip_move_direction_e move_direction;
  static uint32_t strip_code;
  static uint32_t paired_strip_code;
  static string   strip_code_str;
  
  void ConstructTitleStrip(void);
  void SaveTitleStrip(const string &filename);

private:
  uint32_t move_delay {};
  uint32_t move_delay_timer {};
  bool move_reverse { false };
  string desc { };

  title_strip_state_t state { title_strip_state_t::init };
  array <ALLEGRO_BITMAP*, animation_title_strips> title_strip_bitmap {};
  array <bitmap_t, animation_title_strips> album_coverart_bitmap {};
  void ConstructDescription(const string &var, const song_t *song, const song_t *paired_song, bool add_song_nums);
  void ConstructSinglesTitleStrip(void);
  void ConstructAlbumsTitleStrip(void);
  uint32_t title_strip_toggle {};
  
  uint32_t animateInit(const uint32_t ani_num);
  bool animateTitleStrip(void);
  animate_direction_e animate_direction {};
  float animation_steps {};
  ani_t move[animation_title_strips];
  ani_t move_delta[animation_title_strips];
  const animate_t *Animate[animation_title_strips];
  
};

