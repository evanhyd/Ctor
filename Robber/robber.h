#ifndef ROBBER_H
#define ROBBER_H

#include <string>

class Inventory;
class Builder;

class Robber {
protected:
	int index;

public:
	int GetTileIndex() const;
	void MoveToTile(int tileIndex);

  virtual void ApplyResourceModifier(Inventory& inventory) const = 0;
  virtual void ApplyBuilderModifier(const std::vector<std::unique_ptr<Builder>>& allBuilders, Builder& currentBuilder) const = 0;
  virtual explicit operator std::string() const = 0;

	explicit Robber(int index);
	virtual ~Robber();
};
#endif
