#include "tower.h"
#include "../../Utility/print.h"

Inventory Tower::GetUpgradeCost() const {
  Assert(false, "attempted to upgrade a tower");
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

Tower::operator std::string() const {
  return "TOWER";
}
