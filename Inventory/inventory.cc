#include "inventory.h"
#include <cassert>
#include <string>
#include <map>

using namespace std;

Inventory::Inventory(int brick, int energy, int glass, int heat, int wifi) 
  : resources{brick, energy, glass, heat, wifi} {
  assert((resources >= 0).min());
}

int Inventory::GetTotal() const {
  return resources.sum();
}

bool Inventory::CanAfford(const Inventory& cost) const {
  return (resources >= cost.resources).min();
}

Inventory& Inventory::operator+=(const Inventory& other) {
  resources += other.resources;
  return *this;
}

Inventory& Inventory::operator-=(const Inventory& other) {
  resources -= other.resources;
  return *this;
}

Inventory& Inventory::operator*=(int mulitplier) {
  resources *= mulitplier;
  return *this;
}

Inventory operator*(Inventory inventory, int multiplier) {
  inventory *= multiplier;
  return inventory;
}

Inventory operator*(int multiplier, Inventory inventory) {
  inventory *= multiplier;
  return inventory;
}

Inventory::operator std::string() const {
  using namespace std;
  return to_string(resources[0]) + " " + to_string(resources[1]) + " " + to_string(resources[2]) + " " + to_string(resources[3]) + " " + to_string(resources[4]);
}
