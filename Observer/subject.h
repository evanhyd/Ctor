#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"
#include "../Utility/print.h"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Subject {
  std::vector<Observer<T>*> observers;

public:
  void Attach(Observer<T>* observer) { 
    Assert(none_of(observers.begin(), observers.end(), [&](auto o) { return o == observer; }), Format("attached duplicated observer %v", observer));
    observers.push_back(observer);
  }

  void Detach(Observer<T>* observer) {
    Assert(any_of(observers.begin(), observers.end(), [&](auto o) { return o == observer; }, Format("attempted to remove non-existed observer %v", observer)));
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
