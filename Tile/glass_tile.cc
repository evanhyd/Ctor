#include "glass_tile.h"

constexpr GlassTile::GlassTile(int tileNum): Tile(tileNum, Inventory(0, 0, 1, 0, 0)) {}

std::string GlassTile::GetTileType() const {
	return "GLASS";
}
