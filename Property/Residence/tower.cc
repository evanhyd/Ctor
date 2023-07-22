#include "tower.h"

Tower::Tower(Builder* builder): Residence(true, Inventory(3, 2, 2, 2, 1), builder) {}

int Tower::Points() const {
  return 3;
}
