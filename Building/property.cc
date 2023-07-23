#include "property.h"
#include "builder.h"
#include "building.h"
#include <cassert>

Builder& Property::GetOwner() {
  return *owner;
}

const Builder& Property::GetOwner() const {
  return *owner;
}

Inventory Property::GetUpgradeCost() {
  return building->GetUpgradeCost();
}

bool Property::CanUpgrade(Builder& builder) const {
  //purchsable if it is unowned or owned by the builder AND the builder can afford it
  return (!owner || owner == &builder) && building->CanUpgrade() && builder.GetInventory().CanAfford(building->GetUpgradeCost());
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
