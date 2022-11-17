#include "fruitbox.hpp"

using namespace std;

uint32_t TitleStripDisplayClass::title_strip_offset { 0 };
uint32_t TitleStripDisplayClass::start_title_strip { 0 };
bool     TitleStripDisplayClass::idle { false };
title_strip_move_direction_e TitleStripDisplayClass::move_direction { title_strip_move_direction_e::None };
uint32_t TitleStripDisplayClass::strip_code {};
uint32_t TitleStripDisplayClass::paired_strip_code {};
string   TitleStripDisplayClass::strip_code_str {};


const animate_t LeftAnimation[num_title_strip_move_effects][animation_title_strips] =
{
//    ------------------ Current TitleStrip -------------------       ------------------- Next TitleStrip --------------------
//    ix,  iy,  iw,  ih,  ia,     dx,  dy,  dw,  dh,  da, fd, tl  h      ix,  iy,  iw,  ih,  ia,     dx,  dy,  dw,  dh,  da,  fd, tl h
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}, {{ -1 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}},  // swipe left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 0, 1, 0}, {{  0 , -1 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 0, 1, 0}},  // swipe down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 ,  0 ,  0 ,  0 }, 0, 0, 1}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 1, 0, 1}},  // reveal left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 , -1 }, 1, 1, 0}, {{  0 , -1 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 ,  0 ,  0 }, 1, 1, 0}},  // reveal down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  1 ,  0 , -1 ,  0 , -1 }, 1, 0, 1}, {{  0 ,  0 ,  0 ,  1 ,  0 }, {  0 ,  0 ,  1 ,  0 ,  1 }, 1, 0, 1}},  // squash left
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 , -1 , -1 }, 1, 1, 0}, {{  0 ,  1 ,  1 ,  0 ,  0 }, {  0 , -1 ,  0 ,  1 ,  1 }, 1, 1, 0}},  // squash down
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 ,  0 }, 2, 1, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 2, 1, 0}}   // dissolve
};

const animate_t RightAnimation[num_title_strip_move_effects][animation_title_strips] =
{
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 0, 1, 1}, {{  1 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 0, 1, 1}},  // swipe right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}, {{  0 ,  1 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}},  // swipe up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 , -1 }, 1, 1, 1}, {{  1 ,  0 ,  1 ,  1 ,  1 }, { -1 ,  0 ,  0 ,  0 ,  0 }, 1, 1, 1}},  // reveal right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 , -1 ,  0 ,  0 ,  0 }, 0, 0, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 1, 0, 0}},  // reveal up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 , -1 ,  0 , -1 }, 1, 1, 1}, {{  1 ,  0 ,  0 ,  1 ,  0 }, { -1 ,  0 ,  1 ,  0 ,  1 }, 1, 1, 1}},  // squash right
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  1 ,  0 , -1 , -1 }, 1, 0, 0}, {{  0 ,  0 ,  1 ,  0 ,  0 }, {  0 ,  0 ,  0 ,  1 ,  1 }, 1, 0, 0}},  // squash up
  {{{  0 ,  0 ,  1 ,  1 ,  1 }, {  0 ,  0 ,  0 ,  0 ,  0 }, 2, 1, 0}, {{  0 ,  0 ,  1 ,  1 ,  0 }, {  0 ,  0 ,  0 ,  0 ,  1 }, 2, 1, 0}}   // dissolve
};

