#ifndef COMMAND_H
#define COMMAND_H

class Board;

class Command {
protected:
  Board& board;

public:
  enum class Code : int {
    SUCCESS,
    END_STAGE,
  };
  virtual Code operator()() = 0;

  Command(Board& board);
  virtual ~Command();
};

#endif
