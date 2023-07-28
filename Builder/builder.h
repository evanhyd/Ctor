#ifndef BUILDER_H
#define BUILDER_H 
#include <vector> 
#include <string>
#include <map>
#include "colour_enum.h"
#include "../Inventory/inventory.h"
#include "../Building/property.h"
#include "../Building/residence_property.h"
   
class Dice; 

class Builder {
  ColourEnum colour;
  Inventory inventory;
  std::map<int, Property*> roads;
  std::map<int, ResidenceProperty*> residences;
  const Dice* dice;

public: 
  Inventory& GetInventory();
  const Inventory& GetInventory() const;
  int GetVictoryPoints() const;
  bool OwnRoad(int roadIndex) const; 
  bool OwnResidence(int residenceIndex) const; 
  void AddRoad(int index, Property& property);
  void AddResidence(int index, ResidenceProperty& property);
  std::string GetColour();
  std::string GetStats();
  
  explicit Builder(ColourEnum colour); 
  virtual ~Builder();
};

#endif 
