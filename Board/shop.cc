#include "shop.h"
#include "Layout/layout.h"
#include "../Builder/builder.h"
#include <cassert>

using namespace std;

const std::string Shop::NOT_VALID_BUILD_ERROR_MSG = "You cannot build here.";
const std::string Shop::NOT_SUFFICIENT_RESOURCES_ERROR_MSG = "You do not have enough resources.";

void Shop::BroadcastMessage(const std::string& message) const {
  
}

void Shop::PurchaseAndUpgrade(Builder& builder, Property& property) const {
  builder.GetInventory() -= property.GetUpgradeCost();
  property.Upgrade(builder);
}

std::optional<std::string> Shop::CanBuildRoad(Builder& builder, Layout& layout, int roadIndex) const {
  assert(0 <= roadIndex && roadIndex < int(layout.GetRoads().size()));

  const auto& roadGraph = layout.GetRoadGraph();
  const auto& residences = layout.GetResidences();
  const auto& roads = layout.GetRoads(); 

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

    for (int i = 0; i < layout.GetRoads().size(); ++i) {
      if (!builder.OwnRoad(i)) {
        continue;
      }

      //check if there's a property sandwitched in between
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

std::optional<std::string> Shop::CanBuildResidence(Builder& builder, Layout& layout, int residenceIndex) const{
  assert(0 <= residenceIndex && residenceIndex < layout.GetResidences().size());

  //initially not owned by anyone 
  const auto& roadGraph = layout.GetRoadGraph(); 
  const auto& residences = layout.GetResidences(); 
  const auto& property = residences[residenceIndex];

  //check if not owned by anyone    
  if(property->GetOwner()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  //check there's no adjacent property
  for(int i = 0; i < layout.GetRoads().size(); ++i){
    if((roadGraph[i][0] == residenceIndex && residences[roadGraph[i][1]]->GetOwner()) ||
       (roadGraph[i][1] == residenceIndex && residences[roadGraph[i][0]]->GetOwner())) {
      return NOT_VALID_BUILD_ERROR_MSG; 
    }
  }

  //check there's an adjacent road
  int index = 0;
  const bool hasAdjacent = std::any_of(roadGraph.begin(), roadGraph.end(), [&](const auto& roadEdge) mutable {
    return (roadEdge[0] == residenceIndex || roadEdge[1] == residenceIndex) && builder.OwnRoad(index++);
  });

  if (!hasAdjacent) {
    return NOT_VALID_BUILD_ERROR_MSG; 
  }

  //make sure the housing is affordable
  if(!builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
  }

  return {};
}

std::optional<std::string> Shop::CanImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  assert(0 <= residenceIndex && residenceIndex < int(layout.GetResidences().size()));

  //initially not owned by anyone 
  const auto& property = layout.GetResidences()[residenceIndex]; 

  //must be owned and have next tier
  if (property->GetOwner() != &builder || property->CanUpgradeToNextTier()) {
    return NOT_VALID_BUILD_ERROR_MSG;
  }

  if(!builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR_MSG;
  }

  return {};
}

bool Shop::CanTrade(Builder& instigator, Builder& subject, const Inventory& trade) const {
  return instigator.GetInventory().CanAfford(trade) && subject.GetInventory().CanAfford(trade * -1);
}


bool Shop::BuildRoad(Builder& builder, Layout& layout, int roadIndex) const {
  if (auto error = CanBuildRoad(builder, layout, roadIndex); error) {
    BroadcastMessage(error.value());
    return false;
  }

  const auto& property = layout.GetRoads()[roadIndex];
  PurchaseAndUpgrade(builder, *property);
  builder.AddRoad(roadIndex, *property);
  return true;
}

bool Shop::BuildResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  if (auto error = CanBuildResidence(builder, layout, residenceIndex); error) {
    BroadcastMessage(error.value());
    return false;
  }
  const auto& property = layout.GetResidences()[residenceIndex];
  PurchaseAndUpgrade(builder, *property);
  builder.AddResidence(residenceIndex, *property);
  return true;
}

bool Shop::ImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  if (auto error = CanImproveResidence(builder, layout, residenceIndex); error) {
    BroadcastMessage(error.value());
    return false;
  }
  //only improve, does not add to the property set
  PurchaseAndUpgrade(builder, *layout.GetResidences()[residenceIndex]);
  return true;
}

bool Shop::Trade(Builder& instigator, Builder& subject, const Inventory& trade) const {
  if (CanTrade(instigator, subject, trade)) {
    instigator.GetInventory() -= trade; 
    subject.GetInventory() += trade; 
    return true; 
  }
  return false; 
}

Shop::~Shop() {}
