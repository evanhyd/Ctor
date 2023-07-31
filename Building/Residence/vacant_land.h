#ifndef VACANT_LAND_H
#define VACANT_LAND_H

#include "residence.h"
#include <string>

class Builder;

class VacantLand : public Residence {
  virtual Inventory GetUpgradeCost() const override;
  virtual std::unique_ptr<Building> GetUpgradedBuilding() const override;
  virtual int GetVictoryPoints() const override;
  virtual Inventory GenerateResource(Inventory inventory) const override;

  using Residence::Residence;
};
#endif
