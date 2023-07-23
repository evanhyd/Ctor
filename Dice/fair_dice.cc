#include "fair_dice.h"
#include "random.h"

constexpr FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {  
  return util::GetRandom(1, 6) + util::GetRandom(1, 6);
}

const FairDice FairDice::dice {};
