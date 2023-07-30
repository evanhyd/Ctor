#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <map>
#include <string>
#include <functional>
#include "Layout/layout.h"
#include "shop.h"
#include "../Observer/subject.h"
#include "../Inventory/inventory.h"

class Builder;

class Board : Subject<std::string> {
  enum class Code : int {
    SUCCESS,
    END_STAGE,
  };

	std::unique_ptr<Layout> layout;
	std::unique_ptr<Shop> shop;

  int playerIndex;
  //command set should be initialize dynamically
  //so we can add more commands if we are going to do bonus
  //consider moving it into a commmand class.
  std::map<std::string, std::function<Code()>> beginTurnCMD;
  std::map<std::string, std::function<Code()>> duringTurnCMD;

  virtual void InitializeCommandMapping();
  Builder& CurrentBuilder();

  //4 stages of the game
  void BeginGame();
  void BeginTurn();
  Code DuringTurn();
  Code EndOfGame();

  //beginning of turn
  Code CommandLoad();
  Code CommandFair();
  Code CommandRoll();

  //during the turn
  Code CommandBoard();
  Code CommandStatus();
  Code CommandResidences();
  Code CommandBuildRoad();
  Code CommandBuildRes();
  Code CommandImprove();
  Code CommandTrade();
  Code CommandNext();
  Code CommandSave();
  Code CommandHelp();

  void DistributeResource(int tileNumber);
  void ActivateRobber();
	Inventory ParseResourceToInventory(std::string resource);
  bool HasWon();

public:
  void ImportBoard();
	void Play();
  
	Board();
};


#endif
