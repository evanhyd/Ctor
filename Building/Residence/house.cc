#include "house.h"
#include "tower.h"

Inventory House::GetUpgradeCost() const {
  return Inventory(3, 2, 2, 2, 1);
}

std::unique_ptr<Building> House::GetUpgradedBuilding() const {
  return std::make_unique<Tower>();
}

int House::GetVictoryPoints() const {
  return 2;
}

Inventory House::GenerateResource(Inventory inventory) const {
  return inventory * 2;
}

House::operator std::string() const {
  return "HOUSE";
}
