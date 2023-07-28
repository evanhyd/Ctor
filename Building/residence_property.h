#ifndef RESIDENCE_PROPERTY_H
#define RESIDENCE_PROPERTY_H

#include "property.h"
#include "../Observer/observer.h"
#include "../Inventory/inventory.h"

class ResidenceProperty : public Property, public Observer<Inventory> {
  virtual void Notify(const Inventory&) override;

public:
  int GetVictoryPoints() const;

  explicit ResidenceProperty(std::unique_ptr<Building> building);
  ~ResidenceProperty();
};

#endif
