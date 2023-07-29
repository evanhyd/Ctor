#include "robber.h"

int Robber::GetTileIndex() const {
  return index;
}

void Robber::MoveTo(int tileIndex) {
  index = tileIndex;
  MoveToImpl(index);
}

Robber::Robber(int index) : index(index) {}

Robber::~Robber() {}

