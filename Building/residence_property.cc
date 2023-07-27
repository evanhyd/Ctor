#include "residence_property.h"
#include "Residence/residence.h"
#include "../Builder/builder.h"
#include "../Tile/tile.h"
#include <cassert>

void ResidenceProperty::Notify() {
  //reward the owner with resources
  const Inventory gained = static_cast<Residence*>(building.get())->GenerateResource(tile.GetResource());
  owner->GetInventory() += gained;
}

int ResidenceProperty::GetVictoryPoints() const {
  return static_cast<Residence*>(building.get())->GetVictoryPoints();
}

ResidenceProperty::ResidenceProperty(std::unique_ptr<Building> building, Tile& tile)
  : Property(std::move(building)), tile(tile) {
  assert(dynamic_cast<Residence*>(building.get()) && "building is not a property type");
  tile.Attach(this);
}

ResidenceProperty::~ResidenceProperty() {
  tile.Detach(this);
}
