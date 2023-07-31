#include "command_help.h"
#include "../board.h"
#include <string>

using namespace std;

Command::Code CommandHelp::operator()() {
  board.NotifyAll(
    string("Valid commands:\n") +
    "board\n" +
    "status\n" +
    "residences\n" +
    "build-road <edge#>\n" +
    "build-res <housing#>\n" +
    "improve <housing#>\n" +
    "trade <colour> <give> <take>\n" +
    "next\n" +
    "save <file>\n" +
    "help\n"
  );
  return Code::SUCCESS;
}
