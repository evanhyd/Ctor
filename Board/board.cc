#include "board.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"
#include "../Dice/loaded_dice.h"
#include "../Dice/fair_dice.h"
#include <exception>
#include <utility>

using namespace std;

Board::Board() : layout(make_unique<Layout>()), shop(make_unique<Shop>()) {}

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

Builder& Board::CurrentBuilder() {
  return *layout->GetBuilders()[playerIndex];
}

void Board::ImportBoard() {

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
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", ColourEnum::Name(CurrentBuilder().GetColour())));

    while (CurrentBuilder().OwnedResidenceCount() < 1) {
      NotifyAll("> ");
      CommandBuildRes();
    }
    CommandBoard();
  }

  for (playerIndex = int(builders.size()) - 1; playerIndex >= 0; --playerIndex) {
    NotifyAll(Format("Builder %v, where do you want to build a basement?\n", ColourEnum::Name(CurrentBuilder().GetColour())));

    while (CurrentBuilder().OwnedResidenceCount() < 2) {
      NotifyAll("> ");
      CommandBuildRes();
    }
    CommandBoard();
  }
}

void Board::BeginTurn() {
  NotifyAll(Format("Builder %v's turn.\n%v", ColourEnum::Name(CurrentBuilder().GetColour()), CurrentBuilder().GetStats()));

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
  NotifyAll(Format("Builder %v has won!\n", ColourEnum::Name(CurrentBuilder().GetColour())));
  while (true) {
    NotifyAll("Would you like to play again? yes/no\n> ");
    string input; cin >> input;

    for_each(input.begin(), input.end(), [](char& c) {c = tolower(c);});
    if (input == "yes") {
      return Code::SUCCESS;
    } else if (input == "no") {
      return Code::END_STAGE;
    }
  }
}

