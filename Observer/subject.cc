#include "subject.h"
#include "observer.h"
#include <algorithm>
#include <cassert>

using namespace std;

void Subject::Attach(Observer* observer) {
  assert(none_of(observers.begin(), observers.end(), [&](Observer* o) { return o = observer; }));
  observers.push_back(observer);
}

void Subject::Detach(Observer* observer) {
  assert(any_of(observers.begin(), observers.end(), [&](Observer* o) { return o = observer; }));
  observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::NotifyAll() {
  for_each(observers.begin(), observers.end(), [](Observer* o) {o->Notify();});
}

Subject::~Subject() {}
