#include <iostream>
#include <memory>
#include "Board/board.h"

using namespace std;

int main() {
  unique_ptr<Board> board = make_unique<Board>();
  board->Play();
  return 0;
}
