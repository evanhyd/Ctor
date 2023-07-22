#ifndef BUILDER_H
#define BUILDER_H 
#include <vector> 
#include <string>
#include "colour_enum.h"
#include "inventory.h"
   
class Dice; 

class Builder{
public: 
    Builder(ColourEnum colour, int victoryPoints); 
    virtual ~Builder() = 0; 
    int GetPoints(); 
    std::string GetStats(); 
    void UpdateVictoryPoints (int diff); 
    
    void TryBuildRes(int index); 
    void TryBuildRoad(int index); 
    void BuildRes(int index); 
    void BuildRoad(int index); 

    void TryBuyDevCard(int index); 

private: 
    ColourEnum colour;
    Inventory resources; 
    std::vector<int> roads; 
    std::vector<int> residences; 
    const Dice* dice;   
    int victoryPoints; 
};

#endif 
