#ifndef FAIR_DICE_H
#define FAIR_DICE_H

#include "dice.h"

class FairDice : public Dice {
  virtual int RollImpl() const override;

public:
  explicit FairDice();  
  static const FairDice dice;
};

#endif
