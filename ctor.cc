#include <iostream>
#include <memory>
#include "Board/board.h"

using namespace std;

int main() {
  unique_ptr<Board> board = make_unique<Board>();
  board->Start();
  return 0;
}
