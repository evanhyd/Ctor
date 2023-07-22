#include "heat_tile.h"

constexpr HeatTile::HeatTile(int tileNum): Tile(tileNum, Inventory(0, 0, 0, 1, 0)) {}

std::string HeatTile::GetTileType() const {
	return "HEAT";
}
