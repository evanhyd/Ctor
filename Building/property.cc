#include "property.h"
#include "builder.h"
#include "building.h"
#include "tile.h"
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

void Property::Notify() {

}

Property::Property(Tile* tile) : tile(tile) {
  assert(tile && "subscribing to a null subject!");
  tile->Attach(this);
} 

Property::~Property() {
  if (tile) {
    tile->Detach(this);
  }
}
