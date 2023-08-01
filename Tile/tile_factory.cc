#include "tile_factory.h"
#include "brick_tile.h"
#include "energy_tile.h"
#include "glass_tile.h"
#include "heat_tile.h"
#include "wifi_tile.h"
#include "park_tile.h"
#include "../Utility/print.h"

using namespace std;

unique_ptr<Tile> TileFactory::CreateTile(Type tileType, int tileNumber) {
  switch (tileType) {
    case BRICK: return make_unique<BrickTile>(tileNumber);
    case ENERGY: return make_unique<EnergyTile>(tileNumber);
    case GLASS: return make_unique<GlassTile>(tileNumber);
    case HEAT: return make_unique<HeatTile>(tileNumber);
    case WIFI: return make_unique<WifiTile>(tileNumber);
    case PARK: return make_unique<ParkTile>(tileNumber);
    default: Assert(false, Format("invalid tile type %v", tileType)); 
  }
  return nullptr;
}
