#ifndef GEESE_H
#define GEESE_H
#include "robber.h"
#include <string>

class Inventory;
class Builder;

class Geese : public Robber {
  using Robber::Robber;

  virtual void ApplyResourceModifier(Inventory& inventory) const override;
  virtual void ApplyBuilderModifier(Builder& builder) const override;
  virtual explicit operator std::string() const override;
};
#endif
