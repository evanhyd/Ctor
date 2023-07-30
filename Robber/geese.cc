#include "geese.h"
#include "../Inventory/inventory.h"
#include "../Builder/builder.h"

#include <random> 

using namespace std;

Inventory Geese::GetRandomHalfInventory(Inventory& inventory) const {

}

void Geese::ApplyResourceModifier(Inventory& inventory) const {
  inventory = Inventory(0, 0, 0, 0, 0);
}


void Geese::ApplyBuilderModifier(const std::vector<std::unique_ptr<Builder>>& allBuilders, Builder& builder) const {
  //all builders with more than 10 resources are going to lose half of their resources 
  for(auto& builder : allBuilders){
    if(builder->GetInventory().GetTotal() >= 10){
      Inventory halfInventory = GetRandomHalfInventory(builder->GetInventory()); 
      builder->GetInventory() -= halfInventory; 
      
      //now how do we output 
      //Builder <colour> loses <numResourcesLost> resources to the geese. They lose:
      //<numResource> <resourceName>
    } 
  }
}

Geese::operator string() const {
	return "GEESE";
}
