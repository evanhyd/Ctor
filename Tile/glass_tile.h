#ifndef GLASS_TILE_H
#define GLASS_TILE_H
#include "tile.h"

class GlassTile : public Tile {
public:
	constexpr GlassTile(int number);
	std::string GetTileType() const override;
};
#endif
