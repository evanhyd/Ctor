#include "residence_property.h"
#include "Residence/residence.h"
#include "../Builder/builder.h"
#include "../Tile/tile.h"
#include <cassert>

void ResidenceProperty::Notify(const Inventory& inventory) {
  //reward the owner with resources
  const Inventory gained = static_cast<Residence*>(building.get())->GenerateResource(inventory);
  owner->GetInventory() += inventory;
}

int ResidenceProperty::GetVictoryPoints() const {
  return static_cast<Residence*>(building.get())->GetVictoryPoints();
}

ResidenceProperty::ResidenceProperty(std::unique_ptr<Building> building)
  : Property(std::move(building)), Observer() {
  assert(dynamic_cast<Residence*>(building.get()) && "building is not a property type");
}

ResidenceProperty::~ResidenceProperty() {}
