#include "geese.h"
#include "../Inventory/inventory.h"
#include "../Builder/builder.h"
#include "../Board/Layout/layout.h"
#include "../Board/board.h"
#include "../Utility/print.h"

#include <random> 
#include <chrono>
#include <algorithm>

using namespace std;

Inventory Geese::CalculateStolenInventory(const Inventory& inventory) const {
  Assert(inventory.GetTotal() >= RESOURCE_LIMIT, Format("inventory size %v does not meet the limit %v", inventory.GetTotal(), RESOURCE_LIMIT));

  //flatten inventory to resources
  vector<ResourceEnum::Type> resources;
  for (const auto&[resource, count] : inventory) {
    fill_n(back_inserter(resources), count, resource);
  }

  //shuffle and remove half
  default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
  shuffle(resources.begin(), resources.end(), engine);
  resources.resize(resources.size() / 2);

  //fill back the inventory;
  vector<int> collectTable(ResourceEnum::COUNT);
  for (int type : resources) {
    ++collectTable[type];
  }
  Inventory stolen(0, 0, 0, 0, 0);
  for (int type = 0; type < ResourceEnum::COUNT; ++type) {
    stolen += Inventory(ResourceEnum::Type(type), collectTable[type]);
  }
  return stolen;
}

void Geese::ApplyResourceModifier(Inventory& inventory) const {
  inventory = Inventory(0, 0, 0, 0, 0);
}

void Geese::ApplyBoardModifier(Board& board) const {
  //player with resources above the goose limit will lose half of the inventory
  for (auto& builder : board.GetLayout().GetBuilders()) {
    if (builder->GetInventory().GetTotal() >= RESOURCE_LIMIT) {
      Inventory stolen = CalculateStolenInventory(builder->GetInventory()); 
      builder->GetInventory() -= stolen; 
      
      board.NotifyAll(Format("Builder %v loses %v resources to the geese. They lose:\n", ColourEnum::Name(builder->GetColour()), stolen.GetTotal())); 
      for (const auto& [type, count] : stolen) {
        board.NotifyAll(Format("%v %v\n", count, ResourceEnum::Name(type)));
      }
    }
  }
}

Geese::operator string() const {
	return "GEESE";
}
