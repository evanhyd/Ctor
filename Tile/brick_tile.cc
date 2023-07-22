#include "brick_tile.h"

constexpr BrickTile::BrickTile(int tileNum): Tile(tileNum, Inventory(1, 0, 0, 0, 0)) {}

std::string BrickTile::GetTileType() const {
	return "BRICK";
}
