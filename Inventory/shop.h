#ifndef SHOP_H
#define SHOP_H

#include "inventory.h"
#include "../Builder/builder.h"
#include "../Layout/layout.h"

#include <optional> 

class Shop {
public:
	Shop(Layout& layout);
	
	//should probably pass by a Builder reference.
	//you will need to get the builder reference later anyway
	//and to get the builder reference from ColorEnum, u will have to access the layout

	//that's why i suggest we pass the builder reference directly would be easier, so Shop doesn't need layout
	//but in CanBuildRoad, it has to check the layout again, this is complicated...
	void BuildRoad(int edgeIndex, ColourEnum player); 
	void BuildRes(int residenceIndex, ColourEnum player); 
	void ImproveRes(int residenceIndex);
	bool Trade(Inventory& inv, ColourEnum color);

private:

//just returning a bool tells us basically nothing.
//make this return std::optional<>, so we know the exact reason why it can't build
	
	std::optional<std::string> CanBuildRoad(int edgeIndex, ColourEnum player);
	std::optional<std::string> CanBuildRes(int residenceIndex, ColourEnum player);

	const Layout& layout; //then don't need this 
	
};
#endif
