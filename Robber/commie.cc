#include "commie.h"

using namespace std;

Inventory Commie::ApplyModifier(const Inventory& inventory) const {
  return inventory * 2;
}

explicit Commie::operator string() const {
	return "AOC";
}
