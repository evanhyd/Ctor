#include "command_roll.h"
#include "../board.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include "../../Inventory/inventory.h"
#include "../../Utility/print.h"
#include <vector>
#include <map>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

Command::Code CommandRoll::operator()() {
  const int tileNumber = board.CurrentBuilder().Roll();
  board.NotifyAll(Format("rolled %v\n", tileNumber)); 

  constexpr int ROBBER_TILE_NUMBER = 7;
  if (tileNumber != ROBBER_TILE_NUMBER) {
    DistributeResource(tileNumber);
  } else {
    ActivateRobber();
  }

  return Code::END_STAGE;
}

void CommandRoll::DistributeResource(int tileNumber){
  const auto& builders = board.GetLayout().GetBuilders();
  const auto& tiles = board.GetLayout().GetTiles();
  const auto& robber = board.GetLayout().GetRobber();

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
      board.NotifyAll(gained);
    }
  }

  if (!hasGained) {
    board.NotifyAll("No builders gained resources.\n");
  }
}

void CommandRoll::ActivateRobber() {

  //apply robber effect to all players
  Layout& layout = board.GetLayout();
  Robber& robber = layout.GetRobber();
  robber.ApplyBoardModifier(board);

  //prompting builder for new position 
  while (true) {
    board.NotifyAll(Format("Choose where to place the %v.\n> ", string(robber)));

    int tileIndex;
    while (!(cin >> tileIndex)) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin.clear();
    }

    if (tileIndex == robber.GetTileIndex()) {
      board.NotifyAll("Opps, you must move the robber to a different tile.\n");
      continue;
    }
    if (tileIndex < 0 || tileIndex >= int(layout.GetTiles().size())) {
      board.NotifyAll("Opps, invalid tile index");
      continue;
    }
    robber.MoveToTile(tileIndex);
    break;
  }

  //getting all nearby owners of residences of that tile
  std::map<ColourEnum::Type, Builder*> victims;
  for(int residenceIndex : layout.GetAdjacentResidencesByTile(robber.GetTileIndex())) {
    ResidenceProperty& property = *layout.GetResidences()[residenceIndex];

    //valid player, not the stealer, have non-empty resource
    if (property.GetOwner() && property.GetOwner() != &board.CurrentBuilder() && property.GetOwner()->GetInventory().GetTotal() > 0) {
      victims.insert({property.GetOwner()->GetColour(), property.GetOwner()});
    }
  }

  //no one to steal from 
  if(victims.empty()) {
    board.NotifyAll(Format("Builder %v has no one to steal from.\n", ColourEnum::Name(board.CurrentBuilder().GetColour()))); 
    return;
  }

  //list out other builders to steal from 
  string message = Format("Builder %v can choose to steal from ", ColourEnum::Name(board.CurrentBuilder().GetColour()));
  for (const auto& [colour, builder] : victims) {
    message += ColourEnum::Name(colour) + ", ";
  }
  message[message.size() - 2] = '.';
  message[message.size() - 1] = '\n';
  board.NotifyAll(message);
  
  //takes in colour of builder to steal from 
  board.NotifyAll("Choose a builder to steal from.\n"); 

  Builder* victim;
  while(true) {
    string target; cin >> target;
    target = ToPascalCase(target);

    bool found = false;
    for (const auto& [colour, builder] : victims) {
      if (ColourEnum::Name(colour) == target){
        victim = builder;
        found = true;
        break;
      }
    }

    if (found) {
      break;
    }
  }
  
  //steal from the victim with chance proportional to their resource distribution
  default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> dist(0, victim->GetInventory().GetTotal());
  
  int resourceSlot = dist(engine), total = 0; 
  for (int type = ResourceEnum::Type::BRICK; type < ResourceEnum::COUNT; ++type) {
    ResourceEnum::Type v = ResourceEnum::Type(type);
    total += victim->GetInventory().GetResource(v);

    //steal
    if (total != 0 && resourceSlot <= total) {
      auto error = board.GetShop().Trade(board.CurrentBuilder(), *victim, Inventory(0, 0, 0, 0, 0), Inventory(v, 1));
      Assert(!error, Format("stealing failed! %v", error.value()));
      
      board.NotifyAll(Format("Builder %v steals %v from builder %v\n", 
        ColourEnum::Name(board.CurrentBuilder().GetColour()),
        ColourEnum::Name(victim->GetColour()),
        ResourceEnum::Name(v), victim->GetColour())
      );
      break; 
    }
  }
}
