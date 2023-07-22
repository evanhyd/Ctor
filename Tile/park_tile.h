#ifndef PARK_TILE_H
#define PARK_TILE_H
#include "tile.h"

class ParkTile : public Tile {
public:
	constexpr ParkTile();
	std::string GetTileType() const override;
};
#endif
