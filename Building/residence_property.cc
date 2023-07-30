#include "residence_property.h"
#include "Residence/residence.h"
#include "../Builder/builder.h"
#include "../Tile/tile.h"
#include "../Utility/print.h"

using namespace std;

void ResidenceProperty::Notify(const Inventory& inventory) {
  //apply resources modifiers based on the building type
  const Inventory gained = static_cast<Residence*>(building.get())->GenerateResource(inventory);
  owner->GetInventory() += inventory;
}

int ResidenceProperty::GetVictoryPoints() const {
  return static_cast<Residence*>(building.get())->GetVictoryPoints();
}

ResidenceProperty::ResidenceProperty(std::unique_ptr<Building> building)
  : Property(std::move(building)), Observer() {
  Assert(dynamic_cast<Residence*>(this->building.get()) != nullptr, "building is not a property type");
}

ResidenceProperty::~ResidenceProperty() {}
