#ifndef COMMAND_BANK_TRADE_H
#define COMMAND_BANK_TRADE_H
#include "command.h"
#include "../../Inventory/inventory.h"
#include <string>

class CommandBankTrade : public Command {
  using Command::Command;
  virtual Command::Code operator()() override;
  Inventory ParseResourceToInventory(std::string& resource);
};

#endif
