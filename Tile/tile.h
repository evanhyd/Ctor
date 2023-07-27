#ifndef TILE_H
#define TILE_H

#include <string>
#include "../Observer/subject.h"
#include "../Inventory/inventory.h"

class Tile : public Subject {
protected:
	const int number;

public:
  int GetNumber() const;
  virtual Inventory GetResource() const = 0;
	virtual std::string GetTileType() const = 0;

  explicit operator std::string() const;
  
	explicit constexpr Tile(int tileNumber); 
	virtual ~Tile();
};
#endif
