#include <iostream>
#include <memory>
#include "Board/board.h"
#include "Board/View/stream_view.h"
#include <exception>

using namespace std;

int main() {
  try {
    StreamView view{std::cout};
    bool enable_bank_trades = true;
    Board board(enable_bank_trades);
    board.Attach(&view);
    board.Play();
  } catch(const std::exception& error) {
    cerr << error.what() << endl;
  }

  return 0;
}
