#include "residence_property.h"
#include "Residence/residence.h"
#include "tile.h"
#include <cassert>

void ResidenceProperty::Notify() {
  //reward the owner with resources
  Inventory gained = static_cast<Residence*>(building.get())->GenerateResource(tile->GetResource());

  /////////////////////////????????????????????
}

int ResidenceProperty::GetVictoryPoints() const {
  return static_cast<Residence*>(building.get())->GetVictoryPoints();
}

ResidenceProperty::ResidenceProperty(std::unique_ptr<Building> building, Tile* tile)
  : Property(std::move(building)), tile(tile) {
  assert(tile && "subscribing to a null subject!");
  tile->Attach(this);
}

ResidenceProperty::~ResidenceProperty() {
  if (tile) {
    tile->Detach(this);
  }
}
