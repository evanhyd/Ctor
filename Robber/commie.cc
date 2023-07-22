#include "commie.h"

int Commie::GetTileIndex() const {
    return tileIndex; 
}

void Commie::MoveTo(int inputTileIndex){
    tileIndex = inputTileIndex; 
}