#ifndef SHOP_H
#define SHOP_H

#include "inventory.h"
#include "builder.h"

class Shop {
public:
	Shop();
	~Shop();
	bool BuildRoad(int index);
	bool BuildRes(int index);
	void ImproveRes(int index);
	bool Trade(Inventory& inv, ColorEnum color);
};
#endif
