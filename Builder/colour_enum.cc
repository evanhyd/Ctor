#include "colour_enum.h"

std::string ColourEnum::Name(Type type) {
  return NAME[type];
}

const std::string ColourEnum::NAME[COUNT] = {
  "Blue",
  "Red",
  "Orange",
  "Yellow",
};
