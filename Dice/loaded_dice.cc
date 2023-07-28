#include "loaded_dice.h"

int LoadedDice::RollImpl() const {
  return target;
}

LoadedDice::LoadedDice(int num) : Dice(), target(num) {}

const LoadedDice LoadedDice::dice[13] = {
  LoadedDice(0),
  LoadedDice(1),
  LoadedDice(2),
  LoadedDice(3),
  LoadedDice(4),
  LoadedDice(5),
  LoadedDice(6),
  LoadedDice(7),
  LoadedDice(8),
  LoadedDice(9),
  LoadedDice(10),
  LoadedDice(11),
  LoadedDice(12),
};
