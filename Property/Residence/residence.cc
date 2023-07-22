#include "residence.h"
#include "tile.h"

Residence::Residence(bool canUpgrade, Inventory upgradePrice, Builder* owner) : Property(canUpgrade, upgradePrice, owner) {}

Residence::~Residence() {
	if (tile) {
		tile->Detach(this);
	}
}
