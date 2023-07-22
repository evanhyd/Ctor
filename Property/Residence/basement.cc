#include "basement.h"

Basement::Basement(Builder* builder): Residence(true, Inventory(1, 1, 1, 0, 1), builder) {}

int Basement::Points() const {
  return 1;
}
