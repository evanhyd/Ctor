#include "command_save.h"

using namespace std;

Command::Code CommandSave::operator()() {
  return Code::SUCCESS;
}
