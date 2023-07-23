#ifndef PROPERTY_H
#define PROPERTY_H

#include <memory>
#include "inventory.h"

class Builder;
class Building;

class Property {
protected:
  std::unique_ptr<Building> building;
  Builder* owner;

public:
  Builder& GetOwner();
  const Builder& GetOwner() const;

  Inventory GetUpgradeCost();
  bool CanUpgrade(Builder& builder) const;
  void Upgrade(Builder& builder);

  explicit Property(std::unique_ptr<Building> building);
  virtual ~Property();
};

#endif
