#include "inventory.h"
#include <cassert>

constexpr Inventory::Inventory(int brick, int energy, int glass, int heat, int wifi) 
  : brick(brick), energy(energy), glass(glass), heat(heat), wifi(wifi) {
    assert(brick >= 0);
    assert(energy >= 0);
    assert(glass >= 0);
    assert(heat >= 0);
    assert(wifi >= 0);
}

int Inventory::GetTotal() const{
  return brick + energy + glass + heat + wifi;
}

bool Inventory::TrySpend(const Inventory& other) {
  if (brick < other.brick || energy < other.energy || glass < other.glass || heat < other.heat || wifi < other.wifi) {
    return false;
  }
  brick -= other.brick;
  energy -= other.energy;
  glass -= other.glass;
  heat -= other.heat;
  wifi -= other.wifi;
  return true;
}

void Inventory::Gain(const Inventory& other) {
  brick += other.brick;
  energy += other.energy;
  glass += other.glass;
  heat += other.heat;
  wifi += other.wifi;
}
