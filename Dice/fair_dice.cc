#include "fair_dice.h"
#include <chrono>

constexpr FairDice::FairDice() : Dice() {}

int FairDice::RollImpl() const {  
  using namespace std;

  //seeding the engine when the application start
  static default_random_engine engine{chrono::system_clock::now().time_since_epoch().count()};
  static uniform_int_distribution<int> dist(1, 6);
  return dist(engine) + dist(engine);
}

const FairDice FairDice::dice {};
