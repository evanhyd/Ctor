#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <algorithm>
#include <cassert>
#include "observer.h"

template <typename T>
class Subject {
  std::vector<Observer<T>*> observers;

public:
  void Attach(Observer<T>* observer) {
    assert(none_of(observers.begin(), observers.end(), [&](auto* o) { return o = observer; }));
    observers.push_back(observer);
  }

  void Detach(Observer<T>* observer) {
    assert(any_of(observers.begin(), observers.end(), [&](auto* o) { return o = observer; }));
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
  }

  void NotifyAll(const T& state) {
    for (auto observer : observers) {
      observer->Notify(state);
    }
  }

  virtual ~Subject() {}
};

#endif
