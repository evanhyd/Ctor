#include "command_build_road.h"
#include "../board.h"
#include "../shop.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"
#include <iostream>

using namespace std;

Command::Code CommandBuildRoad::operator()() {
  int roadIndex;
  if (!(cin >> roadIndex)) {
    roadIndex = -1;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  if (auto error = board.GetShop().BuildRoad(board.CurrentBuilder(), board.GetLayout(), roadIndex); error) {
    board.NotifyAll(error.value());
  }
  return Code::SUCCESS;
}
