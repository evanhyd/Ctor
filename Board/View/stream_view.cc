#include "stream_view.h"
#include "../Layout/layout.h"
#include "../../Utility/print.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

StreamView::StreamView(std::ostream& buffer) : buffer{buffer} {}

// Format Vertex
string StreamView::FV(int vertex, const Layout& layout) {
  const std::unique_ptr<ResidenceProperty>& residence = layout.GetResidences()[vertex];
  return (residence->GetOwner() ? string(*residence) : Format("%2v", vertex));
}

// Format Edge
string StreamView::FE(int edge, const Layout& layout) {
  const std::unique_ptr<Property>& road = layout.GetRoads()[edge];
  return (road->GetOwner() ? string(*road) : Format("%2v", edge));
}

// Format Robber
string StreamView::FR(int tile, const Layout& layout) {
  const Robber& robber = layout.GetRobber();
  return (robber.GetTileIndex() == tile ? string(robber) : "     ");
}

//Format Tile Name
string StreamView::FTN(int index, const Layout& layout) {
  return layout.GetTiles()[index]->GetTileType();
}

//Format Tile Number
string StreamView::FTNum(int index, const Layout& layout) {
  int number = layout.GetTiles()[index]->GetNumber();
  if (number == 7) return "  ";
  return Format("%v", layout.GetTiles()[index]->GetNumber());
}

