#ifndef COMMAND_FAIR_H
#define COMMAND_FAIR_H

#include "command.h"

class CommandFair : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
