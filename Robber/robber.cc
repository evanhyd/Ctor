#include "robber.h"

int Robber::GetTileIndex() const {
  return tileIndex;
}

void Robber::MoveTo(int tileIndex) {
  tileIndex = tileIndex;
  MoveToImpl(tileIndex);
}

Robber::Robber(int tileIndex) : tileIndex(tileIndex) {}

Robber::~Robber() {}
