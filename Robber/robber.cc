#include "robber.h"

int Robber::GetTileIndex() const {
  return index;
}

void Robber::MoveToTile(int tileIndex) {
  index = tileIndex;
}

Robber::Robber(int index) : index(index) {}

Robber::~Robber() {}
