#include "property.h"
#include "builder.h"

Property::Property(bool canUpgrade, Inventory upgradePrice, const Builder* owner) : canUpgrade(canUpgrade), upgradePrice(upgradePrice), owner(owner) {}

Property::~Property() {}

const Builder* Property::GetOwner() const {
	return owner;
}

