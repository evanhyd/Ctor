#ifndef COMMAND_BUILD_ROAD_H
#define COMMAND_BUILD_ROAD_H

#include "command.h"

class CommandBuildRoad : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
};

#endif
