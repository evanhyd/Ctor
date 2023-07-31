#ifndef COMMAND_STATUS_H
#define COMMAND_STATUS_H

#include "command.h"

class CommandStatus : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
