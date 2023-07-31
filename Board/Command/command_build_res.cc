#include "command_build_res.h"
#include "../board.h"
#include "../shop.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include <iostream>

using namespace std;

Command::Code CommandBuildRes::operator()() {
  int residenceIndex;
  if (!(cin >> residenceIndex)) {
    residenceIndex = -1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
  }

  if (auto error = board.GetShop().BuildResidence(board.CurrentBuilder(), board.GetLayout(), residenceIndex, board.CurrentBuilder().OwnedResidenceCount() < 2); error) {
    board.NotifyAll(error.value());
  }
  return Code::SUCCESS;
}
