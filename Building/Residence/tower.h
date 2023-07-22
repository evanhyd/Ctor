#ifndef TOWER_H
#define TOWER_H

#include "residence.h"

class Tower : public Residence {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;
  virtual int GetVictoryPoints() const override;

  using Residence::Residence;
};
#endif
