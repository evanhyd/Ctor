#ifndef PROPERTY_H
#define PROPERTY_H

#include <memory>
#include "observer.h"
#include "inventory.h"

class Builder;
class Building;
class Tile;

class Property : public Observer {
  Builder* owner;
  Tile* tile;
  std::unique_ptr<Building> building;

public:
  Builder* GetOwner();
  const Builder* GetOwner() const;

  Inventory GetUpgradeCost();
  bool CanUpgrade(Builder* builder) const;
  void Upgrade(Builder* builder);

  virtual void Notify() override;

  Property(Tile* tile);
  ~Property();
};

#endif
