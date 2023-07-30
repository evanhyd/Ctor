#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

/**
  A std::string format function similar to Python's .format().
  A variable's replacement is indicated by the wildcard %?v, where ? is the minimum width.

  Usage:
  string str = Format("I have %5v marks in %v class", 69, "cs");
  str -> "I have 69    marks in cs class"
*/
template <typename... Args>
std::string Format(const std::string& fmt, const Args&... args) {
  using namespace std;
  static const regex pattern(R"(%([1-9]\d*)?v)");

  ostringstream ss;
  string parsed;
  const auto& tokenParser = [&](auto&& self, sregex_iterator result, const auto& arg, const auto&... args) {
    if (result == sregex_iterator{}) {
      return;
    }

    size_t width = (*result)[1].length() ? stoi((*result)[1]) : 0;
    ss << arg;
    string token;
    if (ss.str().size() < width) {
      token.resize(width - ss.str().size(), ' ');
    }
    token += ss.str();
    ss.str("");
    parsed += result->prefix().str() + token;
    if constexpr (sizeof...(args) != 0) {
      self(self, ++result, args...);
    } else {
      parsed += result->suffix().str();
    }
  };

  if constexpr (sizeof...(args) != 0) {
    tokenParser(tokenParser, regex_iterator(fmt.begin(), fmt.end(), pattern), args...);
  } else {
    parsed = fmt;
  }
  return parsed;
}

/**
  A formatted print function using Format().

  Usage:
  Print("I have %5v marks in %v class", 69, "cs");
*/
template <typename... Args>
void Print(const std::string& fmt, const Args&... args) {
  std::cout << Format(fmt, args...);
}

/**
  A formatted print function using Format(), except the stream are redirected to std::cerr.
  Should be preferred over Print() when used for debugging since the buffer is always flushed.

  Usage:
  PrintErr("I have %5v marks in %v class", 69, "cs");
*/
template <typename... Args>
void PrintErr(const std::string& fmt, const Args&... args) {
  std::cerr << Format(fmt, args...);
}

/**
  A formatted print function using Format() that always prefix by the function name and line number.
  Log() only gets called if _DEBUG flag is defined.
  Should be preferred for stats logging that does not appear in the release build.

  Usage:
  Log("I have %5v marks in %v class", 69, "cs");
*/
template <typename... Args>
void Log(const std::string& fmt, const Args&... args) {
  std::clog << Format(fmt, args...);
}

/**
  An assert function that ensures the precondition and postcondition of a function.
  Should be preferred over <cassert> header's assert() function.

  Assert() only gets called if _DEBUG flag is defined.
  The function that evaluates to the condition value should be pure function, no side effect.
*/
template <typename Printable>
void Assert(bool condition, const Printable& message, const char* file, const char* function, int line) {
  using namespace std;
  if (!condition) {
    cerr << "assertion failed at " << file << ": " << function << " (" << line << ")" << endl;
    cerr << "error: " << message << endl;
    exit(1);
  }
}

#define _DEBUG
#ifdef _DEBUG
#define Log(...) std::clog << __func__ << "(" << __LINE__ << "): "; Log(__VA_ARGS__)
#define Assert(...) Assert(__VA_ARGS__, __FILE__, __func__, __LINE__)
#else 
#define Log(...) 0
#define Assert(...) 0
#endif

#endif
