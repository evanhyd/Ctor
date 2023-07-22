#include "Builders/builder.h"
#include "fair_dice.h"

Builder::Builder(ColourEnum colour, int victoryPoints) : 
    colour{colour}, resources{0, 0, 0, 0, 0}, dice{&FairDice::dice}, victoryPoints{victoryPoints} {

}

int Builder::GetPoints(){
    return victoryPoints; 
}

void Builder::UpdateVictoryPoints(int diff){
    victoryPoints += diff; 
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
