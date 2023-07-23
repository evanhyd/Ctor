#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>
#include <memory>

class Tile;
class Property;
class ResidenceProperty;
class Builder;
class Robber;

class Layout {
protected:
	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Property>> roads;
	std::vector<std::unique_ptr<ResidenceProperty>> residences;
	std::vector<std::unique_ptr<Builder>> builders;
	std::unique_ptr<Robber> robber;
  
public: 
	explicit Layout();
  virtual ~Layout();
};
#endif
