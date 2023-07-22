#include "property.h"
#include "builder.h"
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

bool Property::CanUpgrade(Builder* builder) const {
  //other builder owns this property already
  //may be this logic should be moved to the store
  if (owner && owner != builder) {
    return false;
  }
  return building->CanUpgrade();
}

void Property::Upgrade(Builder* builder) {
  owner = builder;
  building = building->GetUpgradedBuilding();
}

Property::Property(std::unique_ptr<Building> building) 
  : building(std::move(building)) {
  assert(building && "null building object");
} 

Property::~Property() {}
