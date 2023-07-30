#ifndef COMMIE_H
#define COMMIE_H
#include "robber.h"
#include <string>

class Inventory;
class Builder;

class Commie : public Robber {
  using Robber::Robber;

  virtual void ApplyResourceModifier(Inventory& inventory) const override;
  virtual void ApplyBuilderModifier(Builder& builder) const override;
  virtual explicit operator std::string() const override;
};
#endif
