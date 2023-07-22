#ifndef PRIVATE_ROAD_H
#define PRIVATE_ROAD_H
#include "road.h"

class PrivateRoad : public Road {
public:
	PrivateRoad(Builder* builder);
	~PrivateRoad();
};
#endif
