#include "commie.h"
#include "../Inventory/inventory.h"
#include "../Builder/builder.h"

using namespace std;

void Commie::ApplyResourceModifier(Inventory& inventory) const {
  inventory *= 2;
}

void Commie::ApplyBuilderModifier(Builder& builder) const {

}


Commie::operator string() const {
	return "AOC";
}
