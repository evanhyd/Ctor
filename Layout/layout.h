#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <string>
#include <memory>
#include "subject.h"

class Tile;
class Property;
class ResidenceProperty;
class Builder;
class Robber;

class Layout : public Subject {
protected:
	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Property>> roads;
	std::vector<std::unique_ptr<ResidenceProperty>> residences;
	std::vector<std::unique_ptr<Builder>> builders;
	std::unique_ptr<Robber> robber;

  virtual void GenerateRandomLayoutImpl();
  
public:
  void GenerateRandomLayout();
  bool ImportLayout(const std::string& fileName);

	explicit Layout();
  virtual ~Layout();

private:
  static constexpr int TILE_COUNT = 19;
  static constexpr int ROAD_COUNT = 72;
  static constexpr int RESIDENCE_COUNT = 54;
  static constexpr int BUILDER_COUNT = 4;
};
#endif
