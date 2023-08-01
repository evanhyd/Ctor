#include "command_load.h"
#include "../board.h"
#include "../../Builder/builder.h"
#include "../../Dice/loaded_dice.h"
#include <iostream>

using namespace std;

Command::Code CommandLoad::operator()() {
  while (true) {
    board.NotifyAll("Input a roll between 2 and 12: ");
    if (int load; cin >> load) {
      if (2 <= load && load <= 12) {
        board.CurrentBuilder().SetDice(LoadedDice::dice[load]);
        break;        
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    board.NotifyAll("Invalid roll.\n");
  }
  return Code::SUCCESS;
}
