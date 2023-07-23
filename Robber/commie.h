#ifndef COMMIE_H
#define COMMIE_H
#include "robber.h"

class Commie : public Robber {
  using Robber::Robber;

  virtual void MoveToImpl(int tileIndex) override;
};
#endif
