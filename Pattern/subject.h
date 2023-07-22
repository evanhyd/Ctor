#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
  std::vector<Observer*> observers;

public:
  void Attach(Observer* observer);
  void Detach(Observer* observer);
  void NotifyAll();

  virtual ~Subject();
};

#endif
