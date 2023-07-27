#include "layout.h"
#include "../../Tile/brick_tile.h"
#include "../../Tile/energy_tile.h"
#include "../../Tile/glass_tile.h"
#include "../../Tile/heat_tile.h"
#include "../../Tile/wifi_tile.h"
#include "../../Tile/park_tile.h"
#include "../../Building/Road/vacant_road.h"
#include "../../Building/Residence/vacant_land.h"
#include "../../Builder/human_builder.h"
#include "../../Robber/geese.h"
#include "../../Utility/random.h"

using namespace std;

std::vector<int> Layout::GetAdjacentTiles(int residenceIndex) const {

  //find the tiles that contains this residence
  //bad time complexity, but should suffice since the graph size is small
  //can replace with hardcoded value if performance is an issue
  vector<int> tilesIndex;
  for (int i = 0; i < TILE_COUNT; ++i) {
    const auto mapping = GetAdjacentResidences(i);
    if (any_of(mapping.begin(), mapping.end(), [&](int index) { return index == residenceIndex; })) {
      tilesIndex.push_back(i);
    }
  }
  return tilesIndex;
}

std::vector<int> Layout::GetAdjacentResidences(int tileIndex) const {
  static const vector<vector<int>> mapping = {
    {0, 1, 3, 4, 8, 0},
    {2, 3, 7, 8, 13, 14},
    {4, 5, 9, 10, 15, 16},
    {6, 7, 12, 13, 18, 19},
    {8, 9, 14, 15, 20, 21},
    {10, 11, 16, 17, 22, 23},
    {13, 14, 19, 20, 25, 26},
    {15, 16, 21, 22, 27, 28},
    {18, 19, 24, 25, 30, 31},
    {20, 21, 26, 27, 32, 33},
    {22, 23, 28, 29, 34, 35},
    {25, 26, 31, 32, 37, 38},
    {27, 28, 33, 34, 39, 40},
    {30, 31, 36, 37, 42, 43},
    {32, 33, 38, 39, 44, 45},
    {34, 35, 40, 41, 46, 47},
    {37, 38, 43, 44, 48, 49},
    {39, 40, 45, 46, 50, 51},
    {44, 45, 49, 50, 52, 53},
  };

  return mapping[tileIndex];
}


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
  const vector<int> candidates = {3, 4, 5, 6, 8, 9, 10, 11};
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

  //generate roads, residence, players, robber
  generate_n(back_inserter(roads), ROAD_COUNT, []() { return make_unique<Property>(make_unique<VacantRoad>()); });
  generate_n(back_inserter(residences), RESIDENCE_COUNT, []() { return make_unique<ResidenceProperty>(make_unique<VacantLand>()); });
  generate_n(back_inserter(builders), RESIDENCE_COUNT, []() { return make_unique<ResidenceProperty>(make_unique<HumanBuilder>()); });
  const int parkTileIndex = distance(tiles.begin(), find_if(tiles.begin(), tiles.end(), [](auto& tile) { return tile->GetNumber() == 7; }));
  robber = make_unique<Geese>(parkTileIndex);
}

void Layout::GenerateRandomLayout() {
  GenerateRandomLayoutImpl();
}

bool Layout::ImportLayout(const string& fileName) {
  return false;
}

Layout::Layout() {}

Layout::~Layout() {}
