#include "energy_tile.h"

constexpr EnergyTile::EnergyTile(int tileNum): Tile(tileNum, Inventory(0, 1, 0, 0, 0)) {}

std::string EnergyTile::GetTileType() const {
	return "ENERGY";
}
