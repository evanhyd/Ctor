#include "command_improve.h"
#include "../board.h"
#include "../shop.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include <iostream>

using namespace std; 

Command::Code CommandImprove::operator()() {
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
  }
  if (auto error = board.GetShop().ImproveResidence(board.CurrentBuilder(), board.GetLayout(), residenceIndex); error) {
    board.NotifyAll(error.value());
  }
  return Code::SUCCESS;
}
