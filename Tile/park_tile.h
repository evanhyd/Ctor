#ifndef PARK_TILE_H
#define PARK_TILE_H
#include "tile.h"

class ParkTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};
#endif
