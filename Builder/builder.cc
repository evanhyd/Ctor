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

bool Builder::CanAffordResidence(int residenceIndex){
  return inventory.CanAfford(residences[residenceIndex]->GetUpgradeCost()); 
}

bool Builder::CanAffordRoad(int roadIndex){
  return inventory.CanAfford(roads[roadIndex]]->GetUpgradeCost()); 
} 
  
void Builder::UpgradeResidence(int residenceIndex){
  residences[residenceIndex]->Upgrade(*this); 
}

void Builder::UpgradeRoad(int roadIndex){
  roads[roadIndex]->Upgrade(*this); 
}


std::string Builder::GetColour() {
  static const std::string COLOUR_NAMES[ColourEnum::COUNT] = {"Blue", "Red", "Orange", "Yellow"};
  return COLOUR_NAMES[colour];
}

std::string Builder::GetStats() {
  return "to do";
}

Builder::Builder(ColourEnum colour)
  : colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  assert(dice && "dice is null");
}

Builder::~Builder() {}
