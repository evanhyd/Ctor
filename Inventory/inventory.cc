#include "inventory.h"
#include "../Utility/print.h"

using namespace std;

Inventory::Inventory(int brick, int energy, int glass, int heat, int wifi) 
  : resources{brick, energy, glass, heat, wifi} {
  Assert((resources >= 0).min(), Format("negative inventory resources %v %v %v %v %v", brick, energy, glass, heat, wifi));
}

Inventory::Inventory(ResourceEnum::Type type, int count) : resources{0, 0, 0, 0, 0} {
  resources[type] += count; 
  Assert((count >= 0), Format("negative amount(%v) of %v resources", count, ResourceEnum::Name(type))); 
} 

int Inventory::GetResource(ResourceEnum::Type type) const {
  return resources[type];
}

int Inventory::GetTotal() const {
  return resources.sum();
}

bool Inventory::CanAfford(const Inventory& cost) const {
  return (resources >= cost.resources).min();
}

Inventory::Iterator Inventory::begin() {
  return Iterator(resources, 0);
}

Inventory::ConstIterator Inventory::begin() const {
  return ConstIterator(resources, 0);
}

Inventory::Iterator Inventory::end() {
  return Iterator(resources, int(resources.size()));
}

Inventory::ConstIterator Inventory::end() const {
  return ConstIterator(resources, int(resources.size()));
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

Inventory operator+(Inventory inv1, const Inventory& inv2) {
  inv1 += inv2;
  return inv1;
}

Inventory operator-(Inventory inv1, const Inventory& inv2) {
  inv1 -= inv2;
  return inv1;
}

Inventory operator*(Inventory inventory, int multiplier) {
  inventory *= multiplier;
  return inventory;
}

Inventory operator*(int multiplier, Inventory inventory) {
  inventory *= multiplier;
  return inventory;
}

bool operator==(const Inventory& inv1, const Inventory& inv2) {
  return (inv1.resources == inv2.resources).min() == true;
}

bool operator!=(const Inventory& inv1, const Inventory& inv2) {
  return !(inv1 == inv2);
}

Inventory::operator std::string() const {
  return Format("%v brick, %v energy, %v glass, %v heat, and %v WiFi", resources[0], resources[1], resources[2], resources[3], resources[4]); 
}