const string * TextDescriptionAddSongTitle(const song_t *song, const song_t *paired_song) { return &song->title; }
const string * TextDescriptionAddSongArtist(const song_t *song, const song_t *paired_song) { return &song->artist; }
const string * TextDescriptionAddAlbumTitle(const song_t *song, const song_t *paired_song) { return &song->album; }
const string * TextDescriptionAddAlbumArtist(const song_t *song, const song_t *paired_song) { return &song->albumArtist; }
const string * TextDescriptionAddYear(const song_t *song, const song_t *paired_song) { return &song->year; }
const string * TextDescriptionAddGenre(const song_t *song, const song_t *paired_song) { return &song->genre; }
const string * TextDescriptionAddTrackNumber(const song_t *song, const song_t *paired_song) { return &song->trackNumberStr; }
const string * TextDescriptionAddPublisher(const song_t *song, const song_t *paired_song) { return &song->publisher; }
const string * TextDescriptionAddISRC(const song_t *song, const song_t *paired_song) { return &song->isrc; }
const string * TextDescriptionAddCustomTag(const song_t *song, const song_t *paired_song) { return &song->custom_tag; }
const string * TextDescriptionAddLength(const song_t *song, const song_t *paired_song) { return &song->lengthStr; }
const string * TextDescriptionAddStripCode(const song_t *song, const song_t *paired_song) { TitleStripDisplayClass::strip_code_str = Engine->IntToSel(TitleStripDisplayClass::strip_code); return &TitleStripDisplayClass::strip_code_str; }
const string * TextDescriptionAddPairedSongTitle(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->title; else return nullptr;}
const string * TextDescriptionAddPairedSongArtist(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->artist; else return nullptr;}
const string * TextDescriptionAddPairedAlbumTitle(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->album; else return nullptr;}
const string * TextDescriptionAddPairedAlbumArtist(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->albumArtist; else return nullptr;}
const string * TextDescriptionAddPairedYear(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->year; else return nullptr;}
const string * TextDescriptionAddPairedGenre(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->genre; else return nullptr;}
const string * TextDescriptionAddPairedTrackNumber(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->trackNumberStr; else return nullptr;}
const string * TextDescriptionAddPairedPublisher(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->publisher; else return nullptr;}
const string * TextDescriptionAddPairedISRC(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->isrc; else return nullptr;}
const string * TextDescriptionAddPairedCustomTag(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->custom_tag; else return nullptr;}
const string * TextDescriptionAddPairedLength(const song_t *song, const song_t *paired_song) { if (paired_song) return &paired_song->lengthStr; else return nullptr;}
const string * TextDescriptionAddPairedStripCode(const song_t *song, const song_t *paired_song) { TitleStripDisplayClass::strip_code_str = Engine->IntToSel(TitleStripDisplayClass::paired_strip_code); return &TitleStripDisplayClass::strip_code_str; }

void TitleStripDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(sze, emsk);
  for (auto &b : title_strip_bitmap) {
    b = al_create_bitmap(size.x.val, size.y.val);
    // bitmaps_created++; log_file << "al_create_bitmap(" << size.x.val << "," << size.y.val << ") - " << bitmaps_created << " TitleStripDisplayClass::init" << endl;
    if (b == nullptr) error("Couldn't create %d x %d title_strip_bitmap", size.x.val, size.y.val);
  }
  update(StatusEvent_init);
  
  desc.reserve(128);
}

