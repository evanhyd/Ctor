#include "fair_dice.h"
#include <chrono>

using namespace std;

constexpr FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {
  return ENGINE(uniform_int_distribution(1, 6)) + ENGINE(uniform_int_distribution(1, 6));
}

//seeding the engine when the application start
const default_random_engine FairDice::ENGINE{chrono::system_clock::now().time_since_epoch().count()};

const FairDice FairDice::dice {};
