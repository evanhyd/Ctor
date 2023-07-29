#ifndef BOARD_H
#define BOARD_H


#include <memory>
#include "View/view.h"
#include "Layout/layout.h"
#include "shop.h"

class Board {
	std::unique_ptr<Layout> layout;
	std::unique_ptr<Shop> shop;
	std::unique_ptr<View> view;

	void CommandHelp() const;

public:
	void Start();
	void Play();
	bool Turn(std::unique_ptr<Builder> &builder); // returns if player has won
	void Print();
	void Win(std::unique_ptr<Builder> &builder);
	bool Won(std::unique_ptr<Builder> &builder);
	void Reset();
	Inventory GetInventory(std::string resource);
  
	Board();
};


#endif
