#include "builder.h"
#include "../Dice/fair_dice.h"
#include "../Dice/loaded_dice.h"
#include "../Utility/print.h"

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
  Assert(!roads.count(index), Format("duplicated road index %v", index));
  roads.insert({index, &property});
}

void Builder::AddResidence(int index, ResidenceProperty& property) {
  Assert(!residences.count(index), Format("duplicated residence index %v", index));
  residences.insert({index, &property});
}

int Builder::OwnedRoadCount() const {
  return roads.size();
}

int Builder::OwnedResidenceCount() const {
  return residences.size();
}

int Builder::Roll(){
  return dice->Roll(); 
}

void Builder::SetDice(const Dice& newDice) {
  dice = &newDice;
}

ColourEnum::Type Builder::GetColour() const {
  return colour;
}

string Builder::GetStats() const {
  return Format("%v has %v building points, %v.\n", ColourEnum::Name(GetColour()), GetVictoryPoints(), string(inventory));
}

string Builder::GetResidences() const {
  string buildings = ColourEnum::Name(GetColour()) + " has built:\n"; 
  for(const auto& [index, residence] : residences) {
    buildings += Format("%v %v\n", index, string(*residence)[1]);
  }
  return buildings; 
}

string Builder::SaveData() const {
  string saveData; 
  //save data from inventory
  for (const auto& [_, count] : inventory) {
    saveData += to_string(count) + ' ';
  }

  //save data for roads 
  saveData += "r "; 
  for(const auto& [index, _] : roads) {
    saveData += to_string(index) + " "; 
  }

  //save data for residences
  saveData += "h "; 
  for(const auto& [index, residence] : residences) {
    saveData += Format("%v %v ", index, string(*residence)[1]); 
  }
  return saveData; 
}

SaveLoadable::Error Builder::LoadData(const string& data) {
  return {};
}

Builder::Builder(ColourEnum::Type colour)
  : SaveLoadable(), colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  Assert(dice, "dice is null");
}

Builder::~Builder() {}
