#include "tile.h"

int Tile::GetNumber() const {
  return number;
}

Tile::operator std::string() const {
  return GetTileType() + " " + std::to_string(number);
}

Tile::Tile(int tileNumber) : Subject(), number(tileNumber) {}

Tile::~Tile() {}
