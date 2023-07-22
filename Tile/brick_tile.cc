#include "brick_tile.h"

std::string BrickTile::GetTileType() const {
  return "BRICK";
}

Inventory BrickTile::GetResource() const {
  return Inventory(1, 0, 0, 0, 0);
}
