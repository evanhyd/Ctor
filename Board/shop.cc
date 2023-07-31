#include "shop.h"
#include "Layout/layout.h"
#include "../Builder/builder.h"
#include "../Utility/print.h"

using namespace std;

const std::string Shop::NOT_VALID_BUILD_ERROR = "You cannot build here.\n";
const std::string Shop::NOT_SUFFICIENT_RESOURCES_ERROR = "You do not have enough resources.\n";

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
    return NOT_VALID_BUILD_ERROR;
  }

  //check the road has no owner
  if (roads[roadIndex]->GetOwner()) {
    return NOT_VALID_BUILD_ERROR;
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
        const int r0 = roadGraph[roadIndex][DX[j]];
        const int r1 = roadGraph[i][DY[j]];
        const Builder* owner = residences[r0]->GetOwner(); 
        if (r0 == r1 && (!owner || owner == &builder)) {
          return true;
        }
      }
    }
    return false;
  };

  if(!CheckResidence() && !CheckRoad()) {
    return NOT_VALID_BUILD_ERROR;
  }

  if(!builder.GetInventory().CanAfford(roads[roadIndex]->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR;
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
    Log("invalid residence index %v\n", residenceIndex);
    return NOT_VALID_BUILD_ERROR;
  }

  //check if not owned by anyone    
  if (property->GetOwner()) {
    Log("residence owned by %v\n", ColourEnum::Name(property->GetOwner()->GetColour()));
    return NOT_VALID_BUILD_ERROR;
  }

  //check there's no adjacent property
  for (int i = 0; i < int(roads.size()); ++i){
    if((roadGraph[i][0] == residenceIndex && residences[roadGraph[i][1]]->GetOwner()) ||
       (roadGraph[i][1] == residenceIndex && residences[roadGraph[i][0]]->GetOwner())) {
      Log("too crowded\n");
      return NOT_VALID_BUILD_ERROR; 
    }
  }

  //check there's an adjacent road
  int index = -1;
  const bool hasAdjacent = initialPlacement || std::any_of(roadGraph.begin(), roadGraph.end(), [&](const auto& roadEdge) {
    ++index;
    return (roadEdge[0] == residenceIndex || roadEdge[1] == residenceIndex) && builder.OwnRoad(index);
  });

  if (!hasAdjacent) {
    Log("no adjacent road\n");
    return NOT_VALID_BUILD_ERROR;
  }

  //make sure the housing is affordable
  if(!initialPlacement && !builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR;
  }

  return {};
}

Shop::Error Shop::CanImproveResidence(Builder& builder, Layout& layout, int residenceIndex) const {
  const auto& residences = layout.GetResidences();

  //check index bound
  if (residenceIndex < 0 || residenceIndex >= int(residences.size())) {
    return NOT_VALID_BUILD_ERROR;
  }

  //must be owned and have next tier
  const auto& property = residences[residenceIndex]; 
  if (property->GetOwner() != &builder || !property->CanUpgradeToNextTier()) {
    return NOT_VALID_BUILD_ERROR;
  }

  if(!builder.GetInventory().CanAfford(property->GetUpgradeCost())) {
    return NOT_SUFFICIENT_RESOURCES_ERROR;
  }

  return {};
}

Shop::Error Shop::CanTrade(Builder& instigator, Builder& subject, const Inventory& offer1, const Inventory& offer2) const {
  if (!instigator.GetInventory().CanAfford(offer1)) {
    return Format("Builder %v does not have enough resources\n", ColourEnum::Name(instigator.GetColour()));
  }
  if (!subject.GetInventory().CanAfford(offer2)) {
    return Format("Builder %v does not have enough resources\n", ColourEnum::Name(subject.GetColour()));
  }
  return {};
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
  const auto& tiles = layout.GetTiles();
  PurchaseAndUpgrade(builder, *property, initialPlacement);
  for (int tileIndex : layout.GetAdjacentTilesByResidence(residenceIndex)) {
    tiles[tileIndex]->Attach(property.get());
  }
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

Shop::Error Shop::Trade(Builder& instigator, Builder& subject, const Inventory& offer1, const Inventory& offer2) const {
  if (auto error = CanTrade(instigator, subject, offer1, offer2); error) {
    return error;
  }
  instigator.GetInventory() += offer2 - offer1; 
  subject.GetInventory() += offer1 - offer2; 
  return {}; 
}

Shop::Error Shop::BankTrade(Builder& instigator, const Inventory& offer) const {
  if (!instigator.GetInventory().CanAfford(offer)) {
    return Format("Builder %v does not have enough resources\n", ColourEnum::Name(instigator.GetColour()));
  }
  instigator.GetInventory() -= offer;; 
  return {}; 
}

Shop::~Shop() {}
