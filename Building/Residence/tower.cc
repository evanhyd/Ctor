#include "tower.h"
#include <cassert>

Inventory Tower::GetUpgradeCost() const {
  assert(!("attempted to upgrade a tower"));
  return Inventory(0, 0, 0, 0, 0);
}

std::unique_ptr<Building> Tower::GetUpgradedBuilding() const {
  return nullptr;
}

int Tower::GetVictoryPoints() const {
  return 3;
}

Inventory Tower::GenerateResource(Inventory inventory) const {
  return inventory * 3;
}
