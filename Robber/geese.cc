#include "geese.h"

using namespace std;

Inventory Geese::ApplyModifier(const Inventory& inventory) const {
  return Inventory(0, 0, 0, 0, 0);
}

Geese::operator string() const {
	return "GEESE";
}
