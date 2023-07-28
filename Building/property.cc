#include "property.h"
#include "../Builder/builder.h"
#include "building.h"
#include <cassert>

Builder* Property::GetOwner() {
  return owner;
}

const Builder* Property::GetOwner() const {
  return owner;
}

Inventory Property::GetUpgradeCost() {
  return building->GetUpgradeCost();
}

bool Property::CanUpgradeToNextTier() const {
  return building->CanUpgradeToNextTier();
}

void Property::Upgrade(Builder& builder) {
  owner = &builder;
  builder.GetInventory() -= building->GetUpgradeCost();
  building = building->GetUpgradedBuilding();
}

Property::Property(std::unique_ptr<Building> building) : building(std::move(building)) {
  assert(building && "null building object");
} 

Property::~Property() {}
