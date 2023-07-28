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
  int GetVictoryPoints() const;
  bool OwnRoad(int roadIndex) const; 
  bool OwnResidence(int residenceIndex) const; 
  std::string GetColour();
  std::string GetStats();
  
  explicit Builder(ColourEnum colour); 
  virtual ~Builder();
};

#endif 
