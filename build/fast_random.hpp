#pragma once

#include <stdint.h>

namespace fast_random 
{
  void init(uint32_t seed);
  uint32_t rand(void);
}