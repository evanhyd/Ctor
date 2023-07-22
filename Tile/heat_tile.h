#ifndef HEAT_TILE_H
#define HEAT_TILE_H
#include "tile.h"

class HeatTile : public Tile {
public:
	constexpr HeatTile(int number);
	std::string GetTileType() const override;
};
#endif
