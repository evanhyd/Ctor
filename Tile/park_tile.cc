#include "park_tile.h"

constexpr ParkTile::ParkTile(): Tile(7, Inventory(0, 0, 0, 0, 0)) {}

std::string ParkTile::GetTileType() const {
	return "PARK";
}
