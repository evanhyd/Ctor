#include "Builder/builder.h"
#include "Dice/fair_dice.h"
#include <cassert>

using namespace std;

Inventory& Builder::GetInventory() {
  return inventory;
}

int Builder::GetVictoryPoints() {
  int points = 0;
  for (const auto& [_, property] : residences) {
    points  += property->GetVictoryPoints();
  }
  return points;
}

bool Builder::OwnRoad(int roadIndex) const {
  return roads.contains(roadIndex);
}

bool Builder::OwnResidence(int residenceIndex) const {
  return residence.contains(residenceIndex);
}


Builder::Builder(ColourEnum colour)
  : colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  assert(dice && "dice is null");
}

Builder::~Builder() {}
