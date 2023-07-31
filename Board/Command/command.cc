#include "command.h"
#include "../board.h"

Command::Command(Board& board) : board(board) {}

Command::~Command() {}
