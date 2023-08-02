#include "layout.h"
#include "../../Tile/tile_factory.h"
#include "../../Building/Road/vacant_road.h"
#include "../../Building/Residence/vacant_land.h"
#include "../../Robber/geese.h"
#include "../../Builder/builder.h"
#include <random>
#include <chrono>

using namespace std;

const vector<vector<int>>& Layout::GetRoadGraph() {
  /*
    Return the incident edge graph representation of the roads.
    It stores the residenceIndex that the edge is incident to.

    Ex:
    road 27 is a path from residence 20 to residence 21
    mapping[27] = {20, 21}

    |20|--27--|21|
      |         |
     31    9   32
      |  BRICK  |
    |26|   2  |27|
      |         |
     39        40
      |         |
    |32|--44--|33|
  */
  static const vector<vector<int>> mapping = {
    {0, 1},   {0, 3},   {1, 4},   {2, 3},   {4, 5},   {2, 7},   {3, 8},   {4, 9},   {5, 10},
    {6, 7},   {8, 9},   {10, 11}, {6, 12},  {7, 13},  {8, 14},  {9, 15},  {10, 16}, {11, 17},
    {13, 14}, {15, 16}, {12, 18}, {13, 19}, {14, 20}, {15, 21}, {16, 22}, {17, 23}, {18, 19},
    {20, 21}, {22, 23}, {18, 24}, {19, 25}, {20, 26}, {21, 27}, {22, 28}, {23, 29}, {25, 26},
    {27, 28}, {24, 30}, {25, 31}, {26, 32}, {27, 33}, {28, 34}, {29, 35}, {30, 31}, {32, 33},
    {34, 35}, {30, 36}, {31, 37}, {32, 38}, {33, 39}, {34, 40}, {35, 41}, {37, 38}, {39, 40},
    {36, 42}, {37, 43}, {38, 44}, {39, 45}, {40, 46}, {41, 47}, {42, 43}, {44, 45}, {46, 47},
    {43, 48}, {44, 49}, {45, 50}, {46, 51}, {48, 49}, {50, 51}, {49, 52}, {50, 53}, {52, 53}
  }; 

  return mapping;
}

const std::vector<int>& Layout::GetAdjacentTilesByResidence(int residenceIndex) const {
  /**
    Returns the indices of tiles that's around the residence given by the residence index.
    This is the inverse of GetAdjacentResidencesByTile().
  */
  static vector<vector<int>> mapping;
  
  if (residenceIndex >= int(mapping.size())) {
    mapping.resize(residenceIndex + 1);
  }

  if (mapping[residenceIndex].empty()) {
    
    //not in cache, compute the tiles
    for (int i = 0; i < int(tiles.size()); ++i) {
      const auto& res = GetAdjacentResidencesByTile(i);
      if (any_of(res.begin(), res.end(), [&](int index) { return index == residenceIndex; })) {
        mapping[residenceIndex].push_back(i);
      }
    }
  }

  return mapping[residenceIndex];
}

