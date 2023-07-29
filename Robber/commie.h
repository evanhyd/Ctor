#ifndef COMMIE_H
#define COMMIE_H
#include "robber.h"

class Commie : public Robber {
  using Robber::Robber;

  virtual void MoveToImpl(int index) override;
  virtual explicit operator std::string() const override;
};
#endif
