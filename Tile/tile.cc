#include "tile.h"

constexpr Tile::Tile(int tileNum, const Inventory& resource) : tileNum{tileNum}, resource(resource) {}

Tile::~Tile() {}
