#include "basement.h"
#include "house.h"

Inventory Basement::GetUpgradeCost() const {
  return Inventory(0, 0, 2, 3, 0);
}

std::unique_ptr<Building> Basement::GetUpgradedBuilding() const {
  return std::make_unique<House>();
}

int Basement::GetVictoryPoints() const {
  return 1;
}

Inventory Basement::GenerateResource(Inventory inventory) const {
  return inventory;
}

Basement::operator std::string() const {
  return "Basement"; 
}

