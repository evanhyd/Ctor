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

class Layout : public Subject<std::string> {
protected:
  std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Property>> roads; 
	std::vector<std::unique_ptr<ResidenceProperty>> residences;
	std::vector<std::unique_ptr<Builder>> builders;
	std::unique_ptr<Robber> robber;
  
  //define the content of a layout
  virtual void GenerateTiles(unsigned seed);
  virtual void GenerateRoads();
  virtual void GenerateResidences();
  virtual void GenerateBuilders();
  virtual void GenerateRobber();
  virtual void SetUpConnection();
  
public:
  void GenerateLayout(unsigned seed);
  bool ImportLayout(const std::string& fileName);

  const std::vector<std::unique_ptr<Tile>>& GetTiles() const;
  const std::vector<std::unique_ptr<Property>>& GetRoads() const;
  const std::unique_ptr<Property>& GetRoad(int index) const;
  const std::vector<std::unique_ptr<ResidenceProperty>>& GetResidences() const;
  const std::unique_ptr<ResidenceProperty>& GetResidence(int index) const;
  const std::vector<std::unique_ptr<Builder>>& GetBuilders() const;
  const std::unique_ptr<Tile>& GetTile(int index) const;
  std::unique_ptr<Builder>& GetBuilder(int index);
  virtual const std::vector<std::vector<int>>& GetRoadGraph();

  //define the physical structure of a layout
  const std::vector<int>& GetAdjacentTilesByResidence(int residenceIndex) const;
  virtual const std::vector<int>& GetAdjacentResidencesByTile(int index) const;

	explicit Layout();
  virtual ~Layout();
};
#endif
