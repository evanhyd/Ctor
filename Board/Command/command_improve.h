#ifndef COMMAND_IMPROVE_H
#define COMMAND_IMPROVE_H

#include "command.h"

class CommandImprove : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
