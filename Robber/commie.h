#ifndef COMMIE_H
#define COMMIE_H
#include "robber.h"
#include <string>

class Commie : public Robber {
  using Robber::Robber;

  virtual Inventory ApplyModifier(const Inventory& inventory) const = 0;
  virtual explicit operator std::string() const = 0;
};
#endif
