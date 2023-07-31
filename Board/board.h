#ifndef BOARD_H
#define BOARD_H

#include "../Observer/subject.h"
#include "Layout/layout.h"
#include "shop.h"
#include "../Inventory/inventory.h"
#include "../SaveLoadable/save_loadable.h"
#include "Command/command.h"
#include <memory>
#include <map>
#include <string>
#include <functional>

class Builder;

class Board : public Subject<std::string, Layout>, public SaveLoadable {
protected:
  using Commands = std::map<std::string, std::unique_ptr<Command>>;
  Commands beginTurnCMD;
  Commands duringTurnCMD;

  int playerIndex;
	std::unique_ptr<Layout> layout;
	std::unique_ptr<Shop> shop;

  virtual void InitializeCommandMapping();
  Command::Code ExecuteCommand(const Commands& commands, const std::string& cmd);
  virtual bool HasWon();

  //4 stages of the game
  void BeginGame();
  void BeginTurn();
  bool DuringTurn();
  bool EndOfGame();

public:
  Builder& CurrentBuilder();
  Layout& GetLayout();
  Shop& GetShop();
  int GetPlayerIndex();
  
  virtual std::string SaveData() const;
  virtual Error LoadData(const std::string& data);

  void ImportBoard();
	void Play();
  
	Board();
};

#endif
