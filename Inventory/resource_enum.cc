#include "resource_enum.h"

const std::string& ResourceEnum::Name(Type type) {
  return NAME[type];
}

const std::string ResourceEnum::NAME[COUNT] = {
  "BRICK",
  "ENERGY",
  "GLASS",
  "HEAT",
  "WIFI",
};
