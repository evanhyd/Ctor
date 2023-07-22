#include "inventory.h"
#include <cassert>

constexpr Inventory::Inventory(int brick, int energy, int glass, int heat, int wifi) 
  : resources{brick, energy, glass, heat, wifi} {
  assert((resources >= 0).min());
}

int Inventory::GetTotal() const {
  return resources.sum();
}

bool Inventory::CanAfford(const Inventory& cost) const {
  return (resources >= cost.resources).min();
}

bool Inventory::TrySpend(const Inventory& other) {
  const auto spent = resources - other.resources;
  const bool sufficient = spent.min() >= 0;
  if (sufficient) {
    resources = std::move(spent);
  }
  return sufficient;
}

Inventory& Inventory::Add(const Inventory& other) {
  resources += other.resources;
  return *this;
}

Inventory& Inventory::Multiply(int multiplier) {
  resources *= multiplier;
  return *this;
}

Inventory::operator std::string() const {
  using namespace std;
  return to_string(resources[0]) + " " + to_string(resources[1]) + " " + to_string(resources[2]) + " " + to_string(resources[3]) + " " + to_string(resources[4]);
}
