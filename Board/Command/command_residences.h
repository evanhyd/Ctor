#ifndef COMMAND_RESIDENCES_H
#define COMMAND_RESIDENCES_H

#include "command.h"

class CommandResidences : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
