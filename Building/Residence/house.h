#ifndef HOUSE_H
#define HOUSE_H

#include "residence.h"

class House : public Residence {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;
  virtual int GetVictoryPoints() const override;
  virtual Inventory GenerateResource(Inventory inventory) const override;
  
  using Residence::Residence;
};
#endif
