#include "board.h"
#include "Layout/layout.h"
#include "shop.h"
#include "../Builder/builder.h"
#include "View/stream_view.h"
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

Board::Board()
  : layout(make_unique<Layout>()), shop(make_unique<Shop>()), view(make_unique<StreamView>(cout)) {
}


void Board::Print() {
	// TODO: print layout
  cout << "board" << endl;
}

void Board::Start() {
  layout->GenerateLayout(69420);

  int vertex;
  bool successful_placement = false;
  bool reversed = false;
  int i = 0;
  Print();
  while (i > 0 || !reversed) {
    if (i == layout->GetBuilders().size()) {
      reversed = true;
      i--;
    }
    std::unique_ptr<Builder>& builder = layout->GetBuilder(i);
    successful_placement = false;
	cout << "here" << endl;
	cout << builder->GetColour() << endl;
	cout << "here2" << endl;
    while (!successful_placement) {
      cout << "Builder " << builder->GetColour() << ", where do you want to build a basement" << endl;
      cin >> vertex;
      successful_placement = shop->BuildResidence(*builder, *layout, vertex, true);
    }
    if (reversed) i--;
    else i++;
  }
}

void Board::Play() {

  bool won = false;
  int winner_index = 0;
  while (!won) {
    for (int i = 0; i < layout->GetBuilders().size(); i++) {
      unique_ptr<Builder> &builder = layout->GetBuilder(i);
      if (Turn(builder)) {
        won = true;
        winner_index = i;
        break;
      }
    }
  }
  Win(layout->GetBuilder(winner_index));
}

bool Board::Turn(unique_ptr<Builder> &builder) {
	string command;
	Print();
	cout << "Builder " << builder->GetColour() << "'s turn." << endl;
	cout << builder->ToString() << endl;
	while (true) {
		cout << "> ";
		cin >> command;
		if (command == "load") {
			
		} else if (command == "fair") {

		} else if (command == "roll") {

		} else {
			cout << "Invalid command." << endl;
			continue;
		}
		break;
	}
	while (true) {
    	cout << "> ";
		cin >> command;
		if (command == "board") { 
			Print();
		} else if (command == "status") {
			cout << builder->ToString() << endl;
		} else if (command == "residences") {
			cout << builder->GetBuildings() << endl;
		} else if (command == "build-road") {
			int roadIndex;
			cin >> roadIndex;
			shop->BuildRoad(*builder, *layout, roadIndex);
		} else if (command == "build-res") {
			int vertex;
			cin >> vertex;
		  if (shop->BuildResidence(*builder, *layout, vertex) && Won(builder)) return true;
		} else if (command == "improve") {
			int vertex;
			cin >> vertex;
			if (shop->ImproveResidence(*builder, *layout, vertex) && Won(builder)) return true;
		} else if (command == "trade") {
			string colour;
			string give;
			string take;
			cin >> colour >> give >> take;
      Inventory give_inventory = GetInventory(give);
      if (give_inventory.GetTotal() == 0) {
				cout << "Invalid give resource" << endl;
				continue;
      }
      Inventory take_inventory = GetInventory(take);
      if (take_inventory.GetTotal() == 0) {
				cout << "Invalid take resource" << endl;
				continue;
      }
			if (give == take) {
        cout << "Can't give and take same resource" << endl;
        continue;
      }
      give_inventory -= take_inventory;
      int builder_index = 0;

      if (colour == builder->GetColour()) {
        cout << "Can't trade with ya self" << endl;
        continue;
      }

			if (colour == "Blue") builder_index = 0;
			else if (colour == "Red") builder_index = 1;
			else if (colour == "Orange") builder_index = 2;
			else if (colour == "Yellow") builder_index = 3;
			else {
				cout << "Invalid colour" << endl;
				continue;
			}
      if (!shop->Trade(*builder, *layout->GetBuilder(builder_index), give_inventory)) cout << "Failed to trade" << endl;
		} else if (command == "next") {
			return false;
		} else if (command == "save") {
			// TODO	Save
		} else if (command == "help") {
      CommandHelp();
		} else {
			cout << "Invalid command." << endl;
		}
	}
}

void Board::Win(unique_ptr<Builder> &builder) {
  cout << "Builder " << builder->GetColour() << " has won!" << endl;
  cout << "Would you like to play again?" << endl;
  cout << "yes/no : ";
  string input;
  while (true) {
    cin >> input;
    if (input == "yes" || input == "Yes") return Reset();
    else if (input == "no" || input == "No") return;
    else cout << "That wasn't yes or no. Enter yes/no : ";
  }
}

void Board::Reset() {
  layout = make_unique<Layout>();
  Start();
}

bool Board::Won(std::unique_ptr<Builder> &builder) {
  return builder->GetVictoryPoints() >= 10;
}

Inventory Board::GetInventory(string resource) {
  static const map<string, Inventory> mp = {
    {"Brick", Inventory{1, 0, 0, 0, 0}},
    {"Energy", Inventory{0, 1, 0, 0, 0}},
    {"Glass", Inventory{0, 0, 1, 0, 0}},
    {"Heat", Inventory{0, 0, 0, 1, 0}},
    {"Wifi", Inventory{0, 0, 0, 0, 1}},
  };

  if (mp.find(resource) != mp.end()) {
    return mp.find(resource)->second;
  }
  else return Inventory{0, 0, 0, 0, 0};
}

void Board::CommandHelp() const {
  cout << "Valid commands:" << endl;
  cout << "board" << endl;
  cout << "status" << endl;
  cout << "build-road <edge#>" << endl;
  cout << "build-res <housing#>" << endl;
  cout << "improve <housing#>" << endl;
  cout << "trade <colour> <give> <take>" << endl;
  cout << "next" << endl;
  cout << "save <file>" << endl;
  cout << "help" << endl;
}
