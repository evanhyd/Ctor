#ifndef BUILDER_H
#define BUILDER_H 
#include <vector> 
#include <string>
#include "colour_enum.h"
#include "Inventory/inventory.h"
   
class Dice; 

class Builder{
  ColourEnum colour;
  Inventory inventory;
  std::vector<int> roads;
  std::vector<int> residences;
  const Dice* dice;

public: 
  Inventory& GetInventory();
  
  explicit Builder(ColourEnum colour); 
  virtual ~Builder();

















  int GetVictoryPoints() const;
  int GetPoints(); 
  std::string GetStats(); 

  
  void TryBuildRes(int index); 
  void TryBuildRoad(int index); 
  void BuildRes(int index); 
  void BuildRoad(int index); 

  void TryBuyDevCard(int index); 
};

#endif 
