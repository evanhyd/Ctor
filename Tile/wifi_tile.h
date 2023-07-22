#ifndef WIFI_TILE_H
#define WIFI_TILE_H

#include "tile.h"

class WifiTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};

#endif
