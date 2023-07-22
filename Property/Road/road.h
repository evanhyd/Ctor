#ifndef ROAD_H
#define ROAD_H
#include "property.h"

class Road : public Property {
public:
	Road(bool canUpgrade, Inventory upgradePrice, Builder* owner = nullptr);
	virtual ~Road();
};
#endif
