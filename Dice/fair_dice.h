#ifndef FAIR_DICE_H
#define FAIR_DICE_H

#include "dice.h"
#include <random>

class FairDice : public Dice {

public:
  constexpr FairDice();

private:
  virtual int RollImpl() const override;
  static const std::default_random_engine ENGINE;

public:
  static const FairDice dice;
};

#endif
