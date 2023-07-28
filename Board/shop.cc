#include "shop.h"
#include "Layout/layout.h"
#include "../Builder/builder.h"

using namespace std;

std::optional<std::string> Shop::CanBuildRoad(Builder& builder, int roadIndex, Layout& layout) {
  return "no, you can't purchase it, don't ask why";
}

std::optional<std::string> Shop::CanBuildResidence(Builder& builder, int residenceIndex, Layout& layout) {
  return "no, you can't purchase it, don't ask why";
}


bool Shop::BuildRoad(Builder& builder, int roadIndex, Layout& layout) {
  auto error = CanBuildRoad(builder, roadIndex, layout);
  if (error) {
    //notice the layout view
    return false;
  }

  return true;
}

bool Shop::BuildResidence(Builder& builder, int residenceIndex, Layout& layout) {
  auto error = CanBuildResidence(builder, residenceIndex, layout);
  if (error) {
    //notice the layout view
    return false;
  }

  return true;
}

bool Shop::Trade(Builder& instigator, Builder& subject) {
  return true;
}


Shop::~Shop() {
  
}
