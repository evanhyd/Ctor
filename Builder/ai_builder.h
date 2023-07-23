#ifndef AI_BUILDER_H
#define AI_BUILDER_H 
#include "builder.h"
#include "colour_enum.h"

class AIBuilder : public Builder {
    AIBuilder(ColourEnum colour, int victoryPoints);
    ~AIBuilder() override;  
}; 

#endif 
