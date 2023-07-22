#ifndef ENERGY_TILE_H
#define ENERGY_TILE_H

#include "tile.h"

class EnergyTile : public Tile {
public:
	constexpr EnergyTile(int number);
	std::string GetTileType() const override;
};
#endif
