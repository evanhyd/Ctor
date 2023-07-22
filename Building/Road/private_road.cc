#include "private_road.h"
#include <cassert>

Inventory PrivateRoad::GetUpgradeCost() const {
  assert(!("attempted to upgrade a private road"));
  return Inventory(0, 0, 0, 0, 0);
}

std::unique_ptr<Building> PrivateRoad::GetUpgradedBuilding() const {
  return nullptr;
}
