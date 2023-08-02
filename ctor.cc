#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string>
#include <memory>
#include <chrono>
#include <utility>
#include <exception>
#include "Board/board.h"
#include "Board/shop.h"
#include "Board/View/stream_view.h"

using namespace std;

string GetFileName(int argc, char* argv[], int i) {
  if (i >= argc) {
    cerr << "file name is missing" << endl;
    exit(1);
  }
  return argv[i];
}

unsigned GetSeed(int argc, char* argv[], int i) {
  if (i >= argc) {
    cerr << "seed argument is missing" << endl;
    exit(1);
  }

  try {
    return stoi(argv[i + 1]);
  } catch (const exception& error) {
    cerr << error.what() << endl;
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  unique_ptr<Layout> layout = make_unique<Layout>();
  unique_ptr<Shop> shop = make_unique<Shop>();

  constexpr int SEED_BASED = 0;
  constexpr int GAME_SAVE_FILE = 1;
  constexpr int STRUCT_SAVE_FILE = 2;
  int loadType = 0;
  string fileName = "";
  unsigned seed = chrono::system_clock().now().time_since_epoch().count();
  bool enable_bank_trades = true;

  for (int i = 1; i < argc; ++i) {
    string arg(argv[i]);
    if (arg == "-seed") {
      loadType = SEED_BASED;
      seed = GetSeed(argc, argv, ++i);  
      continue;
    }
    
    if (arg == "-load") {
      loadType = GAME_SAVE_FILE;
      fileName = GetFileName(argc, argv, ++i);  
      continue;
    }
    
    if (arg == "-board") {
      loadType = STRUCT_SAVE_FILE;
      fileName = GetFileName(argc, argv, ++i);   
      continue;
    }
    
    if (arg == "-random-board") {
      loadType = SEED_BASED;
    }
    
    if (arg == "--enable-bank-trades") {
      enable_bank_trades = true;
      continue; 
    }
  }

  StreamView view{std::cout};
  Board board(std::move(layout), std::move(shop), enable_bank_trades);
  board.Attach(&view);

  try {
    cin.exceptions(ios::eofbit);

    bool freshStart = true;
    if (loadType == SEED_BASED) {
      // normal seeding
      board.GetLayout().GenerateLayout(seed);

    } else {
      ifstream file;
      file.exceptions(ios::badbit);
      file.open(fileName);

      Log("opened %v\n", fileName);

      if (loadType == GAME_SAVE_FILE) {
        board.LoadData(file);
        freshStart = false;
      } else {
        board.GetLayout().LoadData(file);
      }
    }

    board.Play(freshStart);

  } catch(const std::exception& error) {
    ofstream file("backup.sv", ios::trunc);
    file << board.SaveData() << endl;
    cerr << error.what() << endl;
    exit(1);
  }
  
  return 0;
}
