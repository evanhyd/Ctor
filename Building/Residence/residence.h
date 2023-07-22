#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "building.h"

class Residence : public Building {
  virtual int GetVictoryPoints() const = 0;

  using Building::Building;
};
#endif
