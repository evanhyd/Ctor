#ifndef SAVE_LOADABLE_H
#define SAVE_LOADABLE_H

#include <string>
#include <optional>

class SaveLoadable {
public:
  using Error = std::optional<std::string>;
  virtual std::string SaveData() const = 0;
  virtual SaveLoadable::Error LoadData(const std::string& data) = 0;

  virtual ~SaveLoadable();
};

#endif
