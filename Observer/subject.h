#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"
#include "../Utility/print.h"
#include <vector>
#include <algorithm>

template <typename ...Ts>
class Subject {
  std::vector<Observer<Ts...>*> observers;

public:
  void Attach(Observer<Ts...>* observer) {
    Assert(std::none_of(observers.begin(), observers.end(), [&](auto o) { return o == observer; }), Format("attached duplicated observer %v", observer));
    observers.push_back(observer);
  }

  void Detach(Observer<Ts...>* observer) {
    Assert(std::any_of(observers.begin(), observers.end(), [&](auto o) { return o == observer; }, Format("attempted to remove non-existed observer %v", observer)));
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
  }

  template <typename T>
  void NotifyAll(const T& data) {
    for (auto observer : observers) {
      observer->Notify(data);
    }
  }

  virtual ~Subject() {}
};

#endif
