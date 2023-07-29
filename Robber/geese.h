#ifndef GEESE_H
#define GEESE_H
#include "robber.h"

class Geese : public Robber {
  using Robber::Robber;

  virtual void MoveToImpl(int index) override;
  virtual explicit operator std::string() const override;

};
#endif
