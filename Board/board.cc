#include "board.h"
#include "Layout/layout.h"
#include "shop.h"
#include <cassert>

Board::Board(std::unique_ptr<Layout> layout, std::unique_ptr<Shop> shop)
  : layout(std::move(layout)), shop(std::move(shop)) {
    assert(layout);
    assert(shop);
}

void Board::Play() {

}
