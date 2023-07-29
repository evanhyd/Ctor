#include "park_tile.h"
#include "../Utility/print.h"

std::string ParkTile::GetTileType() const {
  return "PARK";
}

Inventory ParkTile::GetResource() const {
  Assert(false, "park trigerred resource distribution!");
  return Inventory(0, 0, 0, 0, 0);
}
