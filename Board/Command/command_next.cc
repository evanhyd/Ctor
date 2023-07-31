#include "command_next.h"

using namespace std; 

Command::Code CommandNext::operator()() {
  return Code::END_STAGE;
}
