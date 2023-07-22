#include "private_road.h"

PrivateRoad::PrivateRoad(Builder* builder) : Road(false, Inventory(0, 0, 0, 0, 0), builder) {}

PrivateRoad::~PrivateRoad() {}
