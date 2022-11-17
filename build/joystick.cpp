#include "fruitbox.hpp"
#include "fruitbox_joystick_highlight.hpp"

using namespace std;

void JoystickDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
  // DisplayBaseClass::init(sze, emsk, bitmap_name);
  event_mask = emsk;

  if (bitmap_name.size() == 0) // no mouse graphic pointer specified, so use internal one...
  {
    ALLEGRO_FILE *fruitbox_joystick_highlight_f { al_open_memfile(fruitbox_joystick_highlight_data, FRUITBOX_JOYSTICK_HIGHLIGHT_LEN, "rb") };
    if (fruitbox_joystick_highlight_f == nullptr) error( "Failed to load fruitbox joystick highlight mem file");
    bitmap = al_load_bitmap_f(fruitbox_joystick_highlight_f, ".png");
    if (bitmap == nullptr) error( "Failed to load embedded joystick highlight bitmap");
    al_fclose(fruitbox_joystick_highlight_f);
  }
  else
  {
    bitmap = al_load_bitmap(bitmap_name.c_str());
    if (bitmap == nullptr) error( "Failed to load mouse pointer bitmap");
  }

  if (size.x.val == 0) ResetDynamic(size.x, sze.x.val); // if not specified, use size calculated from title strips
  if (size.y.val == 0) ResetDynamic(size.y, sze.y.val); // if not specified, use size calculated from title strips

  // InitDynamics();
  tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
}

void JoystickDisplayClass::draw(void)
{
  if (Config->skin_general->select_mode == select_mode_e::TouchSong) return; // don't draw joystick highlighter in touch song mode

  if (TitleStripDisplayClass::idle) // only draw if pages aren't moving
  {
    DisplayBaseClass::draw();
  }
}

