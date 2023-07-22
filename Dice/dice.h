#ifndef DICE_H
#define DICE_H

class Dice {
protected:
  virtual int RollImpl() const = 0;

public:
  int Roll() const;

  virtual ~Dice();
};

#endif
