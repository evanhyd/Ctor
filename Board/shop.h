#ifndef SHOP_H
#define SHOP_H

#include <optional>
#include <string>

class Layout;
class Builder;

class Shop {
  
  //define the rules of purchasing
  virtual std::optional<std::string> CanBuildRoad(Builder& builder, int roadIndex, Layout& layout);
	virtual std::optional<std::string> CanBuildResidence(Builder& builder, int residenceIndex, Layout& layout);

public:
	bool BuildRoad(Builder& builder, int roadIndex, Layout& layout); 
	bool BuildResidence(Builder& builder, int residenceIndex, Layout& layout);
	bool Trade(Builder& instigator, Builder& subject);

  virtual ~Shop();
};
#endif
