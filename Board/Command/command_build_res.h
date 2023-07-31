#ifndef COMMAND_BUILD_RES_H
#define COMMAND_BUILD_RES_H

#include "command.h"

class CommandBuildRes : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
