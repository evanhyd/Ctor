#ifndef LOADED_DICE_H
#define LOADED_DICE_H

#include "dice.h"

class LoadedDice : public Dice {
  int target;

  virtual int RollImpl() const override;

public:
  constexpr LoadedDice(int num);

  static const LoadedDice dice[13];
};

#endif
