#include "vacant_land.h"
#include "basement.h"
#include <cassert>

Inventory VacantLand::GetUpgradeCost() const {
  return Inventory(1, 1, 1, 1, 0);
}

std::unique_ptr<Building> VacantLand::GetUpgradedBuilding() const {
  return std::make_unique<Basement>();
}

int VacantLand::GetVictoryPoints() const {
  assert(!("no one should owns vacant land"));
  return 0;
}
