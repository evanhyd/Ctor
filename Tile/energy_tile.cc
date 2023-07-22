#include "energy_tile.h"

std::string EnergyTile::GetTileType() const {
  return "ENERGY";
}

Inventory EnergyTile::GetResource() const {
  return Inventory(0, 1, 0, 0, 0);
}
