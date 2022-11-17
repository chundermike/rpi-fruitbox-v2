#include "fruitbox.hpp"
#include "fruitbox_logo.hpp"

using namespace std;

bool DisplayClass::jukebox_drawn { false };

DisplayClass::DisplayClass(uint32_t width, uint32_t height)
{
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);

  log_file << "Detecting display..." << endl;
  if (al_get_display_mode(0, &display_size) == nullptr) error("Failed to get display mode");

  if (width && height) // if (user-specified) width and height are not zero...
  {
    display_size.width = width;
    display_size.height = height;
  }

  log_file << "Creating " << display_size.width << " x " << display_size.height << " display..." << endl;
  display = al_create_display(display_size.width, display_size.height);
  if (display == nullptr) error("Failed to create %d x %d display", display_size.width, display_size.height);
 
  display_refresh_rate = display_size.refresh_rate;
  
  log_file << display_size.width << " x " << display_size.height << " (" << display_size.refresh_rate << "Hz)" << endl;

  al_hide_mouse_cursor(display);

  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);// | ALLEGRO_MIPMAP);

  // clear backbuffer to dialog backdrop_colour (for dialogs prior to jukebox backdrop)...
  al_set_target_bitmap(al_get_backbuffer(display));
  al_clear_to_color(al_map_rgba(255, 255, 255, 255));

  ALLEGRO_FILE *fruitbox_logo_f { al_open_memfile(fruitbox_logo_data, FRUITBOX_LOGO_LEN, "rb") };
  if (fruitbox_logo_f == nullptr) error( "Failed to load fruitbox logo mem file");
  fruitbox_logo_bm = al_load_bitmap_f(fruitbox_logo_f, ".png");
  if (fruitbox_logo_bm == nullptr) error( "Failed to load embedded logo");
  al_fclose(fruitbox_logo_f);

  al_set_display_icon(display, fruitbox_logo_bm);
  active = true;
}

DisplayClass::~DisplayClass()
{
  al_show_mouse_cursor(display);
  al_destroy_bitmap(fruitbox_logo_bm);
  al_destroy_bitmap(jukebox);
  al_destroy_display(display);
}

// void DisplayClass::CapitaliseAndQuote
// (
  // string     &str,
  // const bool cap_en,
  // const bool quo_en
// )
// {
  // if (cap_en) transform(str.begin(), str.end(),str.begin(), ::toupper);
  // if (quo_en) str = "\"" + str + "\"";
// }

int32_t DisplayClass::RenderText
// render text to bitmap. This will create the bitmap of exactly the correct size to hold the text
// left justified, uncondensed. DrawText() later will copy the bitmap to the target bitmap, justifying
// it and applying scrolling or condensing as required.
(
  ALLEGRO_BITMAP * &bitmap,
  const text_t   text,
  const string   &str
)
{
  if (bitmap != nullptr)
  {
    al_destroy_bitmap(bitmap);
    // bitmaps_created--; log_file << "al_destroy_bitmap" << " - " << bitmaps_created << " DisplayClass::RenderText" << endl;
  }
  if (str.size() == 0)
  {
    bitmap = nullptr;
    return 0;
  }
  
  // if (text.font_number >= Config->fonts.size()) return 0;

  ALLEGRO_FONT *font { Config->fonts.at(text.font_number).handle };
  // ALLEGRO_FONT *font { Config->fonts[text.font_number].handle };
  if (font == nullptr) return 0; // font not defined

  string s { };

  if (text.quoted)
  {
    s += "\"";
  }
  
  s += str;

  if (text.quoted)
  {
    s += "\"";
  }

  if (text.capitalise) transform(s.begin(), s.end(), s.begin(), ::toupper);

  if (text.mode == TextModeRegularEllipsis)
  // if text doesn't fit into max_width, replace last bit that doesn't fit with "..."
  {
    int32_t text_width = al_get_text_width(font, s.c_str());
    if (text_width > text.max_width)
    {
      int32_t ellipsis_text_width = al_get_text_width(font, "...");
    }
  }
  else if (text.mode == TextModeWordEllipsis)
  // if text doesn't fit into max_width, replace last bit that doesn't fit with "..." & last word
  {
    // int32_t text_width = al_get_text_width(font, s.c_str());
    // if (text_width > text.max_width)
    // {
      // string last_word = ;
      // int32_t ellipsis_text_width = al_get_text_width(font, "..." + last_word);
    // }
  }
    
  int32_t text_width = al_get_text_width(font, s.c_str());
  int32_t text_height { Config->fonts[text.font_number].size };

  // if (bitmap != nullptr)
  // {
    // al_destroy_bitmap(bitmap);
    // bitmaps_created--; log_file << "al_destroy_bitmap" << " - " << bitmaps_created << " DisplayClass::RenderText" << endl;
  // }

  if ((bitmap = al_create_bitmap(text_width, text_height)) != nullptr)
  {
    // bitmaps_created++; log_file << "al_create_bitmap(" << text_width << "," << text_height << ") - " << bitmaps_created << " DisplayClass::RenderText" << endl;
    ALLEGRO_BITMAP *prev_display { al_get_target_bitmap() };
    al_set_target_bitmap(bitmap);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_draw_text(font, text.colour, 0, 0, ALLEGRO_ALIGN_LEFT, s.c_str());
    al_set_target_bitmap(prev_display);
    
    return text_width;
  }
  else error("Couldn't create RenderText bitmap %d x %d", text_width, text_height);
  
  return 0;
}

