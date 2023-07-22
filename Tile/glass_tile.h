#ifndef GLASS_TILE_H
#define GLASS_TILE_H
#include "tile.h"

class GlassTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};
#endif
