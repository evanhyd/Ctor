#include <iostream>
#include <memory>
#include "Board/board.h"
#include "Board/View/stream_view.h"

using namespace std;

int main() {
  StreamView view{std::cout};
  Board board{};
  board.Attach(&view);
  board.Play();
  return 0;
}
