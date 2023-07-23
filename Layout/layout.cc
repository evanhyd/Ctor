#include "layout.h"
#include "brick_tile.h"
#include "energy_tile.h"
#include "glass_tile.h"
#include "heat_tile.h"
#include "wifi_tile.h"
#include "park_tile.h"
#include "vacant_road.h"
#include "vacant_land.h"
#include "human_builder.h"
#include "geese.h"
#include "Utility/random.h"

using namespace std;

void Layout::GenerateRandomLayoutImpl() {
  /**
   3 WIFI, 3 HEAT, 4 BRICK, 4 ENERGY, 4 GLASS, 1 PARK
   Park tile has tile number 7
   One tile has tile number 2
   One tile has tile number 12
   Remaining tiles values: 3, 4, 5, 6, 8, 9, 10, 11
  */

  //generate tile numbers
  vector<int> tileNums(TILE_COUNT);
  tileNums[0] = 7;
  tileNums[1] = 2;
  tileNums[2] = 12;
  vector<int> candidates = {3, 4, 5, 6, 8, 9, 10, 11};
  Random::Sample(candidates.begin(), candidates.end(), tileNums.begin() + 3, TILE_COUNT - 3);
  Random::Shuffle(tileNums.begin() + 1, tileNums.end());
  
  //generate tiles
  tiles = {
    make_unique<ParkTile>(tileNums[0]),
    make_unique<WifiTile>(tileNums[1]), make_unique<WifiTile>(tileNums[2]), make_unique<WifiTile>(tileNums[3]),
    make_unique<HeatTile>(tileNums[4]), make_unique<HeatTile>(tileNums[5]), make_unique<HeatTile>(tileNums[6]),
    make_unique<BrickTile>(tileNums[7]), make_unique<BrickTile>(tileNums[8]), make_unique<BrickTile>(tileNums[9]), make_unique<BrickTile>(tileNums[10]),
    make_unique<EnergyTile>(tileNums[11]), make_unique<EnergyTile>(tileNums[12]), make_unique<EnergyTile>(tileNums[13]), make_unique<EnergyTile>(tileNums[14]),
    make_unique<GlassTile>(tileNums[15]), make_unique<GlassTile>(tileNums[16]), make_unique<GlassTile>(tileNums[17]), make_unique<GlassTile>(tileNums[18]),
  };
  Random::Shuffle(tiles.begin(), tiles.end());

  //generate roads
  generate_n(back_inserter(roads), ROAD_COUNT, []() { return make_unique<Property>(make_unique<VacantRoad>()); });

  //generate residence
  generate_n(back_inserter(residences), RESIDENCE_COUNT, []() { return make_unique<ResidenceProperty>(make_unique<VacantLand>()); });

  //generate players
  generate_n(back_inserter(builders), RESIDENCE_COUNT, []() { return make_unique<ResidenceProperty>(make_unique<HumanBuilder>()); });

  //generate robber
  int robberIndex = distance(tiles.begin(), find_if(tiles.begin(), tiles.end(), [](auto& tile) { return tile->GetNumber() == 7; }));
  robber = make_unique<Geese>(robberIndex);
}

void Layout::GenerateRandomLayout() {
  GenerateRandomLayoutImpl();
}

bool Layout::ImportLayout(const string& fileName) {
  return false;
}

Layout::Layout() {}

Layout::~Layout() {}
