#ifndef TILE_H
#define TILE_H
#include <string>
#include "inventory.h"
#include "subject.h"

class Tile : public Subject {
public:
	constexpr Tile(int number, const Inventory& resource); 
	virtual ~Tile();
	virtual std::string GetTileType() const = 0;
	const int tileNum;
	const Inventory resource;
};
#endif
