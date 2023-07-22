#include "wifi_tile.h"

constexpr WifiTile::WifiTile(int number) : Tile(number, Inventory(0, 0, 0, 0, 1)) {}

std::string WifiTile::GetTileType() const {
  return "WIFI";
}
