#ifndef BASEMENT_H
#define BASEMENT_H

#include "residence.h"

class Basement : public Residence {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;
  virtual int GetVictoryPoints() const override;
  virtual Inventory GenerateResource(Inventory inventory) const override;

  using Residence::Residence;
};
#endif