void DisplayClass::DrawText
(
  ALLEGRO_BITMAP *text_bitmap,
  ALLEGRO_BITMAP *target_bitmap,
  const text_t   text,
  const int32_t  align_width,
  const int32_t  x,
  const int32_t  y
)
{
  if (text_bitmap == nullptr) return;
  
  int32_t tx { x + text.offset.x };
  int32_t ty { y + text.offset.y };

  int32_t target_bitmap_w { al_get_bitmap_width(target_bitmap) };
  int32_t target_bitmap_h { al_get_bitmap_height(target_bitmap) };
  int32_t text_bitmap_w   { al_get_bitmap_width(text_bitmap) };
  int32_t text_bitmap_h   { al_get_bitmap_height(text_bitmap) };
  
  if (ty > target_bitmap_h) return; // don't bother drawing text out of region

  bool condensed { (text.mode == TextModeCondensed) && (text_bitmap_w > text.max_width) };

  int32_t w { (condensed) ? static_cast<int32_t>(text.max_width) : text_bitmap_w };

  switch (text.alignment)
  {
    case ALLEGRO_ALIGN_CENTRE :
      tx += (align_width - w) / 2;
    break;
    
    case ALLEGRO_ALIGN_RIGHT :
      tx += align_width - w;
    break;
    
    // case ALLEGRO_ALIGN_LEFT :
      // tx += 0;
    // break;
  }
  
  al_set_target_bitmap(target_bitmap);

  if (condensed)
  {
    al_draw_scaled_bitmap(text_bitmap, 0, 0, text_bitmap_w, text_bitmap_h, tx, ty, text.max_width, text_bitmap_h, 0);
  }
  else
  {
    al_draw_bitmap(text_bitmap, tx, ty, 0);
  }

}

void DisplayClass::Text(
  ALLEGRO_BITMAP *bitmap,
  const text_t text,
  const int32_t align_width,
  const int32_t x,
  const int32_t y,
  const string &str
)
{
  RenderText(text_bm, text, str);
  // if (text_bm == nullptr) error("null text_bm!"); // INFINITE LOOP ??????????????????

  DrawText(text_bm, bitmap, text, align_width, x, y);
}

void DisplayClass::DrawJukebox(void)
{
  // draw jukebox to jukebox bitmap...

  al_set_target_bitmap(jukebox);
  al_clear_to_color(al_map_rgb(0,0,0));
  
  for (auto &i : Config->skin_display_object)
  {
    i->draw();
  }

  if (Config->joystick->enabled)
  {
    Config->joystick->draw();
  }

  // now copy jukebox bitmap to display backbuffer (which will scale it...)

  // ALLEGRO_BITMAP *prev_display { al_get_target_bitmap() };
  al_set_target_bitmap(al_get_backbuffer(display));

  if (Config->no_scale)
  {
    al_clear_to_color(al_map_rgb(0,0,0));
    if (Config->rotate)
    {
      float cx { static_cast<float>(al_get_bitmap_width(jukebox)) / 2 };
      float cy { static_cast<float>(al_get_bitmap_height(jukebox)) / 2 };
      float dx { static_cast<float>(display_size.width) / 2 };
      float dy { static_cast<float>(display_size.height) / 2 };
      al_draw_rotated_bitmap(jukebox, cx, cy, dx, display_size.height / 2, Config->rotate, 0);
    }
    else
    {
      float dx { (static_cast<float>(display_size.width)  - static_cast<float>(al_get_bitmap_width(jukebox))) / 2};
      float dy { (static_cast<float>(display_size.height) - static_cast<float>(al_get_bitmap_height(jukebox))) / 2};
      al_draw_bitmap(jukebox, dx, dy, 0);
    }
  }
  else
  {
    if (Config->rotate)
    {
      float cx { static_cast<float>(al_get_bitmap_width(jukebox)) / 2 };
      float cy { static_cast<float>(al_get_bitmap_height(jukebox)) / 2 };
      float dx { static_cast<float>(display_size.width) / 2 };
      float dy { static_cast<float>(display_size.height) / 2 };
      float xscale { static_cast<float>(display_size.width)  / static_cast<float>(al_get_bitmap_width(jukebox)) };
      float yscale { static_cast<float>(display_size.height) / static_cast<float>(al_get_bitmap_height(jukebox)) };
      al_draw_scaled_rotated_bitmap(jukebox, cx, cy, dx, dy, xscale, yscale, Config->rotate, 0);
    }
    else
    {
      al_draw_scaled_bitmap(jukebox, 0, 0, al_get_bitmap_width(jukebox), al_get_bitmap_height(jukebox), 0, 0, display_size.width, display_size.height, 0);
    }
  }
  // al_set_target_bitmap(prev_display);
  
  DisplayClass::jukebox_drawn = true;
}

