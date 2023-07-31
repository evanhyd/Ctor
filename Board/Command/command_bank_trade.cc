#include "command_bank_trade.h"
#include "../board.h"
#include "../shop.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include <string> 
#include <iostream>

using namespace std; 

Command::Code CommandBankTrade::operator()() {
  string give, take;
  cin >> give >> take;

  //parse the trading offer
  Inventory giveInventory = ParseResourceToInventory(give);
  Inventory takeInventory = ParseResourceToInventory(take);
  if (giveInventory.GetTotal() == 0  || takeInventory.GetTotal() == 0) {
    board.NotifyAll("Invalid resource type.\n");
    return Code::SUCCESS;
  }
  Inventory netInventory = 3 * giveInventory - takeInventory;

  if (give == take) {
    board.NotifyAll("Can't trade the same resource.\n");
    return Code::SUCCESS;
  }

  const auto& builders = board.GetLayout().GetBuilders();
  if (auto error = board.GetShop().BankTrade(*builders[board.GetPlayerIndex()], netInventory); error) {
    board.NotifyAll(error.value());
  } else {
    board.NotifyAll("Traded successfully\n");
  }
  return Code::SUCCESS;
}

Inventory CommandBankTrade::ParseResourceToInventory(string& resource) {
  static const map<string, Inventory> mapping = {
    {"brick", Inventory(1, 0, 0, 0, 0)},
    {"energy", Inventory(0, 1, 0, 0, 0)},
    {"glass", Inventory(0, 0, 1, 0, 0)},
    {"heat", Inventory(0, 0, 0, 1, 0)},
    {"wifi", Inventory(0, 0, 0, 0, 1)},
  };

  for_each(resource.begin(), resource.end(), [](char& c) {c = tolower(c);});
  if (auto result = mapping.find(resource); result != mapping.end()) {
    return result->second;
  }
  return Inventory{0, 0, 0, 0, 0};
}
