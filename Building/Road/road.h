#ifndef ROAD_H
#define ROAD_H

#include "../building.h"

class Road : public Building {
  //a transition class that's corresponds to Residence class
  //we can add interface here if we wanna add naughty features to roads related classes
  //for example, double GetDurability(), if it is <= 0.0, then the road crashes etc
  using Building::Building;
};
#endif
