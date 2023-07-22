#ifndef HUMAN_BUILDER_H
#define HUMAN_BUILDER_H 
#include "builder.h"
#include "colour_enum.h"

class HumanBuilder : public Builder{
    HumanBuilder(ColourEnum colour, int victoryPoints);
    ~HumanBuilder() override;  
}; 

#endif 
