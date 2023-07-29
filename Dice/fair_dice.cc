#include "fair_dice.h"
#include <random>
#include <chrono>

FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {  
  using namespace std;
  default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> dist(1, 6);
  return dist(engine) + dist(engine);
}

const FairDice FairDice::dice {};
