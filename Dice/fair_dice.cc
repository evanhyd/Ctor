#include "fair_dice.h"
#include "../Utility/random.h"

constexpr FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {  
  // return Random::GetRandom(1, 6) + Random::GetRandom(1, 6);
  // Evan said he would fix this -- Zac
  return 1;
}

const FairDice FairDice::dice {};
