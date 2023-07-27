#include "shop.h"



using namespace std;

optional<string> Shop::CanBuildRoad(int roadIndex, Builder& builder){
    //need to check if the road slot is empty 
    //need to iterate through all the builders and check... do I just assume the number of builders won't change? 


    //checking if roadIndex is available to be built on 
    const bool roadEdgeAvailable = true; 
    for(int player = blue; player <= yellow; ++player){
        if(any_of(layout.builder[player]->roads.begin(), layout.builder[player]->roads.end(), [&](auto& p){
            return p.first == roadIndex; 
        }); ){
            roadEdgeAvailable = false; 
        }
    }

    //I feel so wrong writing this code  


    vector<int> adjacentResidences = layout.GetAdjacentResidencesFromEdges();
    vector<int> adjacentEdges = layout.GetAdjacentEdgesFromEdges(); 

    const bool hasPlayerResidence = any_of(adjacentResidences.begin(), adjacentResidences.end(), [&](auto& index) {
        return builder.OwnResidence(index);
    });

    const bool hasPlayerRoad = any_of(adjacentEdges.begin(), adjacentEdges.end(), [&](auto& index) {
        return builder.OwnRoad(index);
    });


    //if there are no roads or residences of that player adjacent
    if (!hasPlayerRoad && !hasPlayerResidence) {
        return "no road or residence adjacent/nearby to build roads";
    }

    const bool allBlocked = all_of(adjacentEdges.begin(), adjacentEdges.end(), [&](auto& adjacentIndex){
        //builder doesn't own adjacent road 
        if(!builder.OwnRoad(adjacentIndex)) return true; 
        int sandwichedResidenceIndex = layout.GetResidencesBetweenEdges(roadIndex, adjacentIndex); 

        //return true if builder doesn't own sandwiched residence else return false
        return !builder.OwnResidence(sandwichedResidenceIndex); 
    }); 

    //if path to the road are all blocked 
    if(allBlocked) {
        return "road blocked by other player structures"; 
    }

    //need a way to get the cost for building roads 

    //now need to check for resources 
    if(builder.inventory.CanAfford())


    //iterate through all adjacent edges that belong to you... 
    //if all of them sandwich a residence of another player return false 




    //I am confused, you must build roads "next to" your existing road or residence 
    //and you can sandwich another residence(that is not yours) with your roads 

    //now make sure road is not blocked by residence unless can be approached by another side... 

    //so need to create pairs of road 


    //no residence doesn't mean fail because there could be road same with road... so we need to or them 

    //brb washroom

    /*
	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Property>> roads;
	std::vector<std::unique_ptr<ResidenceProperty>> residences;
	std::vector<std::unique_ptr<Builder>> builders;
	std::unique_ptr<Robber> robber;
    */

    /*
      ColourEnum colour;
  Inventory inventory;
  std::vector<PropertyInfo<Property>> roads;
  std::vector<PropretyInfo<ResidenceProperty>> residences; 

  const Dice* dice;
    */




    //iterate through player residence and check against adjacentResidences 


    //:( n)

    //need to be adjacent to one of players roads or one of player's residences 
    //need to not build through residence of another player 

    

    //shop needs access to layout to check if they can build roads by checking adjacent tiles 

    //need some get adjacent edges from one edge function 

    //also need a function that gets adjacent vertices from an edge 

    
}



bool Shop::CanBuildRes(int index, ColorEnum player){
    //
}
    

void Shop::BuildRoad(int index, ColorEnum player){
    if(!CanBuildRoad(index, player)){
        return; 
    }

    //shop needs access to layout to notify that something has been built 
    //shop needs access to player to notify them to add built road to their array 
}


Shop::Shop(Layout& layout) : layout{layout}{

}
