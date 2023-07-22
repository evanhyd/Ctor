#ifndef FAIR_DICE_H
#define FAIR_DICE_H

#include "dice.h"
#include <random>

class FairDice : public Dice {
  virtual int RollImpl() const override;

public:
  explicit constexpr FairDice();
  
  static const FairDice dice;
};

#endif
