#ifndef BRICK_TILE_H
#define BRICK_TILE_H
#include "tile.h"

class BrickTile : public Tile {
public:
	constexpr BrickTile(int number);
	std::string GetTileType() const override;
};
#endif
