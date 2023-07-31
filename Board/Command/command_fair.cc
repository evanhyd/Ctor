#include "command_fair.h"
#include "../board.h"
#include "../../Builder/builder.h"
#include "../../Dice/fair_dice.h"

Command::Code CommandFair::operator()() {
  board.CurrentBuilder().SetDice(FairDice::dice);
  return Code::SUCCESS;
}
