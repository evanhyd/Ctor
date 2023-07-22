#ifndef BUILDING_H
#define BUILDING_H

#include "inventory.h"
#include <memory>

class Building {
public:
  bool CanUpgrade() const;
  virtual Inventory GetUpgradeCost() const = 0;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const = 0;

  Building();
  virtual ~Building();
};

#endif
