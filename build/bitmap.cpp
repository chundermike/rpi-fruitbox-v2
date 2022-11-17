#include "fruitbox.hpp"

using namespace std;

void BitmapDisplayClass::init
(
  const dynamics2_t sze,
  const uint32_t emsk
)
{
  DisplayBaseClass::init(size, emsk, bitmap_name); // use objects size (from reading config file)
}
