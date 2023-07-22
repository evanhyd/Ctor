#include "wifi_tile.h"

std::string WifiTile::GetTileType() const {
  return "WIFI";
}

Inventory WifiTile::GetResource() const {
  return Inventory(0, 0, 0, 0, 1);
}
