#ifndef SAVE_LOADABLE_H
#define SAVE_LOADABLE_H

#include <string>
#include <optional>
#include <fstream>

class SaveLoadable {
public:
  using Error = std::optional<std::string>;
  virtual std::string SaveData() const = 0;
  virtual void LoadData(std::istream& file) = 0;

  virtual ~SaveLoadable();
};

#endif
