#include "command_save.h"
#include "../board.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <filesystem>

using namespace std;

Command::Code CommandSave::operator()() {
  board.NotifyAll("enter a save filename\n"); 

  std::ofstream savedFile; 
  std::string rootPath = std::filesystem::current_path().generic_string(); 
  while(true){
    std::string filename; 
    cin >> filename; 
    savedFile.open(rootPath + "/SavedGame/" + filename + ".txt");  
    if(!savedFile.is_open()){
      board.NotifyAll(Format("invalid save filename: %v\n", filename)); 
      continue; 
    }
    savedFile << board.SaveData(); 
    break; 
  }

  savedFile.close(); 

  return Code::SUCCESS;
}
