#ifndef BUILDING_H
#define BUILDING_H

#include "../Inventory/inventory.h"
#include <memory>

class Building {
public:
  bool CanUpgradeToNextTier() const;
  virtual Inventory GetUpgradeCost() const = 0;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const = 0;
  
  explicit virtual operator std::string() const;
  explicit Building();
  virtual ~Building();
};

#endif
