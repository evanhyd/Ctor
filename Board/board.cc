#include "board.h"

Board::Board() {
	layout = new Layout();
	shop = new Shop(*layout);
}

Board::~Board() {
	delete layout;
	delete shop;
}

void Board::Play() {

}