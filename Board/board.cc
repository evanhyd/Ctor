#include "board.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"
#include "../Dice/loaded_dice.h"
#include "../Dice/fair_dice.h"
#include "Command/command_load.h"
#include "Command/command_fair.h"
#include "Command/command_roll.h"
#include "Command/command_board.h"
#include "Command/command_status.h"
#include "Command/command_residences.h"
#include "Command/command_build_road.h"
#include "Command/command_build_res.h"
#include "Command/command_improve.h"
#include "Command/command_trade.h"
#include "Command/command_bank_trade.h"
#include "Command/command_next.h"
#include "Command/command_save.h"
#include "Command/command_help.h"

using namespace std;

Board::Board(bool enable_bank_trades) : enable_bank_trades(enable_bank_trades), playerIndex(0), layout(make_unique<Layout>()), shop(make_unique<Shop>()) {}

void Board::InitializeCommandMapping() {
  beginTurnCMD.insert({"load", make_unique<CommandLoad>(*this)});
  beginTurnCMD.insert({"fair", make_unique<CommandFair>(*this)});
  beginTurnCMD.insert({"roll", make_unique<CommandRoll>(*this)});

  duringTurnCMD.insert({"board", make_unique<CommandBoard>(*this)});
  duringTurnCMD.insert({"status", make_unique<CommandStatus>(*this)});
  duringTurnCMD.insert({"residences", make_unique<CommandResidences>(*this)});
  duringTurnCMD.insert({"build-road", make_unique<CommandBuildRoad>(*this)});
  duringTurnCMD.insert({"build-res", make_unique<CommandBuildRes>(*this)});
  duringTurnCMD.insert({"improve", make_unique<CommandImprove>(*this)});
  duringTurnCMD.insert({"trade", make_unique<CommandTrade>(*this)});
  duringTurnCMD.insert({"next", make_unique<CommandNext>(*this)}); 
  duringTurnCMD.insert({"save", make_unique<CommandSave>(*this)}); 
  duringTurnCMD.insert({"help", make_unique<CommandHelp>(*this)}); 
  if (enable_bank_trades) {
    duringTurnCMD.insert({"bank-trade", make_unique<CommandBankTrade>(*this)});
  }
}

Command::Code Board::ExecuteCommand(const Commands& commands, const std::string& cmd) {
  if (auto result = commands.find(cmd); result != commands.end()) {
    return (*result->second)();
  } else {
    NotifyAll("Invalid command.\n");
    return Command::Code::SUCCESS;
  }
}

void Board::Play() {
  InitializeCommandMapping();

  while (true) {
    layout->GenerateLayout(69420);

    //initial building
    BeginGame();

    //main game loop
    const int PLAYER_COUNT = layout->GetBuilders().size();
    constexpr bool P = false;
    constexpr bool NP = true;
    for (playerIndex = 0; P != NP ;playerIndex = (playerIndex + 1)%PLAYER_COUNT) {
      BeginTurn();
      if (!DuringTurn()) {
        break;
      }
    }

    //ending game
    if (!EndOfGame()) {
      break;
    }
    layout = make_unique<Layout>(); //reset the board
  }
}

void Board::BeginGame() {
  ExecuteCommand(duringTurnCMD, "board"); 

  const auto& builders = layout->GetBuilders();
  for (playerIndex = 0; playerIndex < int(builders.size()); ++playerIndex) {
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", ColourEnum::Name(CurrentBuilder().GetColour())));
    while (CurrentBuilder().OwnedResidenceCount() < 1) {
      NotifyAll("> ");
      ExecuteCommand(duringTurnCMD, "build-res");
    }
    ExecuteCommand(duringTurnCMD, "board"); 
  }

  for (playerIndex = int(builders.size()) - 1; playerIndex >= 0; --playerIndex) {
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", ColourEnum::Name(CurrentBuilder().GetColour())));
    while (CurrentBuilder().OwnedResidenceCount() < 2) {
      NotifyAll("> ");
      ExecuteCommand(duringTurnCMD, "build-res"); 
    }
    ExecuteCommand(duringTurnCMD, "board");
  }
}

void Board::BeginTurn() {
  ExecuteCommand(duringTurnCMD, "board");
  NotifyAll(Format("Builder %v's turn.\n%v", ColourEnum::Name(CurrentBuilder().GetColour()), CurrentBuilder().GetStats()));

  while (true) {
    NotifyAll("> ");
    string cmd; cin >> cmd;
    if (ExecuteCommand(beginTurnCMD, cmd) == Command::Code::END_STAGE) {
      break;
    }
  }
}

bool Board::DuringTurn() {
  while (true) {
    NotifyAll("> ");
    string cmd; cin >> cmd;
    auto code = ExecuteCommand(duringTurnCMD, cmd);
    if (HasWon()) {
      return false;
    }
    if (code == Command::Code::END_STAGE) {
      return true;
    }
  }
}

bool Board::EndOfGame() {
  NotifyAll(Format("Builder %v has won!\n", ColourEnum::Name(CurrentBuilder().GetColour())));
  while (true) {
    NotifyAll("Would you like to play again? yes/no\n> ");
    string input; cin >> input;
    for_each(input.begin(), input.end(), [](char& c) {c = tolower(c);});
    if (input == "yes") {
      return true;
    } else if (input == "no") {
      return false;
    }
  }
}

bool Board::HasWon() {
  return CurrentBuilder().GetVictoryPoints() >= 10;
}

Builder& Board::CurrentBuilder() {
  Assert(0 <= playerIndex && playerIndex < int(layout->GetBuilders().size()), Format("invalid builder index %v", playerIndex));
  return *layout->GetBuilders()[playerIndex];
}

Layout& Board::GetLayout() {
  return *layout;
}

Shop& Board::GetShop() {
  return *shop;
}

int Board::GetPlayerIndex(){
  return playerIndex; 
} 

std::string Board::SaveData() const {
  return Format("%v\n%v\n", to_string(playerIndex), layout->SaveData()); 
} 

SaveLoadable::Error Board::LoadData(const std::string& data) {
  return {};
}

void Board::ImportBoard() {

}
