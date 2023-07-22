#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H
#include <ostream>
#include "layout_view.h"

class ConsoleView : public LayoutView {
public: 
    ConsoleView(); 

private: 
    void RenderImpl() override final; 

private: 
    std::ostream& buffer;
}; 

#endif 
