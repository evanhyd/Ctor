#ifndef WIFI_TILE_H
#define WIFI_TILE_H
#include "tile.h"

class WifiTile : public Tile {
public:
	constexpr WifiTile(int number);
	virtual std::string GetTileType() const override;
};
#endif