bool TitleStripDisplayClass::update
(
  const uint32_t event
)
{
  if (state != title_strip_state_t::idle) TitleStripDisplayClass::idle = false; // common idle for all title_strips

  switch (state)
  {
    case title_strip_state_t::idle :
      if (event & StatusEvent_TitleStripMoveChange)
      {
        if (TitleStripDisplayClass::move_direction == title_strip_move_direction_e::Left)
        {
          move_delay_timer = 0;
          if (move_reverse)
          {
            animate_direction = animate_direction_e::animate_right;
          }
          else
          {
            animate_direction = animate_direction_e::animate_left;
          }
          state = title_strip_state_t::wait_move_delay;
        }
        else if (TitleStripDisplayClass::move_direction == title_strip_move_direction_e::Right)
        {
          move_delay_timer = 0;
          if (move_reverse)
          {
            animate_direction = animate_direction_e::animate_left;
          }
          else
          {
            animate_direction = animate_direction_e::animate_right;
          }
          state = title_strip_state_t::wait_move_delay;
        }
      }
      break;

    case title_strip_state_t::wait_move_delay :
      if (move_delay_timer == move_delay)
      {
        ConstructTitleStrip();
        if (Config->skin_general->title_strip_move_style.speed)
        {
          animation_steps = animateInit(Config->skin_general->title_strip_move_style.effect);
          state = title_strip_state_t::moving;
        }
        else
        { // zero speed is instant redraw
          // Display->redraw = true;
          al_set_target_bitmap(bitmap);
          al_draw_bitmap(title_strip_bitmap[1 - title_strip_toggle], 0, 0, 0);
          state = title_strip_state_t::idle;
        }
      }
      else
      {
        ++move_delay_timer;
      }
        
      break;

    case title_strip_state_t::moving :
      // Display->redraw = true;
      if (animateTitleStrip() == false)
      { // Engine_finished moving, so draw visible title_strip at final place
        al_clear_to_color(al_map_rgba(0,0,0,0));
        al_draw_bitmap(title_strip_bitmap[1 - title_strip_toggle], 0, 0, 0);
        state = title_strip_state_t::idle;
      }
      break;

    case title_strip_state_t::init :
      ConstructTitleStrip();
      // Display->redraw = true;
      al_set_target_bitmap(bitmap);
      al_draw_bitmap(title_strip_bitmap[1 - title_strip_toggle], 0, 0, 0);
      state = title_strip_state_t::idle;
      break;
  }
  title_strip_offset++;
  
  return true;
}

void TitleStripDisplayClass::ConstructDescription(const string &str, const song_t *song, const song_t *paired_song, bool add_song_nums)
{
  // copy the string to desc, replacing $var codes with actual strings...

  if (add_song_nums)
  {
    // Note : append() ( or += ) is much faster than + apparently...
    desc = "<";
    desc += Engine->IntToSel(TitleStripDisplayClass::strip_code);
    desc += "> ";
  }
  else
  {
    desc.clear();
  }

  for (auto c = str.cbegin(); c != str.cend(); ++c)  // each character in string...
  {
    if (*c == TitleStripDescriptionsVarStart)
    {
      auto desc_idx { static_cast<uint32_t>(*(++c)) - 1 }; // index is value after TitleStripDescriptionsVarStart (- 1 as +1 when constructing to prevent null characters)
      const string *s { text_description[desc_idx].add_desc_func(song, paired_song) };
      if (s) desc += *s;
    }
    else
    {
      desc += *c;
    }
  }

}

