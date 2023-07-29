#include "stream_view.h"
#include "../Layout/layout.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

StreamView::StreamView(std::ostream& buffer) : buffer{buffer} {}

string IntFormat(int i) {
  if (i < 10) return " " + to_string(i);
  else return to_string(i);
}

string StreamView::VF(int vertex) {
  const std::unique_ptr<ResidenceProperty>& residence = layout->GetResidence(vertex);
  if (residence->GetOwner() == nullptr) {
    return IntFormat(vertex);
  } else {
    return to_string(residence);
  }
}

string StreamView::EF(int edge) {
  const std::unique_ptr<Property>& road = layout->GetRoad(edge);
  if (road->GetOwner() == nullptr) {
    return IntFormat(edge);
  } else {
    return to_string(road);
  }
}

// GOOSE is At this tile
string StreamView::GA(int tile) {
  const std::unique_ptr<Robber>& robber = layout->GetRobber();
  if (robber->GetTileIndex() == tile) {
    return to_string(robber);
  } else {
    return "     ";
  }
}



void StreamView::RenderImpl(Layout& layout){
  // const vector<vector<int>>& road_mapping = layout.GetRoadGraph();
  // map<string, int> reverse_road_mapping;
  // for (int i = 0; i < road_mapping.size(); i++) {
  //   reverse_road_mapping.insert({RoadKey(road_mapping[i][0], road_mapping[i][1]), i});
  // }


  // char display[41][54]





  string display = "";
  display += "                    | 0|-- 0--| 1|\n";
  display += "                      |         |\n";
  display += "                      1    0    2\n";
  display += "                      |  BRICK  |\n";
  display += "          | 2|-- 3--| 3|   3  | 4|-- 4--| 5|\n";
  display += "            |         |  "+GA(0)+"  |         |\n";
  display += "            5    1    6         7    2    8\n";
  display += "            | ENERGY  |         |  HEAT   |\n";
  display += "| 6|-- 9--| 7|  10  | 8|--10--| 9|   5  |10|--11--|11|\n";
  display += "  |         |  "+GA(1)+"  |         |  "+GA(2)+"  |         |\n";
  display += " 12    3   13        14    4   15        16    5   17\n";
  display += "  | ENERGY  |         |  PARK   |         |  HEAT   |\n";
  display += "|12|   4  |13|--18--|14|      |15|--19--|16|  10  |17|\n";
  display += "  |  "+GA(3)+"  |         |  "+GA(4)+"  |         |  "+GA(5)+"  |\n";
  display += " 20        21    6   22        23    7   24        25\n";
  display += "  |         |  GLASS  |         |  BRICK  |         |\n";
  display += "|18|--26--|19|  11  |20|--27--|21|   3  |22|--28--|23|\n";
  display += "  |         |  "+GA(6)+"  |         |  "+GA(7)+"  |         |\n";
  display += " 29    8   30        31    9   32        33   10   34\n";
  display += "  |  HEAT   |         |  BRICK  |         |  BRICK  |\n";
  display += "|24|   8  |25|--35--|26|   2  |27|--36--|28|   6  |29|\n";
  display += "  |  "+GA(8)+"  |         |  "+GA(9)+"  |         |  "+GA(10)+"  |\n";
  display += " 37        38   11   39        40   12   41        42\n";
  display += "  |         | ENERGY  |         |  WIFI   |         |\n";
  display += "|30|--43--|31|   8  |32|--44--|33|  12  |34|--45--|35|\n";
  display += "  |         |  "+GA(11)+"  |         |  "+GA(12)+"  |         |\n";
  display += " 46   13   47        48   14   49        50   15   51\n";
  display += "  | ENERGY  |         |  WIFI   |         |  GLASS  |\n";
  display += "|36|   5  |37|--52--|38|  11  |39|--53--|40|   4  |41|\n";
  display += "  |  "+GA(13)+"  |         |  "+GA(14)+"  |         |  "+GA(15)+"  |\n";
  display += " 54        55   16   56        57   17   58        59\n";
  display += "  |         |  WIFI   |         |  GLASS  |         |\n";
  display += "|42|--60--|43|   6  |44|--61--|45|   9  |46|--62--|47|\n";
  display += "            |  "+GA(16)+"  |         |  "+GA(17)+"  |\n";
  display += "           63        64   18   65        66\n";
  display += "            |         |  GLASS  |         |\n";
  display += "          |48|--67--|49|   9  |50|--68--|51|\n";
  display += "                      |  "+GA(18)+"  |\n";
  display += "                     69        70\n";
  display += "                      |         |\n";
  display += "                    |52|--71--|53|\n";

  print(display);
}

void StreamView::Notify(const string& data) {

}