const std::vector<int>& Layout::GetAdjacentResidencesByTile(int index) const {
  /*
    Returns the indices of residence that surrounds the tile given by the tile index.
    Each tile should have at least one nearby residence, and vice versa.

    Ex:
    Tile index 9 has residence 20, 21, 26, 27, 32, 33 around it.
    mapping[9] = {20, 21, 26, 27, 32, 33}

    |20|--27--|21|
      |         |
     31    9   32
      |  BRICK  |
    |26|   2  |27|
      |         |
     39        40
      |         |
    |32|--44--|33|
  */
  static const vector<vector<int>> mapping = {
    {0, 1, 3, 4, 8, 9},
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

  return mapping[index];
}

void Layout::GenerateTiles(unsigned seed) {
  /*
   3 WIFI, 3 HEAT, 4 BRICK, 4 ENERGY, 4 GLASS, 1 PARK
   Park tile has tile number 7
   One tile has tile number 2
   One tile has tile number 12
   Remaining tiles values: 3, 4, 5, 6, 8, 9, 10, 11
  */

  //generate the tile numbers
  vector<int> tileNums = {7, 2, 12, 3, 4, 5, 6, 8, 9, 10, 11, 3, 4, 5, 6, 8, 9, 10, 11};
  default_random_engine engine(seed);
  shuffle(tileNums.begin() + 1, tileNums.end(), engine);
  
  //create tiles, then shuffle the physical structure order
  const vector<TileFactory::Type> types = {
    TileFactory::PARK,
    TileFactory::WIFI, TileFactory::WIFI, TileFactory::WIFI,
    TileFactory::HEAT, TileFactory::HEAT, TileFactory::HEAT,
    TileFactory::BRICK, TileFactory::BRICK, TileFactory::BRICK, TileFactory::BRICK,
    TileFactory::ENERGY, TileFactory::ENERGY, TileFactory::ENERGY, TileFactory::ENERGY,
    TileFactory::GLASS, TileFactory::GLASS, TileFactory::GLASS, TileFactory::GLASS,
  };
  for (int i = 0; i < int(types.size()); ++i) {
    tiles.push_back(TileFactory::CreateTile(types[i], tileNums[i]));
  }
  shuffle(tiles.begin(), tiles.end(), engine);
}

void Layout::GenerateRoads() {
  constexpr int ROAD_COUNT = 72;
  for (int i = 0; i < ROAD_COUNT; ++i) {
    roads.push_back(make_unique<Property>(make_unique<VacantRoad>()));
  }
}

void Layout::GenerateResidences() {
  constexpr int RESIDENCE_COUNT = 54;
  for (int i = 0; i < RESIDENCE_COUNT; ++i) {
    residences.push_back(make_unique<ResidenceProperty>(make_unique<VacantLand>()));
  }
}

void Layout::GenerateBuilders() {
  constexpr int BUILDER_COUNT = 4;
  for (int i = 0; i < BUILDER_COUNT; ++i) {
    builders.push_back(make_unique<Builder>(ColourEnum::Type(i)));
  }
}

void Layout::GenerateRobber() {
  const int parkTileIndex = distance(tiles.begin(), find_if(tiles.begin(), tiles.end(), [](auto& tile) { return tile->GetNumber() == 7; }));
  robber = make_unique<Geese>(parkTileIndex);
}

/**
  Generate layout by seeding
*/
void Layout::GenerateLayout(unsigned seed) {
  tiles.clear();
  roads.clear();
  residences.clear();
  builders.clear();
  robber.reset();
  GenerateTiles(seed);
  GenerateRoads();
  GenerateResidences();
  GenerateBuilders();
  GenerateRobber();
}

const std::vector<std::unique_ptr<Tile>>& Layout::GetTiles() const{
  return tiles;
}

const std::vector<std::unique_ptr<Property>>& Layout::GetRoads() const {
  return roads; 
}

const std::vector<std::unique_ptr<ResidenceProperty>>& Layout::GetResidences() const {
  return residences;
}

const std::vector<std::unique_ptr<Builder>>& Layout::GetBuilders() const {
  return builders;
}

Robber& Layout::GetRobber() const {
  return *robber;
}

string Layout::SaveData() const {

  //builders
  string saveData;
  for (const auto& builder : builders) {
    saveData += builder->SaveData() + '\n';
  }

  //tiles
  static const map<std::string, int> tileType = { {"BRICK", 0}, {"ENERGY", 1}, {"GLASS", 2}, {"HEAT", 3}, {"WIFI", 4}, {"PARK", 5} }; 
  for(const auto& tile : tiles) {
    saveData += Format("%v %v ", tileType.find(tile->GetTileType())->second, tile->GetNumber());
  }
  saveData += '\n';

  //robber
  saveData += robber->SaveData();
  return saveData;
}

void Layout::LoadData(std::istream& file) {
  vector<stringstream> data, data2;
  for (string line; getline(file, line);) {
    Log("loaded layout data %v\n", line);
    data.push_back(stringstream(line));
    data2.push_back(stringstream(std::move(line)));
  }
  

  //construct tiles
  int tileDataIndex = (data.size() == 1 ? 0 : data.size() - 2);
  for (int type, tileNumber; data[tileDataIndex] >> type >> tileNumber;) {
    Log("tile type %v, number %v\n", type, tileNumber);
    tiles.push_back(TileFactory::CreateTile(TileFactory::Type(type), tileNumber));
  }

  GenerateRoads();
  GenerateResidences();
  GenerateBuilders();
  GenerateRobber();
  
  Log("construct residence\n");
  for (int i = 0; i < int(data.size()) - 2; ++i) {
    //filter out the inventory and road letter 'r'
    string c;
    while (data[i] >> c) if (c == "r") break;

    //construct roads
    while (data[i] >> c) {
      if (c == "h") break;
      int roadIndex = stoi(c);
      roads[roadIndex]->Upgrade(*builders[i]);
      builders[i]->AddRoad(roadIndex, *roads[roadIndex]);
    }
    
    //construct residences
    int residenceIndex;
    char type;
    while (data[i] >> residenceIndex >> type) {
      while(string(*(residences[residenceIndex]))[1] != type) {
        residences[residenceIndex]->Upgrade(*builders[i]); 
      }
      builders[i]->AddResidence(residenceIndex, *residences[residenceIndex]);

      //connect the observer
      for (int tileIndex : GetAdjacentTilesByResidence(residenceIndex)) {
        tiles[tileIndex]->Attach(residences[residenceIndex].get());
      }
    }
  }

  if (data.size() > 1) {
    Log("construct builder and robber\n");
    for (int i = 0; i < int(data.size()) - 2; ++i) {
      builders[i]->LoadData(data2[i]);
    }
    robber->LoadData(data.back());
  }
}

Layout::Layout() : SaveLoadable() {}

Layout::~Layout() {}