void TitleStripDisplayClass::ConstructSinglesTitleStrip(void)
{
  ALLEGRO_BITMAP *title_strip_bm = title_strip_bitmap[title_strip_toggle];

  title_strip_toggle = 1 - title_strip_toggle;

  uint32_t pair_songs { static_cast<uint32_t>(Config->skin_general->pair_songs == pair_songs_e::No ? 0 : 1) };
  al_set_target_bitmap(title_strip_bm);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  int32_t width { al_get_bitmap_width(title_strip_bm) };
  
  uint32_t title_strip { TitleStripDisplayClass::title_strip_offset + TitleStripDisplayClass::start_title_strip };
  ALLEGRO_BITMAP *background_bitmap { Config->skin_general->default_title_strip_bkgnd.bm };

  if (title_strip < Database->number_of_title_strips)
  {
    song_t *first_song_on_title_strip { Database->GetSong(title_strip, 0) };
    background_bitmap = first_song_on_title_strip->strip_bg;
  }

  if (background_bitmap != nullptr)
  {
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(background_bitmap)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(background_bitmap)) };
    al_draw_scaled_bitmap(background_bitmap,  0 ,  0 , sw, sh,  0 ,  0 , size.x.val, size.y.val, 0);
  }

  uint32_t sinc { size.y.val / Config->skin_general->songs_per_title_strip };
  uint32_t yinc { 2 * sinc / (4 - pair_songs) };

  for (uint32_t entry = 0; entry < Config->skin_general->songs_per_title_strip; ++entry)
  {
    song_t *song {};
    song_t *paired_song {};
    uint32_t y { entry * sinc };
    uint32_t extra_y { y };
    uint32_t second_entry { entry + 1 };

    uint32_t title_strip { TitleStripDisplayClass::title_strip_offset + TitleStripDisplayClass::start_title_strip };

    if (title_strip >= Database->number_of_title_strips) return;

    if (y > size.y.val) break; // don't bother drawing text off title_strip

    song = Database->GetSong(title_strip, entry);
    if (second_entry < Config->skin_general->songs_per_title_strip) {
      paired_song = Database->GetSong(title_strip, second_entry);
    }

    if (song)
    {
      TitleStripDisplayClass::strip_code = entry + (Config->skin_general->songs_per_title_strip * TitleStripDisplayClass::title_strip_offset);
      TitleStripDisplayClass::paired_strip_code = TitleStripDisplayClass::strip_code + 1;

      // draw "song" line
      if (Database->dump_title_strips)
      // if we are dumping title strip images to files, we need to construct a string which contains all the select codes
      // for the current title strip.  This is then used as part of the title strip file name...
      {
        Database->dump_title_strip_filename += "_" + Engine->IntToSel(TitleStripDisplayClass::strip_code);
      }
      
      ConstructDescription(Config->skin_general->song_description, song, paired_song, debug_song_nums);
      Display->Text(title_strip_bm, Config->skin_general->song_text, width, 0, y, desc);

      // draw "artist" line
      y += yinc;
      string *artist_desc { &Config->skin_general->matched_artist_description };

      // if song artists in song pair are the not the same (or second song is missing) we use the artist_description...
      if (paired_song) { // second (paired) song is present...
        if (song->artist != paired_song->artist) // ...but has a different artist to the first
        {
          artist_desc = &Config->skin_general->artist_description;
        }
      }

      ConstructDescription(*artist_desc, song, paired_song, false);
      Display->Text(title_strip_bm, Config->skin_general->artist_text, width, 0, y, desc);

      if (pair_songs && paired_song)
      { // draw second "song" line (in pair)
        if (++entry < Config->skin_general->songs_per_title_strip)
        {
          y += yinc;
          ++TitleStripDisplayClass::strip_code;
          if (Database->dump_title_strips)
          // if we are dumping title strip images to files, we need to construct a string which contains all the select codes
          // for the current title strip.  This is then used as part of the title strip file name...
          {
            Database->dump_title_strip_filename += "_" + Engine->IntToSel(TitleStripDisplayClass::strip_code);
          }
          
          ConstructDescription(Config->skin_general->paired_song_description, song, paired_song, debug_song_nums);
          Display->Text(title_strip_bm, Config->skin_general->paired_song_text, width, 0, y, desc);
        }
      }

      // Draw "extra" line(s)
      for (auto e = 0; e < Config->skin_general->extra_description.size(); ++e)
      {
        if (e < Config->skin_general->extra_text.size()) // only draw text if extra text is defined
        {
          ConstructDescription(Config->skin_general->extra_description[e], song, paired_song, false);
          Display->Text(title_strip_bm, Config->skin_general->extra_text[e], width, 0, extra_y, desc);
        }
      }
    }
  }
}

