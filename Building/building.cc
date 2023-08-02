#include "building.h"

bool Building::CanUpgradeToNextTier() const {
  return GetUpgradedBuilding() != nullptr;
}

Building::operator std::string() const {
  return " ";
}

Building::Building() {}

Building::~Building() {}
