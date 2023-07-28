#include "fair_dice.h"
#include "../Utility/random.h"

FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {  
  return Random::GetRandom(1, 6) + Random::GetRandom(1, 6);
}

const FairDice FairDice::dice {};
