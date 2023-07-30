#include "geese.h"
#include "../Inventory/inventory.h"
#include "../Builder/builder.h"

using namespace std;

void Geese::ApplyResourceModifier(Inventory& inventory) const {
  inventory = Inventory(0, 0, 0, 0, 0);
}

void Geese::ApplyBuilderModifier(Builder& builder) const {

}

Geese::operator string() const {
	return "GEESE";
}
