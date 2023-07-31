#include "command_board.h"
#include "../board.h"
#include "../Layout/layout.h"

Command::Code CommandBoard::operator()() {
  board.NotifyAll(board.GetLayout());
  return Code::SUCCESS;
}
