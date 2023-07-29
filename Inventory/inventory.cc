#include "inventory.h"
#include <cassert>
#include <string>
#include <map>
#include <format>

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

Inventory& Inventory::operator*=(int multiplier) {
  resources *= multiplier;
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
  return format("{} brick, {}, energy, {} glass, {} heat, and {} WiFi", resources[0], resources[1], resources[2], resources[3], resources[4]); 
}
