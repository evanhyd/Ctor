#ifndef COMMAND_NEXT_H
#define COMMAND_NEXT_H

#include "command.h"

class CommandNext : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