// BEGINNING OF TURN STAGE
Board::Code Board::CommandLoad() {
  while (true) {
    NotifyAll("Input a roll between 2 and 12: ");
    int load;
    if ((cin >> load) && 2 <= load && load <= 12) {
      CurrentBuilder().SetDice(LoadedDice::dice[load]);
      break;
    }
    cin.ignore('\n');
    cin.clear();
    NotifyAll("Invalid roll.\n");
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandFair() {
  CurrentBuilder().SetDice(FairDice::dice);
  return Code::SUCCESS;
}

Board::Code Board::CommandRoll() {
  auto& tiles = layout->GetTiles();
  const int tileNumber = CurrentBuilder().Roll();

  constexpr int ROBBER_TILE_NUMBER = 7;
  if (tileNumber != ROBBER_TILE_NUMBER) {
    DistributeResource(tileNumber);
  } else {
    ActivateRobber();
  }

  return Code::END_STAGE;
}


//DURING THE TURN
Board::Code Board::CommandBoard() {
  NotifyAll("D====>");
  return Code::SUCCESS;
}

Board::Code Board::CommandStatus() {
  for (const auto& builder : layout->GetBuilders()) {
    NotifyAll(builder->GetStats());
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandResidences() {
  NotifyAll(CurrentBuilder().GetResidences());
  return Code::SUCCESS;
}

Board::Code Board::CommandBuildRoad() {
  int roadIndex;
  if (!(cin >> roadIndex)) {
    roadIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }
  if (auto error = shop->BuildRoad(CurrentBuilder(), *layout, roadIndex); error) {
    NotifyAll(error.value());
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandBuildRes() {
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }
  if (auto error = shop->BuildResidence(CurrentBuilder(), *layout, residenceIndex, CurrentBuilder().OwnedResidenceCount() < 2); error) {
    NotifyAll(error.value());
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandImprove() {
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore('\n');
    cin.clear();
  }
  if (auto error = shop->ImproveResidence(CurrentBuilder(), *layout, residenceIndex); error) {
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

  //validate the builder
  const auto& builders = layout->GetBuilders();
  int receiverIndex = distance(builders.begin(), find_if(builders.begin(), builders.end(), [&](const auto& b) {
    return ColourEnum::Name(b->GetColour()) == colour;
  }));

  if (receiverIndex < 0 || receiverIndex >= int(builders.size())) {
    NotifyAll("Can't trade with a non-existed builder!\n");
    return Code::SUCCESS;
  }

  if (receiverIndex == playerIndex) {
    NotifyAll("Can't trade with yourself!\n");
    return Code::SUCCESS;
  }

  //parse the trading offer
  Inventory trade = ParseResourceToInventory(give) + ParseResourceToInventory(take);
  if (trade.GetTotal() != 2) {
    NotifyAll("Invalid trade. It must contain two distinct types of resources.\n");
    return Code::SUCCESS;
  }

  NotifyAll(Format("%v offers %v one %v for one %v.\n Does %v accept this offer?\n", 
    ColourEnum::Name(builders[playerIndex]->GetColour()),
    ColourEnum::Name(builders[receiverIndex]->GetColour()),
    give, take, ColourEnum::Name(builders[receiverIndex]->GetColour())));

  NotifyAll("> ");
  string response;
  cin >> response;
  for_each(response.begin(), response.end(), [](char& c) { c = tolower(c); });
  if (response == "yes") {
    if (auto error = shop->Trade(*builders[playerIndex], *builders[receiverIndex], trade); error) {
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




// HELPER FUNCTION
void Board::DistributeResource(int tileNumber) {
  const auto& builders = layout->GetBuilders();
  const auto& tiles = layout->GetTiles();
  const auto& robber = layout->GetRobber();

  //record the old resources
  vector<Inventory> oldInventories;
  for (const auto& builder : builders) {
    oldInventories.push_back(builder->GetInventory());
  }

  //activate resources distribution
  for (int i = 0; i < int(tiles.size()); ++i) {
    if (tiles[i]->GetNumber() == tileNumber) {
      Inventory resource = tiles[i]->GetResource();

      //apply resource modifier if the robber is on it
      if (robber.GetTileIndex() == i) {
        robber.ApplyResourceModifier(resource);
      }
      tiles[i]->NotifyAll(resource);
    }
  }

  //calculate the gained separately.
  //there can be mulitple residences near the same tile belongs to one builder.
  //therefore it is not reliable to report the resource through the obserer.
  bool hasGained = false;
  for (int i = 0; i < int(builders.size()); ++i) {
    if (Inventory difference = builders[i]->GetInventory() - oldInventories[i]; difference.GetTotal() != 0) {
      hasGained = true;

      //generate gained information
      string gained = Format("Builder %v gained:\n", ColourEnum::Name(builders[i]->GetColour()));
      for (int type = ResourceEnum::Type::BRICK; type < ResourceEnum::COUNT; ++type) {
        ResourceEnum::Type v = ResourceEnum::Type(type);
        if (difference.GetResource(v) != 0) {
          gained += Format("%v %v\n", difference.GetResource(v), ResourceEnum::Name(v));
        }
      }
      NotifyAll(gained);
    }
  }

  if (!hasGained) {
    NotifyAll("No builders gained resources.");
  }
}

void Board::ActivateRobber() {
  //todo 
  layout->GetRobber().ApplyBuilderModifier(layout->GetBuilders(), CurrentBuilder());
  //how do we notify 


  //prompting builder for new 
  NotifyAll(Format("Choose where to place the %v\n", string(layout->GetRobber()))); 
  int newRobberPosition;
  cin >> newRobberPosition; 

  if(newRobberPosition == layout->GetRobber().GetTileIndex()){
    return; 
  }

  


  //code for placing moving the robber 
  //some robber moveto functionality 
}

Inventory Board::ParseResourceToInventory(string resource) {
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

bool Board::HasWon() {
  return CurrentBuilder().GetVictoryPoints() >= 10;
}
