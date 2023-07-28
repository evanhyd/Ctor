#ifndef SHOP_H
#define SHOP_H

#include <optional>
#include <string>

class Layout;
class Builder;
class Inventory;
class Property;

class Shop {
  void BroadcastMessage(const std::string& message) const;
	void PurchaseAndUpgrade(Builder& builder, Property& property) const;
  
	//define the rules of purchasing property
	virtual std::optional<std::string> CanBuildRoad(Builder& builder, Layout& layout, int roadIndex) const;
	virtual std::optional<std::string> CanBuildResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	virtual std::optional<std::string> CanImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	virtual bool CanTrade(Builder& instigator, Builder& subject, const Inventory& trade) const;

public:
	bool BuildRoad(Builder& builder, Layout& layout, int roadIndex) const;
	bool BuildResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	bool ImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const;
	bool Trade(Builder& instigator, Builder& subject, const Inventory& trade) const;

  virtual ~Shop();

private:
  static const std::string NOT_VALID_BUILD_ERROR_MSG;
  static const std::string NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
};
#endif
