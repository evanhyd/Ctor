#include "park_tile.h"
#include <cassert>

std::string ParkTile::GetTileType() const {
  return "PARK";
}

Inventory ParkTile::GetResource() const {
  assert(!("park trigerred resource distribution!"));
  return Inventory(0, 0, 0, 0, 0);
}
