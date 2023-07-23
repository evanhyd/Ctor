#include "subject.h"
#include "observer.h"
#include <algorithm>
#include <cassert>

void Subject::Attach(Observer* observer) {
  assert(std::find(observers.begin(), observers.end(), observer) == observers.end());
  observers.push_back(observer);
}

void Subject::Detach(Observer* observer) {
  assert(std::find(observers.begin(), observers.end(), observer) != observers.end());
  observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::NotifyAll() {
  std::for_each(observers.begin(), observers.end(), [](Observer* o) {o->Notify();});
}

Subject::~Subject() {}
