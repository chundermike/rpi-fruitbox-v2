#include "fruitbox.hpp"
#include "fruitbox_mouse_pointer.hpp"

using namespace std;

void MouseDisplayClass::init
(
  const uint32_t emsk
)
{
  event_mask = emsk;

  if (bitmap_name.size() == 0) // no mouse graphic pointer specified, so use internal one...
  {
    ALLEGRO_FILE *fruitbox_mouse_pointer_f { al_open_memfile(fruitbox_mouse_pointer_data, FRUITBOX_MOUSE_POINTER_LEN, "rb") };
    if (fruitbox_mouse_pointer_f == nullptr) error( "Failed to load fruitbox mouse pointer mem file");
    bitmap = al_load_bitmap_f(fruitbox_mouse_pointer_f, ".png");
    if (bitmap == nullptr) error( "Failed to load embedded mouse pointer bitmap");
    offset = {2, 2}; // built in pointer hotspot is (nearly) top left
    al_fclose(fruitbox_mouse_pointer_f);
    ResetDynamic(size.y, Display->display_size.height / 16); // ...this is the built in font size, so make the mouse pointer the same height
    ResetDynamic(size.x, (2 * size.y.val) / 3); // ...mouse pointer width looks good if it's 2/3 as wide as the height
    // cout << "****** " << size.x.val << " " << size.y.val << endl;
  }
  else
  {
    bitmap = al_load_bitmap(bitmap_name.c_str());
    if (bitmap == nullptr) error( "Failed to load mouse pointer bitmap");
    if (size.x.val == 0) ResetDynamic(size.x, al_get_bitmap_width(bitmap)); // if not specified, use bitmap size
    if (size.y.val == 0) ResetDynamic(size.y, al_get_bitmap_height(bitmap)); // if not specified, use bitmap size
  }

  // InitDynamics();
  tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
}
