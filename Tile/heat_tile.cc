#include "heat_tile.h"

std::string HeatTile::GetTileType() const {
  return "HEAT";
}

Inventory HeatTile::GetResource() const {
  return Inventory(0, 0, 0, 1, 0);
}
