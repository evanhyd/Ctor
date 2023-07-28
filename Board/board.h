#ifndef BOARD_H
#define BOARD_H

#include <memory>

class Layout;
class Shop;

class Board {
	std::unique_ptr<Layout> layout;
	std::unique_ptr<Shop> shop;

public:
	void Play();
  
	Board(std::unique_ptr<Layout> layout, std::unique_ptr<Shop> shop);
};

#endif
