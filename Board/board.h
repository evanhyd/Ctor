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

	std::unique_ptr<Layout> layout;
	std::unique_ptr<Shop> shop;
  int playerIndex;

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
  bool enable_bank_trades;
  
  virtual std::string SaveData() const;
  virtual void LoadData(std::istream& file) override;

	void Play(bool freshStart);
  
	Board(std::unique_ptr<Layout> layout, std::unique_ptr<Shop> shop, bool enable_bank_trades);
};

#endif
