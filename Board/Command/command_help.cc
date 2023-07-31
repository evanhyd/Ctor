#include "command_help.h"
#include "../board.h"
#include <string>

using namespace std;

Command::Code CommandHelp::operator()() {
  string additional_commands = "";
  if (board.enable_bank_trades) {
    additional_commands += "bank-trade <give> <take>\n";
  }
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
    "help\n" + 
    additional_commands
  );
  return Code::SUCCESS;
}
