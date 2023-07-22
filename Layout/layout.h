#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>

class Tile;
class Road;
class Residence;
class Builder;
class Robber;

class Layout {
public: 
	Layout();
	
	virtual bool CanBuildRoad(int index) = 0;
	virtual bool CanBuildRes(int index) = 0;
	virtual bool BuildRoad(int index) = 0;
	virtual bool BuildRes(int index) = 0;
	virtual void MoveRobber(int index) = 0;

protected:
	std::vector<Tile*> tiles;
	std::vector<Road*> roads;
	std::vector<Residence*> residences;
	std::vector<Builder*> builders;
	std::unique_ptr<Robber> robber;
};
#endif
