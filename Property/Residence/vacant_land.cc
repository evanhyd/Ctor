#include "vacant_land.h"
#include "builder.h"

VacantLand::VacantLand(Builder* builder): Residence(true, Inventory(1, 1, 1, 1, 0), builder) {}

int VacantLand::Points() const {
  return 0;
}
