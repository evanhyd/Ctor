#include "command_save.h"
#include "../board.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <filesystem>

using namespace std;

Command::Code CommandSave::operator()() {
  board.NotifyAll("Enter a save filename: ");
  string filename;
  cin >> filename;
  filename += ".sv";

  try {
    ofstream savedFile;
    savedFile.exceptions(ofstream::failbit | ofstream::badbit);
    savedFile.open(filesystem::current_path() / filename, ios::trunc);
    savedFile << board.SaveData() << endl;
    savedFile.close();
  } catch(const ofstream::failure& error) {
    board.NotifyAll(error.what());
    board.NotifyAll("\nfailed to save the board state due to system error\n please make sure your filename is valid\n");
  }
  
  return Code::SUCCESS;
}
