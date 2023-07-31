#ifndef SHOP_H
#define SHOP_H

#include <optional>
#include <string>

class Layout;
class Builder;
class Inventory;
class Property;

class Shop {
  using Error = std::optional<std::string>;

	void PurchaseAndUpgrade(Builder& builder, Property& property, bool initialPlacement = false) const;
  
	//define the rules of purchasing property
	virtual Error CanBuildRoad(Builder& builder, Layout& layout, int roadIndex) const;
	virtual Error CanBuildResidence(Builder& builder, Layout& layout, int residenceIndex, bool initialPlacement = false) const;
	virtual Error CanImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	virtual Error CanTrade(Builder& instigator, Builder& subject, const Inventory& offer1, const Inventory& offer2) const;

public:
	Error BuildRoad(Builder& builder, Layout& layout, int roadIndex) const;
	Error BuildResidence(Builder& builder, Layout& layout, int residenceIndex, bool initialPlacement = false) const;
	Error ImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	Error Trade(Builder& instigator, Builder& subject, const Inventory& offer1, const Inventory& offer2) const;
	Error BankTrade(Builder& instigator, const Inventory& offer) const;

  virtual ~Shop();

private:
  static const std::string NOT_VALID_BUILD_ERROR;
  static const std::string NOT_SUFFICIENT_RESOURCES_ERROR;
};

#endif
