#include "vacant_land.h"
#include "basement.h"
#include "../../Utility/print.h"

Inventory VacantLand::GetUpgradeCost() const {
  return Inventory(1, 1, 1, 1, 0);
}

std::unique_ptr<Building> VacantLand::GetUpgradedBuilding() const {
  return std::make_unique<Basement>();
}

int VacantLand::GetVictoryPoints() const {
  Assert(false, "no one should owns vacant land");
  return 0;
}

Inventory VacantLand::GenerateResource(Inventory inventory) const {
  Assert(false, "vacant land attempts to generate resource");
  return Inventory(0, 0, 0, 0, 0);
}

