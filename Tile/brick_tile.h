#ifndef BRICK_TILE_H
#define BRICK_TILE_H

#include "Tile/tile.h"

class BrickTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};
#endif
