#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H
#include <memory>

class Tile;

class TileFactory {
public:
  enum Type : int {
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI,
    PARK,
    COUNT,
  };
  
  static std::unique_ptr<Tile> CreateTile(Type tileType, int tileNumber);
};

#endif
