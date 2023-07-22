#ifndef PROPERTY_H
#define PROPERTY_H
#include "inventory.h"

class Builder;

class Property {
public:
	Property(bool canUpgrade, Inventory upgradePrice, const Builder* owner = nullptr);
	virtual ~Property();
  
	const Builder* GetOwner() const;
	const bool canUpgrade;
	const Inventory upgradePrice;
protected:
	const Builder* owner;
};

#endif
