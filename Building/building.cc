#include "building.h"

bool Building::CanUpgradeToNextTier() const {
  return GetUpgradedBuilding() != nullptr;
}

Building::Building() {}

Building::~Building() {}
