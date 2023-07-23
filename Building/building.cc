#include "building.h"

bool Building::CanUpgrade() const {
  return GetUpgradedBuilding() != nullptr;
}

Building::Building() {}

Building::~Building() {}
