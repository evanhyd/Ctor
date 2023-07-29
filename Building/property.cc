#include "property.h"
#include "../Builder/builder.h"
#include "building.h"
#include <cassert>
#include <string>

using namespace std;

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

Property::operator string() const {
  return (owner ? owner->GetColour().substr(0, 1) : "") + string(*building).substr(0, 1);
}

Property::Property(std::unique_ptr<Building> building) : building(std::move(building)) {
  assert(this->building && "null building object");
}

Property::~Property() {}
