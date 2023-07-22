#ifndef PRIVATE_ROAD_H
#define PRIVATE_ROAD_H

#include "road.h"

class PrivateRoad : public Road {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;

  using Road::Road;
};
#endif
