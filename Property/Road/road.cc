#include "road.h"

Road::Road(bool canUpgrade, Inventory upgradePrice, Builder* owner = nullptr) : Property(false, Inventory(0, 0, 0, 0, 0)) {}

Road::~Road() {}

