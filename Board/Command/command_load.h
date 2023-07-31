#ifndef COMMAND_LOAD_H
#define COMMAND_LOAD_H

#include "command.h"

class CommandLoad : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
