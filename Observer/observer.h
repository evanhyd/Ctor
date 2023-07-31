#ifndef OBSERVER_H
#define OBSERVER_H

template <typename ...Ts>
class Observer {
  virtual ~Observer() {};
};

template <typename T>
class Observer<T> {
public:
  virtual void Notify(const T& t) = 0;
  virtual ~Observer() {};
};

template <typename T, typename... Ts>
class Observer<T, Ts...> : public Observer<Ts...> {
public:
  using Observer<Ts...>::Notify;
  virtual void Notify(const T& t) = 0;
};

#endif
