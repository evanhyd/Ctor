#ifndef COLOUR_ENUM_H
#define COLOUR_ENUM_H
#include <string>

class ColourEnum {
public:
  enum Type : int {
    BLUE,
    RED,
    ORANGE,
    YELLOW,
    COUNT,
  };
  ColourEnum() = delete;
  static std::string Name(Type type);

private:
  const static std::string NAME[COUNT];
};

#endif
