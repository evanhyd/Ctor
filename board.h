#ifndef BOARD_H
#define BOARD_H

#include "layout.h"
#include "shop.h"

class Board {
public:
	Board();
	~Board();
	void Play();
private: 
	Layout* layout;
	Shop shop;
};

#endif
