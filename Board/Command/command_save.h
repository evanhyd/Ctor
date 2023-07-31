#ifndef COMMAND_SAVE_H
#define COMMAND_SAVE_H

#include "command.h"

class CommandSave : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
