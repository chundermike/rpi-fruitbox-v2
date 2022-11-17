#include "fruitbox.hpp"

using namespace std;

void TouchSongDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(sze, emsk, bitmap_name);
  // title_strip_size.x = sze.x.val;
  // title_strip_size.y = sze.y.val;
}

void TouchSongDisplayClass::draw(void)
{
  if (title_strip_pressed_draw_en)
  {
    // bitmap         = title_strip_bm.handle;
    // size.x.val     = title_strip_size.x;
    // size.y.val     = title_strip_size.y;
    // position.x.val = title_strip_pos.x;
    // position.y.val = title_strip_pos.y;
    DisplayBaseClass::draw();
  }
}

void TouchSongDisplayClass::cfgRead(string line)
{
  DisplayBaseClass::cfgRead(line);

  if (GetParam(line, cfgKeyword_Bitmap, bitmap_name)) 
  {
    enabled = true;
    return;
  }
  if (GetParam(line, cfgKeyword_Offset, offset)) return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void TouchButtonsDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
//  DisplayBaseClass::init(sze, emsk);
}

void TouchButtonsDisplayClass::draw(void)
{
  if (Input->touch_button_pressed < NUM_BUTTONS) // touch area pressed
  {
    if (DialogBaseClass::touch_menu_active)
    {
      return; // don't draw anything when menus are active
    }
    
    touch_area_t *area { &Config->buttons->button[Input->touch_button_pressed].skin_touch_area };
// cout << "touch_button_pressed " << Input->touch_button_pressed << " ";
    if (area->bitmap != nullptr) {
// cout << al_get_bitmap_width(area->bitmap) << " " << al_get_bitmap_height(area->bitmap) << " " << area->x << " " << area->y << " " << area->w << " " << area->h;
      al_draw_scaled_bitmap(area->bitmap, 0, 0, al_get_bitmap_width(area->bitmap), al_get_bitmap_height(area->bitmap), area->x, area->y, area->w, area->h, 0);
     }
// cout << endl;
  }
}

void TouchButtonsDisplayClass::cfgRead(string line)
{
  for (auto b = 0; b < NUM_BUTTONS; ++b)
  {
    // if (GetParam(line, default_button[b].name , button[default_button[b].num])) return;
    if (GetParam(line, default_button[b].name , Config->buttons->button[default_button[b].num].skin_touch_area)) return;
  }
}

