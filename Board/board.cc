#include "board.h"
#include "shop.h"
#include "Layout/layout.h"
#include "View/stream_view.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"
#include "../Dice/loaded_dice.h"
#include "../Dice/fair_dice.h"
#include "../Inventory/inventory.h"
#include <iostream>
#include <exception>
#include <utility>

using namespace std;

Board::Board()
  : layout(make_unique<Layout>()), shop(make_unique<Shop>()), view(make_unique<StreamView>(cout)) {
}

void Board::InitializeCommandMapping() {
  beginTurnCMD["load"] = bind(&Board::CommandLoad, this);
  beginTurnCMD["fair"] = bind(&Board::CommandFair, this);
  beginTurnCMD["roll"] = bind(&Board::CommandRoll, this);

  duringTurnCMD["board"] = bind(&Board::CommandBoard, this);
  duringTurnCMD["status"] = bind(&Board::CommandStatus, this);
  duringTurnCMD["residences"] = bind(&Board::CommandResidences, this);
  duringTurnCMD["build-road"] = bind(&Board::CommandBuildRoad, this);
  duringTurnCMD["build-res"] = bind(&Board::CommandBuildRes, this);
  duringTurnCMD["improve"] = bind(&Board::CommandImprove, this);
  duringTurnCMD["trade"] = bind(&Board::CommandTrade, this);
  duringTurnCMD["next"] = bind(&Board::CommandNext, this);
  duringTurnCMD["save"] = bind(&Board::CommandSave, this);
  duringTurnCMD["help"] = bind(&Board::CommandHelp, this);
}

void Board::Play() {
  while (true) {
    BeginGame();

    for (const int PLAYER_COUNT = layout->GetBuilders().size();; playerIndex = (playerIndex + 1)%PLAYER_COUNT) {
      BeginTurn();
      if (DuringTurn() == Code::END_STAGE) {
        break;
      }
    }

    if (EndOfGame() == Code::END_STAGE) {
      break;
    }
  }
}

void Board::BeginGame() {
  const auto& builders = layout->GetBuilders();
  for (playerIndex = 0; playerIndex < int(builders.size()); ++playerIndex) {
    auto& builder = builders[playerIndex];
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", builder->GetColour()));

    while (builder->OwnedResidenceCount() < 1) {
      NotifyAll("> ");
      CommandBuildRes();
    }
    CommandBoard();
  }

  for (playerIndex = int(builders.size()) - 1; playerIndex >= 0; --playerIndex) {
    auto& builder = builders[playerIndex];
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", builder->GetColour()));

    while (builder->OwnedResidenceCount() < 2) {
      NotifyAll("> ");
      CommandBuildRes();
    }
    CommandBoard();
  }
}

void Board::BeginTurn() {
  const auto& builder = layout->GetBuilder(playerIndex);
  NotifyAll(Format("Builder %v's turn.\n%v", builder->GetColour(), builder->GetStats()));

  while (true) {
    try {
      NotifyAll("> ");
      string cmd;
      cin >> cmd;
      if (beginTurnCMD[cmd]() == Code::END_STAGE) {
        break;
      }
    } catch (const bad_function_call& error) {
      NotifyAll("Invalid command.");
    } catch (const exception& error) {
      Assert(false, error.what());
    };
  }
}

Board::Code Board::DuringTurn() {
  while (true) {
    try {
      NotifyAll("> ");
      string cmd;
      cin >> cmd;
      Code retCode = duringTurnCMD[cmd]();
      if (HasWon()) {
        return Code::END_STAGE;
      }
      if (retCode == Code::END_STAGE) {
        break;
      }
    } catch (const bad_function_call& error) {
      NotifyAll("Invalid command.");
    } catch (const exception& error) {
      Assert(false, error.what());
    };
  }
  return Code::SUCCESS;
}

Board::Code Board::EndOfGame() {
  NotifyAll(Format("Builder %v has won!\n", layout->GetBuilder(playerIndex)->GetColour()));
  while (true) {
    NotifyAll("Would you like to play again? yes/no\n> ");
    string input; cin >> input;

    for_each(input.begin(), input.end(), [](char& c) {c = tolower(c);});
    if (input == "yes") {
      return Code::SUCCESS;
    } else if (input == "no") {
      return Code::END_STAGE;
    } else {
      NotifyAll("That wasn't yes or no.\n");
    }
  }
}

