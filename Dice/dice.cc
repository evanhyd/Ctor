#include "dice.h"

int Dice::Roll() const {
  return RollImpl();
}

Dice::~Dice() {}
