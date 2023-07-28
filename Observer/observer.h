#ifndef OBSERVER_H
#define OBSERVER_H

template <typename T>
class Observer {
public:
  virtual void Notify(const T& state) = 0;
  
  virtual ~Observer() {};
};

#endif
