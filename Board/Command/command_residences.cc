#include "command_residences.h"
#include "../board.h"
#include "../../Builder/builder.h"

using namespace std;

Command::Code CommandResidences::operator()() {
  board.NotifyAll(board.CurrentBuilder().GetResidences());
  return Code::SUCCESS;
}