void StreamView::RenderImpl(const Layout& l) {
  buffer << Format("                    |%2v|--%2v--|%2v|\n", FV(0, l), FE(0, l), FV(1, l));
  buffer << Format("                      |         |\n");
  buffer << Format("                     %2v    0   %2v\n", FV(1, l),  FV(2, l));
  buffer << Format("                      | %6v  |\n", FTN(0, l));
  buffer << Format("          |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(2, l), FE(3, l), FV(3, l), FTNum(0, l), FV(4, l), FE(4, l), FV(5, l));
  buffer << Format("            |         |  %5v  |         |\n", FR(0, l));
  buffer << Format("           %2v    1   %2v        %2v    2   %2v\n", FE(5, l), FE(6, l), FE(7, l), FE(8, l));
  buffer << Format("            | %6v  |         | %6v  |\n", FTN(1, l), FTN(2, l));
  buffer << Format("|%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(6, l), FE(9, l), FV(7, l), FTNum(1, l), FV(8, l), FE(10, l), FV(9, l), FTNum(2, l), FV(10, l), FE(11, l), FV(11, l));
  buffer << Format("  |         |  %5v  |         |  %5v  |         |\n", FR(1, l), FR(2, l));
  buffer << Format(" %2v    3   %2v        %2v    4   %2v        %2v   5   %2v\n", FE(12, l), FE(13, l), FE(14, l), FE(15, l), FE(16, l), FE(17, l));
  buffer << Format("  | %6v  |         | %6v  |         | %6v  |\n", FTN(3, l), FTN(4, l), FTN(5, l));
  buffer << Format("|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|\n", FV(12, l), FTNum(3, l), FV(13, l), FE(18, l), FV(14, l), FTNum(4, l), FV(15, l), FE(19, l), FV(16, l), FTNum(5, l), FV(17, l));
  buffer << Format("  |  %5v  |         |  %5v  |         |  %5v  |\n", FR(3, l), FR(4, l), FR(5, l));
  buffer << Format(" %2v        %2v    6   %2v        %2v    7   %2v        %2v\n", FE(20, l), FE(21, l), FE(22, l), FE(23, l), FE(24, l), FE(25, l));
  buffer << Format("  |         | %6v  |         | %6v  |         |\n", FTN(6, l), FTN(7, l));
  buffer << Format("|%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(18, l), FE(26, l), FV(19, l), FTNum(6, l), FV(20, l), FE(27, l), FV(21, l), FTNum(7, l), FV(22, l), FE(28, l), FV(23, l));
  buffer << Format("  |         |  %5v  |         |  %5v  |         |\n", FR(6, l), FR(7, l));
  buffer << Format(" %2v    8   %2v        %2v    9   %2v        %2v   10   %2v\n", FE(29, l), FE(30, l), FE(31, l), FE(32, l), FE(33, l), FE(34, l));
  buffer << Format("  | %6v  |         | %6v  |         | %6v  |\n", FTN(8, l), FTN(9, l), FTN(10, l));
  buffer << Format("|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|\n", FV(24, l), FTNum(8, l), FV(25, l), FE(35, l), FV(26, l), FTNum(9, l), FV(27, l), FE(36, l), FV(28, l), FTNum(10, l), FV(29, l));
  buffer << Format("  |  %5v  |         |  %5v  |         |  %5v  |\n", FR(8, l), FR(9, l), FR(10, l));
  buffer << Format(" %2v        %2v   11   %2v        %2v   12   %2v        %2v\n", FE(37, l), FE(38, l), FE(39, l), FE(40, l), FE(41, l), FE(42, l));
  buffer << Format("  |         | %6v  |         | %6v  |         |\n", FTN(11, l), FTN(12, l));
  buffer << Format("|%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(30, l), FE(43, l), FV(31, l), FTNum(11, l), FV(32, l), FE(44, l), FV(33, l), FTNum(12, l), FV(34, l), FE(45, l), FV(35, l));
  buffer << Format("  |         |  %5v  |         |  %5v  |         |\n", FR(11, l), FR(12, l));
  buffer << Format(" %2v   13   %2v        %2v   14   %2v        %2v   15   %2v\n", FE(46, l), FE(47, l), FE(48, l), FE(49, l), FE(50, l), FE(51, l));
  buffer << Format("  | %6v  |         | %6v  |         | %6v  |\n", FTN(13, l), FTN(14, l), FTN(15, l));
  buffer << Format("|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|\n", FV(36, l), FTNum(13, l), FV(37, l), FE(52, l), FV(38, l), FTNum(14, l), FV(39, l), FE(53, l), FV(40, l), FTNum(15, l), FV(41, l));
  buffer << Format("  |  %5v  |         |  %5v  |         |  %5v  |\n", FR(13, l), FR(14, l), FR(15, l));
  buffer << Format(" %2v        %2v   16   %2v        %2v   17   %2v        %2v\n", FE(54, l), FE(55, l), FE(56, l), FE(57, l), FE(58, l), FE(59, l));
  buffer << Format("  |         | %6v  |         | %6v  |         |\n", FTN(16, l), FTN(17, l));
  buffer << Format("|%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(42, l), FE(60, l), FV(43, l), FTNum(16, l), FV(44, l), FE(61, l), FV(45, l), FTNum(17, l), FV(46, l), FE(62, l), FV(47, l));
  buffer << Format("            |  %5v  |         |  %5v  |\n", FR(16, l), FR(17, l));
  buffer << Format("           %2v        %2v   18   %2v        %2v\n", FE(63, l), FE(64, l), FE(65, l), FE(66, l));
  buffer << Format("            |         | %6v  |         |\n", FTN(18, l));
  buffer << Format("          |%2v|--%2v--|%2v|  %2v  |%2v|--%2v--|%2v|\n", FV(48, l), FE(67, l), FV(49, l), FTNum(18, l), FV(50, l), FE(68, l), FV(51, l));
  buffer << Format("                      |  %5v  |\n", FR(18, l));
  buffer << Format("                     %2v        %2v\n", FE(69, l), FE(70, l));
  buffer << Format("                      |         |\n");
  buffer << Format("                    |%2v|--%2v--|%2v|\n", FV(52, l), FE(71 ,l), FV(53, l));
}

void StreamView::Notify(const Layout& data) {
  Render(data);
}


void StreamView::Notify(const string& data) {
  buffer << data;
}
