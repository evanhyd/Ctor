#include "building.h"

bool Building::CanBuild() const {
  return GetUpgradedBuilding() != nullptr;
}

Building::Building() {}

Building::~Building() {}
