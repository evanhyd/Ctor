#include "private_road.h"
#include "../../Utility/print.h"

Inventory PrivateRoad::GetUpgradeCost() const {
  Assert(false, "attempted to upgrade a private road");
  return Inventory(0, 0, 0, 0, 0);
}

std::unique_ptr<Building> PrivateRoad::GetUpgradedBuilding() const {
  return nullptr;
}
