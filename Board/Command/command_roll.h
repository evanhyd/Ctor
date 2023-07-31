#ifndef COMMAND_ROLL_H
#define COMMAND_ROLL_H

#include "command.h"

class CommandRoll : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;

  void DistributeResource(int tileNumber);
  void ActivateRobber();
};

#endif
