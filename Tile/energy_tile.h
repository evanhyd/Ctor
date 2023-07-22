#ifndef ENERGY_TILE_H
#define ENERGY_TILE_H

#include "tile.h"

class EnergyTile : public Tile {
  virtual Inventory GetResource() const override;
	virtual std::string GetTileType() const override;

  using Tile::Tile;
};
#endif
