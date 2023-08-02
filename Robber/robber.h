#ifndef ROBBER_H
#define ROBBER_H

#include <string>
#include <vector>
#include <memory>
#include "../SaveLoadable/save_loadable.h"

class Inventory;
class Builder;
class Board;

class Robber : public SaveLoadable {
protected:
  int index;

public:
  int GetTileIndex() const;
  void MoveToTile(int tileIndex);

  virtual std::string SaveData() const override;
  virtual void LoadData(std::istream& file) override;

  virtual void ApplyResourceModifier(Inventory& inventory) const = 0;
  virtual void ApplyBoardModifier(Board& board) const = 0;
  virtual explicit operator std::string() const = 0;

  explicit Robber(int index);
  virtual ~Robber();
};
#endif
