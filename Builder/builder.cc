#include "builder.h"
#include "../Dice/fair_dice.h"
#include "../Dice/loaded_dice.h"
#include <cassert>
#include "../Utility/format.h"

using namespace std;

Inventory& Builder::GetInventory() {
  return inventory;
}

const Inventory& Builder::GetInventory() const {
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

void Builder::AddRoad(int index, Property& property) {
  assert(!roads.count(index));
  roads[index] = &property;
}

void Builder::AddResidence(int index, ResidenceProperty& property) {
  assert(!residences.count(index));
  residences[index] = &property;
}

int Builder::Roll(){
  return dice->Roll(); 
}

void Builder::SetDice(const Dice& newDice) {
  dice = &newDice;
}

string Builder::GetColour() const {
  static const string COLOUR_NAMES[ColourEnum::COUNT] = {"Blue", "Red", "Orange", "Yellow"};
  return COLOUR_NAMES[colour];
}

string Builder::GetStats() const {
  return Format("%v has %v building points, {}.", GetColour(), GetVictoryPoints(), string(inventory));
}

string Builder::GetBuildings() const {
  string buildings = GetColour() + " has built:\n"; 
  for(const auto& [index, property] : residences) {
    buildings += to_string(index) + ' ' + string(*(property))[1] + "\n"; 
  }
  return buildings; 
}

Builder::Builder(ColourEnum colour) : colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  assert(dice && "dice is null");
}

Builder::~Builder() {}
