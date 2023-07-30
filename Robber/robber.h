#ifndef ROBBER_H
#define ROBBER_H

#include <string>
#include "../Inventory/inventory.h"

class Robber {
protected:
	int index;

public:
	int GetTileIndex() const;
	void MoveToTile(int tileIndex);

  virtual Inventory ApplyModifier(const Inventory& inventory) const = 0;
  virtual explicit operator std::string() const = 0;

	explicit Robber(int index);
	virtual ~Robber();
};
#endif
