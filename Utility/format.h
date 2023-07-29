#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <cctype>

template <typename... Args, typename Arg>
std::string Format(std::string fmt, const Arg& arg, const Args&... args) {
  std::string formatted;
  for (int i = 0; i < fmt.size();) {
    if (fmt[i] == '%') {
      bool wildcard = false;
      bool escape = false;
      int width = 0;
      for (++i; i < fmt.size(); ++i) {
        if (isdigit(fmt[i]) && fmt[i] != '0') {
          ++width;
        } else if (fmt[i] == 'v') {
          wildCard = true;
          break;
        } else if (fmt[i])
      }

      if ()

    } else {
      formatted += fmt[i];
      ++i;
    }
  }
}

#endif
