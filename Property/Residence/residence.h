#ifndef RESIDENCE_H
#define RESIDENCE_H
#include "property.h"
#include "observer.h"

class Tile;

class Residence : public Property, public Observer {
public:
	Residence(bool canUpgrade, Inventory upgradePrice, Builder* owner = nullptr);
	virtual ~Residence();

	virtual int Points() const = 0;

private:
	Tile* tile; //need a way to set the tile
};
#endif
