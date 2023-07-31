#include "robber.h"

using namespace std; 

int Robber::GetTileIndex() const {
  return index;
}

void Robber::MoveToTile(int tileIndex) {
  index = tileIndex;
}

string Robber::SaveData() const {
  return to_string(index);
}

SaveLoadable::Error LoadData(const std::string& data) {
  return {};
}

Robber::Robber(int index) : SaveLoadable(), index(index) {}

Robber::~Robber() {}
