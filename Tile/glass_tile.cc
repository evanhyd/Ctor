#include "glass_tile.h"

std::string GlassTile::GetTileType() const {
  return "GLASS";
}

Inventory GlassTile::GetResource() const {
  return Inventory(0, 0, 1, 0, 0);
}
