#include "board.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"
#include "../Dice/loaded_dice.h"
#include "../Dice/fair_dice.h"
#include <exception>
#include <random>
#include <cmath>


using namespace std;

Board::Board() : layout(make_unique<Layout>()), shop(make_unique<Shop>()) {
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

Builder& Board::CurrentBuilder() {
  Assert(0 <= playerIndex && playerIndex < int(layout->GetBuilders().size()), Format("invalid builder index %v", playerIndex));
  return *layout->GetBuilders()[playerIndex];
}

void Board::ImportBoard() {

}

void Board::Play() {
  InitializeCommandMapping();

  while (true) {
    layout->GenerateLayout(69420);

    //delete this
    for (auto& builder : layout->GetBuilders()) {
      Inventory& inventory = builder->GetInventory();
      inventory += Inventory(50, 50, 50, 50, 50);
    }

    BeginGame();
    const int PLAYER_COUNT = layout->GetBuilders().size();
    playerIndex = 0;
    while (true) {
      BeginTurn();
      if (DuringTurn() == Code::END_STAGE) {
        break;
      }
      playerIndex = (playerIndex + 1)%PLAYER_COUNT;
    }

    if (EndOfGame() == Code::END_STAGE) {
      break;
    }
    layout = make_unique<Layout>(); //reset the board
  }
}

void Board::BeginGame() {
  const auto& builders = layout->GetBuilders();
  CommandBoard();
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
  CommandBoard();

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
      NotifyAll("Invalid command.\n");
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
      NotifyAll("Invalid command.\n");
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
    if (cin >> load) {
      if (2 <= load && load <= 12) {
        CurrentBuilder().SetDice(LoadedDice::dice[load]);
        break;        
      }
    } else {
      cin.ignore('\n');
      cin.clear();
    }
    NotifyAll("Invalid roll.\n");
  }
  return Code::SUCCESS;
}

Board::Code Board::CommandFair() {
  CurrentBuilder().SetDice(FairDice::dice);
  return Code::SUCCESS;
}

Board::Code Board::CommandRoll() {
  // auto& tiles = layout->GetTiles();
  const int tileNumber = CurrentBuilder().Roll();
  NotifyAll(Format("rolled %v\n", tileNumber)); 

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
  NotifyAll(*layout);
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
  Inventory giveInventory = ParseResourceToInventory(give);
  Inventory takeInventory = ParseResourceToInventory(take);
  if (giveInventory.GetTotal() == 0  || takeInventory.GetTotal() == 0) {
    NotifyAll("Invalid resource type.\n");
    return Code::SUCCESS;
  }

  if (give == take) {
    NotifyAll("Can't trade the same resource.\n");
    return Code::SUCCESS;
  }

  NotifyAll(Format("%v offers %v one %v for one %v.\n Does %v accept this offer?\n", 
    ColourEnum::Name(builders[playerIndex]->GetColour()),
    ColourEnum::Name(builders[receiverIndex]->GetColour()),
    give, take, ColourEnum::Name(builders[receiverIndex]->GetColour())));

  NotifyAll("> ");
  string response; cin >> response;
  for_each(response.begin(), response.end(), [](char& c) { c = tolower(c); });
  if (response == "yes") {
    if (auto error = shop->Trade(*builders[playerIndex], *builders[receiverIndex], giveInventory, takeInventory); error) {
      NotifyAll(error.value());
    } else {
      NotifyAll("Traded successfully\n");
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
  "residences\n" +
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
  return ;

  //everyone with >= 10 resources lose half resources 
  layout->GetRobber().ApplyBuilderModifier(layout->GetBuilders(), CurrentBuilder());


  //prompting builder for new position 
  NotifyAll(Format("Choose where to place the %v\n", string(layout->GetRobber()))); 
  int newRobberPosition;
  cin >> newRobberPosition; 

  if(newRobberPosition == layout->GetRobber().GetTileIndex()){
    return; 
  }

  //moving robber to new location 
  layout->GetRobber().MoveToTile(newRobberPosition); 

  //getting all nearby owners of that residence 
  std::vector<Builder*> nearbyBuilders; 
  const auto& nearbyResidences = layout->GetAdjacentResidencesByTile(newRobberPosition);   
  for(auto nearbyResidence : nearbyResidences){
    if(Builder* owner = layout->GetResidences()[nearbyResidence]->GetOwner(); owner && owner != &CurrentBuilder()){
      nearbyBuilders.push_back(owner);  
    }
  }

  //no one to steal from 
  if(nearbyBuilders.empty()){
    NotifyAll(Format("Builder %v has no builders to steal from.\n", CurrentBuilder().GetColour())); 
    return; 
  }

  //list out other builders to steal from 
  NotifyAll(Format("Builder %v can choose to steal from ", CurrentBuilder().GetColour()));
  for(int i = 0; i < nearbyBuilders.size(); ++i){
    if(i == nearbyBuilders.size() - 1){
      NotifyAll(Format("%v\n", nearbyBuilders[i]->GetColour())); 
    }
    NotifyAll(Format("%v, ", nearbyBuilders[i]->GetColour())); 
  }
  NotifyAll(Format("Choose a builder to steal from.\n")); 

  //takes in colour of builder to steal from 
  string colour; 
  while(true){
    cin >> colour; 
    if(any_of(nearbyBuilders.begin(), nearbyBuilders.end(), 
      [&](Builder* builder) { return to_string(builder->GetColour()) == colour; })){
      break;  
    }
    cin.ignore('\n'); 
    cin.clear(); 
  }


  //steal from builder  
  for(Builder* builder : nearbyBuilders){
    if(to_string(builder->GetColour()) == colour){
      
      //there is nothing to steal  
      if(builder->GetInventory().GetTotal() == 0){
        break; 
      }

      //getting type of resource to steal 
      int randomNumber = GetRandom(0, builder->GetInventory().GetTotal());
      int total = 0; 
      int type = ResourceEnum::Type::BRICK;
      for (; type < ResourceEnum::COUNT; ++type) {
        ResourceEnum::Type v = ResourceEnum::Type(type);
        total += builder->GetInventory().GetResource(v);
        if(randomNumber <= total){
          break; 
        }
      }

      //stealing that type of resource
      

      break; 
    }
  }
  
  //now check colour against builder 
  //iterate through all builder and check 

  //question: can you steal from yourself? 
  //Builder <colour1> can choose to steal from [builders].

  //tileindex how to get the vertices from a tile? 

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

int Board::GetRandom(int lower, int higher){
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(lower, higher + 1);
  return floor(dist(mt));
}
