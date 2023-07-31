#ifndef VACANT_ROAD_H
#define VACANT_ROAD_H

#include "road.h"

class VacantRoad : public Road {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;
  using Road::Road;
};
#endif
