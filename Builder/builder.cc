#include "builder.h"
#include "../Dice/fair_dice.h"
#include <cassert>

using namespace std;

Inventory& Builder::GetInventory() {
  return inventory;
}

int Builder::GetVictoryPoints() const {
  int points = 0;
  for (const auto& [_, property] : residences) {
    points  += property->GetVictoryPoints();
  }
  return points;
}

bool Builder::OwnRoad(int roadIndex) const {
  return roads.find(roadIndex) != roads.end();
}

bool Builder::OwnResidence(int residenceIndex) const {
  return residences.find(residenceIndex) != residences.end();
}

std::string Builder::GetColour() {
  switch(colour) {
    case ColourEnum::BLUE:
      return "Blue";
    case ColourEnum::RED:
      return "Red";
    case ColourEnum::ORANGE:
      return "Orange";
    case ColourEnum::YELLOW:
      return "Yellow";
    default:
      return "Invalid";
  }
}

Builder::Builder(ColourEnum colour)
  : colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  assert(dice && "dice is null");
}

Builder::~Builder() {}
