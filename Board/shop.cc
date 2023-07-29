#include "shop.h"
#include "Layout/layout.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"

using namespace std;

const std::string Shop::NOT_VALID_BUILD_ERROR_MSG = "You cannot build here.";
const std::string Shop::NOT_SUFFICIENT_RESOURCES_ERROR_MSG = "You do not have enough resources.";

void Shop::PurchaseAndUpgrade(Builder& builder, Property& property, bool initialPlacement) const {
  if (!initialPlacement) {
    builder.GetInventory() -= property.GetUpgradeCost();
  }
  property.Upgrade(builder);
}

Shop::Error Shop::CanBuildRoad(Builder& builder, Layout& layout, int roadIndex) const {
  const auto& roadGraph = layout.GetRoadGraph();
  const auto& residences = layout.GetResidences();
  const auto& roads = layout.GetRoads();

  //check index bound
  if (roadIndex < 0 || roadIndex >= int(roads.size())) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //check the road has no owner
  if (roads[roadIndex]->GetOwner()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }
  
  //check if any owned adjacent residences
  const auto CheckResidence = [&]() {
    return builder.OwnResidence(roadGraph[roadIndex][0]) || builder.OwnResidence(roadGraph[roadIndex][1]);
  };
  
  //check if any owned adjacent road
  const auto CheckRoad = [&]() {
    constexpr int DX[] = {0, 0, 1, 1};
    constexpr int DY[] = {0, 1, 0, 1};

    for (int i = 0; i < int(roads.size()); ++i) {
      if (!builder.OwnRoad(i)) {
        continue;
      }

      //check if there's a property sand-witched in between
      for (int j = 0; j < 4; ++j) {
        const int r0 = roadGraph[i][DX[j]];
        const int r1 = roadGraph[i][DY[j]];
        const Builder* owner = residences[r0]->GetOwner(); 
        if ((r0 == r1 && !owner) || owner == &builder) {
          return true;
        }
      }
    }
    return false;
  };

  if(!CheckRoad() && !CheckResidence()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  if(!builder.GetInventory().CanAfford(roads[roadIndex]->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
  }

  return {};
}

Shop::Error Shop::CanBuildResidence(Builder& builder, Layout& layout, int residenceIndex, bool initialPlacement) const{
  const auto& roadGraph = layout.GetRoadGraph(); 
  const auto& residences = layout.GetResidences(); 
  const auto& roads = layout.GetRoads();
  const auto& property = residences[residenceIndex];

  //check index bound
  if (residenceIndex < 0 || residenceIndex >= int(residences.size())) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //check if not owned by anyone    
  if (property->GetOwner()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //check there's no adjacent property
  for (int i = 0; i < int(roads.size()); ++i){
    if((roadGraph[i][0] == residenceIndex && residences[roadGraph[i][1]]->GetOwner()) ||
       (roadGraph[i][1] == residenceIndex && residences[roadGraph[i][0]]->GetOwner())) {
      return NOT_VALID_BUILD_ERROR_MSG; 
    }
  }

  //check there's an adjacent road
  int index = 0;
  const bool hasAdjacent = initialPlacement || std::any_of(roadGraph.begin(), roadGraph.end(), [&](const auto& roadEdge) mutable {
    return (roadEdge[0] == residenceIndex || roadEdge[1] == residenceIndex) && builder.OwnRoad(index++);
  });

  if (!hasAdjacent) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //make sure the housing is affordable
  if(!initialPlacement && !builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
  }

  return {};
}

Shop::Error Shop::CanImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  const auto& residences = layout.GetResidences();

  //check index bound
  if (residenceIndex < 0 || residenceIndex >= int(residences.size())) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //must be owned and have next tier
  const auto& property = residences[residenceIndex]; 
  if (property->GetOwner() != &builder || property->CanUpgradeToNextTier()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  if(!builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
  }

  return {};
}

Shop::Error Shop::CanTrade(Builder& instigator, Builder& subject, const Inventory& trade) const {
  if (instigator.GetInventory().CanAfford(trade) && subject.GetInventory().CanAfford(trade * -1)) {
    return {};
  }
  return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
}

Shop::Error Shop::BuildRoad(Builder& builder, Layout& layout, int roadIndex) const {
  if (auto error = CanBuildRoad(builder, layout, roadIndex); error) {
    return error;
  }

  const auto& property = layout.GetRoads()[roadIndex];
  PurchaseAndUpgrade(builder, *property);
  builder.AddRoad(roadIndex, *property);
  return {};
}

Shop::Error Shop::BuildResidence(Builder& builder, Layout& layout, int residenceIndex, bool initialPlacement) const {
  if (auto error = CanBuildResidence(builder, layout, residenceIndex, initialPlacement); error) {
    return error;
  }

  const auto& property = layout.GetResidences()[residenceIndex];
  PurchaseAndUpgrade(builder, *property);
  builder.AddResidence(residenceIndex, *property);
  return {};
}

Shop::Error Shop::ImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  if (auto error = CanImproveResidence(builder, layout, residenceIndex); error) {
    return error;
  }

  //only improve, does not add to the property set
  PurchaseAndUpgrade(builder, *layout.GetResidences()[residenceIndex]);
  return {};
}

Shop::Error Shop::Trade(Builder& instigator, Builder& subject, const Inventory& trade) const {
  if (auto error = CanTrade(instigator, subject, trade); error) {
    return error;
  }
  instigator.GetInventory() -= trade; 
  subject.GetInventory() += trade; 
  return {}; 
}

Shop::~Shop() {}