void TitleStripDisplayClass::ConstructAlbumsTitleStrip(void)
{
  ALLEGRO_BITMAP *title_strip_bm   { title_strip_bitmap[title_strip_toggle] };
  bitmap_t *coverart_bitmap { &album_coverart_bitmap[title_strip_toggle] };
  uint32_t title_strip { TitleStripDisplayClass::title_strip_offset + TitleStripDisplayClass::start_title_strip };

  title_strip_toggle = 1 - title_strip_toggle;

  al_set_target_bitmap(title_strip_bm);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  int32_t width { al_get_bitmap_width(title_strip_bm) };
  
  ALLEGRO_BITMAP *background_bitmap { nullptr };

  if (title_strip < Database->number_of_title_strips)
  {
    song_t *first_song_on_title_strip { Database->GetSong(title_strip, 0) };
    background_bitmap = first_song_on_title_strip->strip_bg;
  }

  // draw background...
  if (background_bitmap != nullptr)
  {
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(background_bitmap)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(background_bitmap)) };
    al_draw_scaled_bitmap(background_bitmap, 0 , 0 , sw, sh, 0 , 0 , size.x.val, size.y.val, 0);
  }

  if (title_strip >= Database->number_of_title_strips) return;
  song_t *song { Database->GetSong(title_strip, 0) };

  // draw artwork...
  Audio->LoadAlbumArtwork(song, coverart_bitmap);

  if (coverart_bitmap->handle != nullptr)
  {
    uint32_t sx { Config->skin_general->album_art_size.x };
    uint32_t sy { Config->skin_general->album_art_size.y };
    uint32_t sw { static_cast<uint32_t>(al_get_bitmap_width(coverart_bitmap->handle)) };
    uint32_t sh { static_cast<uint32_t>(al_get_bitmap_height(coverart_bitmap->handle)) };
    uint32_t dx { Config->skin_general->album_art_offset.x };
    uint32_t dy { Config->skin_general->album_art_offset.y };
    if (Config->skin_general->album_art_angle)
    {
      float ang = static_cast<float>(Config->skin_general->album_art_angle) * (ALLEGRO_PI / 180.0);
      float cx { static_cast<float>(sw >> 1) };
      float cy { static_cast<float>(sh >> 1) };
      float ssx { static_cast<float>(sx) / static_cast<float>(sw) };
      float ssy { static_cast<float>(sy) / static_cast<float>(sh) };
      al_draw_scaled_rotated_bitmap(coverart_bitmap->handle, cx, cy, dx+(sx>>1), dy+(sy>>1), ssx, ssy, ang, 0);
    }
    else
    {
      al_draw_scaled_bitmap(coverart_bitmap->handle, 0, 0, sw, sh, dx, dy, sx, sy, 0);
    }
  }

  TitleStripDisplayClass::strip_code = TitleStripDisplayClass::title_strip_offset;

  // draw "album" line...
  if (Database->dump_title_strips)
  // if we are dumping title strip images to files, we need to construct a string which contains all the select codes
  // for the current title strip.  This is then used as part of the title strip file name...
  {
    Database->dump_title_strip_filename += "_" + Engine->IntToSel(TitleStripDisplayClass::strip_code);
  }
  
  ConstructDescription(Config->skin_general->paired_song_description, song, nullptr, debug_song_nums);
  Display->Text(title_strip_bm, Config->skin_general->album_text, width, 0, 0, desc);

  // draw "artist" line
  ConstructDescription(Config->skin_general->artist_description, song, nullptr, false);
  Display->Text(title_strip_bm, Config->skin_general->artist_text, width, 0, 0, desc);

  // draw album songs...
  uint32_t line_spacing { Config->skin_general->album_song_title_line_spacing};

  // if (Config->skin_general->song_text.font_number >= Config->fonts.size()) return; // invalid song title font number

  for (uint32_t entry = 0; entry < Config->skin_general->songs_per_title_strip; entry++)
  {
    uint32_t text_height {static_cast<uint32_t>(Config->fonts[Config->skin_general->song_text.font_number].size)};
    uint32_t y { entry * (line_spacing + text_height) };

    if (title_strip >= Database->number_of_title_strips) return;

    if (y > size.y.val) break; // don't bother drawing text off title_strip

    song = Database->GetSong(title_strip, entry);
    if (song) // draw song title
    {
      ConstructDescription(Config->skin_general->song_description, song, nullptr, false);
      Display->Text(title_strip_bm, Config->skin_general->song_text, width, 0, y, desc);
    }
  }

  // Draw "extra" line(s)
  for (auto e = 0; e < Config->skin_general->extra_description.size(); ++e)
  {
    if (e < Config->skin_general->extra_text.size()) // only draw text if extra text is defined
    {
      ConstructDescription(Config->skin_general->extra_description[e], song, nullptr, false);
      Display->Text(title_strip_bm, Config->skin_general->extra_text[e], width, 0, 0, desc);
    }
  }
}

