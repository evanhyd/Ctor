#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <string>
#include <memory>
#include "../../Observer/subject.h"
#include "../../Building/residence_property.h"
#include "../../Building/building.h"
#include "../../Tile/tile.h"
#include "../../Robber/robber.h"

class Layout : public Subject {
protected:
  
  const std::vector<int>& GetAdjacentTilesByResidence(int residenceIndex) const;
  virtual const std::vector<int>& GetAdjacentResidencesByTile(int tileIndex) const;
  virtual const std::vector<vector<int>>& GetRoadGraph();
  virtual void GenerateRandomLayoutImpl();
  
public:
  void GenerateRandomLayout();
  bool ImportLayout(const std::string& fileName);

	explicit Layout();
  virtual ~Layout();

	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Property>> roads; 
	std::vector<std::unique_ptr<ResidenceProperty>> residences;
	std::vector<std::unique_ptr<Builder>> builders;
	std::unique_ptr<Robber> robber;

private:
  static constexpr int TILE_COUNT = 19;
  static constexpr int ROAD_COUNT = 72;
  static constexpr int RESIDENCE_COUNT = 54;
  static constexpr int BUILDER_COUNT = 4;
};
#endif
