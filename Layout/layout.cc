#include "layout.h"
#include "tile.h"
#include "road.h"
#include "residence.h"
#include "builder.h"
#include "geese.h"

Layout::Layout() : robber{std::make_unique<Geese>()} {}