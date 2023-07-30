#ifndef RESOURCE_ENUM_H
#define RESOURCE_ENUM_H

#include <string>

class ResourceEnum {
public:
  enum Type : int {
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI,
    COUNT,
  };
  ResourceEnum() = delete;
  static const std::string& Name(Type type);

private:
  const static std::string NAME[COUNT];
};

#endif
