#include "print.h"
#include <cctype>

std::string ToUpperCase(std::string str) {
  for (char& c :str) {
    c = toupper(c);
  }
  return str;

}
std::string ToLowerCase(std::string str) {
  for (char& c :str) {
    c = tolower(c);
  }
  return str;
}

std::string ToPascalCase(std::string str) {
  str = ToLowerCase(str);
  if (!str.empty()) {
    str.front() = toupper(str.front());
  }
  return str;
}
