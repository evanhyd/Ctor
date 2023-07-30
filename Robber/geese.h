#ifndef GEESE_H
#define GEESE_H
#include "robber.h"
#include <string>

class Geese : public Robber {
  using Robber::Robber;

  virtual Inventory ApplyModifier(const Inventory& inventory) const = 0;
  virtual explicit operator std::string() const = 0;
};
#endif
