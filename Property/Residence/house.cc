#include "house.h"

House::House(Builder* builder): Residence(true, Inventory(0, 0, 2, 3, 0), builder) {}

int House::Points() const {
  return 2;
}
