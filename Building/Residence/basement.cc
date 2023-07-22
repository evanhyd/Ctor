#include "basement.h"
#include "house.h"

Inventory House::GetUpgradeCost() const {
  return Inventory(0, 0, 2, 3, 0);
}

std::unique_ptr<Building> House::GetUpgradedBuilding() const {
  return std::make_unique<House>();
}

int House::GetVictoryPoints() const {
  return 1;
}
