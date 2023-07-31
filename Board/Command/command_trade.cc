#include "command_trade.h"
#include "../board.h"
#include "../shop.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include <string> 
#include <iostream>

using namespace std; 

Command::Code CommandTrade::operator()() {
  string colour, give, take;
  cin >> colour >> give >> take;

  //convert colour to camel case
  for_each(colour.begin(), colour.end(), [](char& c) { c = tolower(c); });
  colour[0] = toupper(colour[0]);

  //validate the builder
  const auto& builders = board.GetLayout().GetBuilders();
  int receiverIndex = distance(builders.begin(), find_if(builders.begin(), builders.end(), [&](const auto& b) {
    return ColourEnum::Name(b->GetColour()) == colour;
  }));

  if (receiverIndex < 0 || receiverIndex >= int(builders.size())) {
    board.NotifyAll("Can't trade with a non-existed builder!\n");
    return Code::SUCCESS;
  }

  if (receiverIndex == board.GetPlayerIndex()) {
    board.NotifyAll("Can't trade with yourself!\n");
    return Code::SUCCESS;
  }

  //parse the trading offer
  Inventory giveInventory = ParseResourceToInventory(give);
  Inventory takeInventory = ParseResourceToInventory(take);
  if (giveInventory.GetTotal() == 0  || takeInventory.GetTotal() == 0) {
    board.NotifyAll("Invalid resource type.\n");
    return Code::SUCCESS;
  }

  if (give == take) {
    board.NotifyAll("Can't trade the same resource.\n");
    return Code::SUCCESS;
  }

  board.NotifyAll(Format("%v offers %v one %v for one %v.\n Does %v accept this offer?\n", 
    ColourEnum::Name(builders[board.GetPlayerIndex()]->GetColour()),
    ColourEnum::Name(builders[receiverIndex]->GetColour()),
    give, take, ColourEnum::Name(builders[receiverIndex]->GetColour())));

  board.NotifyAll("> ");
  string response; cin >> response;
  for_each(response.begin(), response.end(), [](char& c) { c = tolower(c); });
  if (response == "yes") {
    if (auto error = board.GetShop().Trade(*builders[board.GetPlayerIndex()], *builders[receiverIndex], giveInventory, takeInventory); error) {
      board.NotifyAll(error.value());
    } else {
      board.NotifyAll("Traded successfully\n");
    }
  }
  return Code::SUCCESS;
}

Inventory CommandTrade::ParseResourceToInventory(string& resource) {
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
