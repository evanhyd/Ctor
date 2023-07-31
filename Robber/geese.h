#ifndef GEESE_H
#define GEESE_H
#include "robber.h"
#include <string>

class Inventory;
class Builder;

class Geese : public Robber {
  using Robber::Robber;
  Inventory CalculateStolenInventory(const Inventory& inventory) const; 
  virtual void ApplyResourceModifier(Inventory& inventory) const override;
	virtual void ApplyBoardModifier(Board& board) const override;
  virtual explicit operator std::string() const override;

  constexpr int RESOURCE_LIMIT = 10;
};
#endif