void TitleStripDisplayClass::ConstructTitleStrip(void)
{
  if (Config->skin_general->album_mode == false)
  {
    ConstructSinglesTitleStrip();
  }
  else
  {
    ConstructAlbumsTitleStrip();
  }
}

void TitleStripDisplayClass::SaveTitleStrip(const string &filename)
{
  al_save_bitmap(filename.c_str(), title_strip_bitmap[1 - title_strip_toggle]);
}

uint32_t TitleStripDisplayClass::animateInit
(
  const uint32_t ani_num
)
{
  int32_t steps;
  const animate_t *ani;
  ani_t *m;
  const animate_t *a;
  int32_t sizex { Config->skin_general->title_strip_size.x.val };
  int32_t sizey { Config->skin_general->title_strip_size.y.val };
  uint32_t speed { Config->skin_general->title_strip_move_style.speed };

  if (animate_direction == animate_direction_e::animate_left)
  {
    ani = LeftAnimation[ani_num];
  }
  else
  {
    ani = RightAnimation[ani_num];
  }

  Animate[title_strip_toggle]     = &ani[0];
  Animate[1 - title_strip_toggle] = &ani[1];

  if (ani[0].horz)
  {
    steps = sizex / speed;
  }
  else
  {
    steps = sizey / speed;
  }
  for (uint32_t i = 0; i < animation_title_strips; ++i)
  {
    m = &move[i];
    a = Animate[i];
    m->x = a->init.x * sizex;
    m->y = a->init.y * sizey;
    m->w = a->init.w * sizex;
    m->h = a->init.h * sizey;
    m->a = a->init.a * 255;

    move_delta[i].x = a->delta.x * speed;
    move_delta[i].y = a->delta.y * speed;
    move_delta[i].w = a->delta.w * speed;
    move_delta[i].h = a->delta.h * speed;
    move_delta[i].a = a->delta.a * 255 / steps;
  }
  return steps;
}

bool TitleStripDisplayClass::animateTitleStrip(void)
{
  uint32_t first_title_strip;
  uint32_t last_title_strip;
  uint32_t title_strip_dir;
  ani_t *m, *d;
  animate_t *a;
  int32_t sizex { Config->skin_general->title_strip_size.x.val };
  int32_t sizey { Config->skin_general->title_strip_size.y.val };

  for (uint32_t i = 0; i < animation_title_strips; ++i) // change title_strip positions/sizes...
  {
    m = &move[i];
    d = &move_delta[i];

    m->x += d->x;
    m->y += d->y;
    m->w += d->w;
    m->h += d->h;
    m->a += d->a;
  }

  if (title_strip_toggle ^ Animate[0]->top_layer)
  {
    first_title_strip = 0;
    last_title_strip = animation_title_strips;
    title_strip_dir = 1;
  }
  else
  {
    first_title_strip = animation_title_strips  -1;
    last_title_strip = first_title_strip - animation_title_strips;
    title_strip_dir = -1;
  }

  al_set_target_bitmap(bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));

  for (uint32_t title_strip = first_title_strip; title_strip != last_title_strip; title_strip += title_strip_dir) // draw title_strip and its animation pair...
  {
    m = &move[title_strip];
    uint8_t a = static_cast<uint8_t>(m->a);
    ALLEGRO_BITMAP *bm = title_strip_bitmap[title_strip];

    if (Animate[title_strip]->fade == 2) // alpha fade
    {
      al_draw_tinted_scaled_bitmap(bm, al_map_rgba(a,a,a,a), 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
    else if ((Animate[title_strip]->fade == 1) && Config->skin_general->title_strip_move_style.fading) // fade to/from black
    {
      al_draw_tinted_scaled_bitmap(bm, al_map_rgb(a,a,a), 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
    else
    {
      al_draw_scaled_bitmap(bm, 0, 0, sizex, sizey, m->x, m->y, m->w, m->h, 0);
    }
  }
  animation_steps--;

  return (animation_steps ? true : false);
}


