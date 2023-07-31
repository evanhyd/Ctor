#ifndef COMMAND_HELP_H
#define COMMAND_HELP_H

#include "command.h"

class CommandHelp : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
