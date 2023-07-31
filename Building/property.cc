#include "property.h"
#include "building.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"
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
  building = building->GetUpgradedBuilding();
}

Property::operator string() const {
  return (owner ? ColourEnum::Name(owner->GetColour()).substr(0, 1) : "") + string(*building).substr(0, 1);
}

Property::Property(std::unique_ptr<Building> building)
  : building(std::move(building)), owner(nullptr) {
  Assert(this->building != nullptr, "null building object");
}

Property::~Property() {}
