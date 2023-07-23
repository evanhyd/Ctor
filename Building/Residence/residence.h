#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "BUilding/building.h"

class Inventory;

class Residence : public Building {
public:
  virtual int GetVictoryPoints() const = 0;
  virtual Inventory GenerateResource(Inventory inventory) const = 0;

  using Building::Building;
};
#endif
