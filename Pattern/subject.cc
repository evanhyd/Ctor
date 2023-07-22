#include "subject.h"
#include "observer.h"
#include <algorithm>
#include <cassert>

void Subject::Attach(Observer* observer) {
  assert(std::none_of(observers.begin(), observers.end(), [&](Observer* o) {return o == observer};));
  observers.push_back(observer);
}

void Subject::Detach(Observer* observer) {
  assert(std::any_of(observers.begin(), observers.end(), [&](Observer* o) {return o == observer};));
  observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::NotifyAll() {
  for (Observer* observer : observers) {
    observer->Notify();
  }
}

~Subject() {}
