#ifndef COMMAND_BOARD_H
#define COMMAND_BOARD_H

#include "command.h"

class CommandBoard : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