// BEGINNING OF TURN STAGE
Board::Code Board::CommandLoad() {
  NotifyAll("Input a roll between 2 and 12:\n");
  while (true) {
    NotifyAll("> ");
    int load;
    if ((cin >> load) && 2 <= load && load <= 12) {
      layout->GetBuilder(playerIndex)->SetDice(LoadedDice::dice[load]);
      break;
    }
    NotifyAll("Invalid roll.\n");
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandFair() {
  layout->GetBuilder(playerIndex)->SetDice(FairDice::dice);
  return Code::SUCCESS;
}

Board::Code Board::CommandRoll() {
  return Code::SUCCESS;
}


//DURING THE TURN
Board::Code Board::CommandBoard() {

}

Board::Code Board::CommandStatus() {
  for (const auto& builder : layout->GetBuilders()) {
    NotifyAll(builder->GetStats());
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandResidences() {
  NotifyAll(layout->GetBuilder(playerIndex)->GetResidences());
  return Code::SUCCESS;
}

Board::Code Board::CommandBuildRoad() {
  auto& builder = layout->GetBuilder(playerIndex);
  int roadIndex;
  if (!(cin >> roadIndex)) {
    roadIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }

  if (auto error = shop->BuildRoad(*builder, *layout, roadIndex); error) {
    NotifyAll(error.value());
  }

  return Code::SUCCESS;
}

Board::Code Board::CommandBuildRes() {
  auto& builder = layout->GetBuilder(playerIndex);
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }

  if (auto error = shop->BuildResidence(*builder, *layout, residenceIndex, builder->OwnedResidenceCount() < 2); error) {
    NotifyAll(error.value());
  }

  return Code::SUCCESS;
}

Board::Code Board::CommandImprove() {
  auto& builder = layout->GetBuilder(playerIndex);
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }

  if (auto error = shop->ImproveResidence(*builder, *layout, residenceIndex); error) {
    NotifyAll(error.value());
  }

  return Code::SUCCESS;
}

Board::Code Board::CommandTrade() {
  string colour, give, take;
  cin >> colour >> give >> take;

  //convert colour to camel case
  for_each(colour.begin(), colour.end(), [](char& c) { c = tolower(c); });
  colour[0] = toupper(colour[0]);

  //try to find the builder
  const auto& builders = layout->GetBuilders();
  int receiverIndex = distance(builders.begin(), find_if(builders.begin(), builders.end(), [&](const auto& b) {
    return b->GetColour() == colour;
  }));

  if (receiverIndex >= builders.size()) {
    NotifyAll("Can't trade with a non-existed builder!\n");
  }

  if (receiverIndex == playerIndex) {
    NotifyAll("Can't trade with yourself!\n");
  }

  //parse the trading offer
  Inventory trade = ParseResourceToInventory(give) + ParseResourceToInventory(take);
  if (trade.GetTotal() != 2) {
    NotifyAll("Invalid trade. It must contain two distinct types of resources.\n");
    return Code::SUCCESS;
  }

  NotifyAll(Format("%v offers %v one %v for one %v.\n Does %v accept this offer?\n", 
  builders[playerIndex]->GetColour(),
  builders[receiverIndex]->GetColour(),
  give, take, builders[receiverIndex]->GetColour()));

  NotifyAll("> ");
  string response;
  cin >> response;
  for_each(response.begin(), response.end(), [](char& c) { c = tolower(c); });
  if (response == "yes") {
    auto error = shop->Trade(*builders[playerIndex], *builders[receiverIndex], trade);
    if (error) {
      NotifyAll(error.value());
    }
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandNext() {
  return Code::END_STAGE;
}

Board::Code Board::CommandSave() {
  return Code::SUCCESS;
}

Board::Code Board::CommandHelp() {
  NotifyAll(
  string("Valid commands:\n") +
  "board\n" +
  "status\n" +
  "build-road <edge#>\n" +
  "build-res <housing#>\n" +
  "improve <housing#>\n" +
  "trade <colour> <give> <take>\n" +
  "next\n" +
  "save <file>\n" +
  "help\n");
  return Code::SUCCESS;
}

Inventory Board::ParseResourceToInventory(string resource) {
  static const map<string, Inventory> mp = {
    {"brick", Inventory{1, 0, 0, 0, 0}},
    {"energy", Inventory{0, 1, 0, 0, 0}},
    {"glass", Inventory{0, 0, 1, 0, 0}},
    {"heat", Inventory{0, 0, 0, 1, 0}},
    {"wifi", Inventory{0, 0, 0, 0, 1}},
  };

  for_each(resource.begin(), resource.end(), [](char& c) {c = tolower(c);});
  if (auto result = mp.find(resource); result != mp.end()) {
    return result->second;
  }
  return Inventory{0, 0, 0, 0, 0};
}

bool Board::HasWon() {
  return layout->GetBuilder(playerIndex)->GetVictoryPoints() >= 10;
}

void Board::Reset() {
  layout = make_unique<Layout>();
  //to do: generalize layout in a systematic way
}
