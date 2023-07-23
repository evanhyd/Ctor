#ifndef RESIDENCE_PROPERTY_H
#define RESIDENCE_PROPERTY_H

#include "property.h"
#include "observer.h"

class Tile;

class ResidenceProperty : public Property, public Observer {
  Tile& tile;

  virtual void Notify() override;

public:
  int GetVictoryPoints() const;

  explicit ResidenceProperty(std::unique_ptr<Building> building, Tile& tile);
  ~ResidenceProperty();
};

#endif
