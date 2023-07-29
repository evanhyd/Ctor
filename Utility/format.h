#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <cctype>
#include <regex>
#include <type_traits>

/**
  A custom std::string format function similar to C's printf.
  A variable's replacement is indicated by the wildcard %?v, where ? is the width.

  Usage:
  string str = Format("I have %5v marks in %v class", 69, "cs");
  str -> "I have 69    marks in cs class"
*/
template <typename... Args>
std::string Format(const std::string& fmt, const Args&... args) {
  using namespace std;
  static const regex pattern(R"(%([1-9]\d*)?v)");

  string parsed;
  const auto& tokenParser = [&](auto&& self, sregex_iterator result, const auto& arg, const auto&... args) {
    if (result == sregex_iterator{}) {
      return;
    }

    int width = (*result)[1].length() ? stoi((*result)[1]) : 0;
    string token;
    if constexpr (requires { to_string(arg); }) {
      token += to_string(arg);
    } else {
      token += arg;
    }
    if (token.size() < width) {
      token.resize(width, ' ');
    }
    parsed += result->prefix().str() + token;
    if constexpr (sizeof...(args) != 0) {
      self(self, ++result, args...);
    }
  };
  tokenParser(tokenParser, regex_iterator(fmt.begin(), fmt.end(), pattern), args...);
  return parsed;
}

#endif
