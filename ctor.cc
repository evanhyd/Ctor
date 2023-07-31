#include <iostream>
#include <memory>
#include "Board/board.h"
#include "Board/View/stream_view.h"
#include <exception>

using namespace std;

int main() {
  try {
    StreamView view{std::cout};
    Board board{};
    board.Attach(&view);
    board.Play();
  } catch(const std::exception& error) {
    cerr << error.what() << endl;
  }

  return 0;
}
