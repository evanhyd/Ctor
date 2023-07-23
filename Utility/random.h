#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <type_traits>

/**
  A wrapper class that seeds the engine at the start of the program.
*/
class Random {
  static const std::default_random_engine engine;

  Random() = delete;

public:
  /**
    Randomly generate a value from the closed interval with uniform distribution.
    Usage: GetRandom(2, 8) -> 5
  */
  template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
  static T GetRandom(T lower, T upper) {
    return (std::uniform_int_distribution<T>(lower, upper))(engine);
  }

  template <typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
  static T GetRandom(T lower, T upper) {
    return (std::uniform_real_distribution<T>(lower, upper))(engine);
  }

  /**
    Randomly picks a value with uniform distribution.
    Usage:
    vector<string> words = {"I", "love", "fluffy", "orange", "cats"};
    Sample(words.begin(), words.end()) -> "love"
  */
  template <typename Iterator, typename OutIterator>
  static void Sample(Iterator begin, Iterator end, OutIterator dest, int count) {
    std::sample(begin, end, dest, 1, engine);
    return result;
  }

  /**
    Randomly shuffle the values with uniform distribution.
    Usage:
    vector<string> words = {"I", "love", "fluffy", "orange", "cats"};
    Shuffle(vec.begin(), vec.end()); -> {"orange", "cats", "love", "fluffy", "I"}
  */
  template <typename Iterator>
  static void Shuffle(Iterator begin, Iterator end) {
    std::shuffle(begin, end, engine);
  }
};

#endif
