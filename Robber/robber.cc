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

void Robber::LoadData(std::istream& file) {
  int robberIndex; 
  file >> robberIndex; 
  MoveToTile(robberIndex);
}

Robber::Robber(int index) : SaveLoadable(), index(index) {}

Robber::~Robber() {}
