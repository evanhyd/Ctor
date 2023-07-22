#include "vacant_road.h"
#include "private_road.h"

Inventory VacantRoad::GetUpgradeCost() const {
  return Inventory(0, 0, 0, 1, 1);
}

std::unique_ptr<Building> VacantRoad::GetUpgradedBuilding() const {
  return std::make_unique<PrivateRoad>();
}
