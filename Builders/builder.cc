#include "builder.h"
#include "fair_dice.h"
#include <cassert>

Inventory& Builder::GetInventory() {
  return inventory;
}

Builder::Builder(ColourEnum colour)
  : colour(colour), inventory(0, 0, 0, 0, 0), dice{&FairDice::dice} {
  assert(dice && "dice is null");
}

Builder::~Builder() {}













int Builder::GetPoints(){
  return 0; 
}

void Builder::TryBuildRes(int index){
    //todo: 
}

void Builder::TryBuildRoad(int index){
    //todo: 
}

void Builder::BuildRes(int index){
    //todo: perhaps append/change residence vector 
}

void Builder::TryBuyDevCard(int index){
    //todo: perhaps check if you can through inventory resources 
}
