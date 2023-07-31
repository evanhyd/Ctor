#include "command_status.h"
#include "../board.h"
#include "../Layout/layout.h"
#include "../../Builder/builder.h"

using namespace std;

Command::Code CommandStatus::operator()() {
  for (const auto& builder : board.GetLayout().GetBuilders()) {
    board.NotifyAll(builder->GetStats());
  }
  return Code::SUCCESS;
}
