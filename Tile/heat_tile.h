#ifndef HEAT_TILE_H
#define HEAT_TILE_H
#include "tile.h"

class HeatTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};
#endif
