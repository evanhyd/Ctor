#include "view.h"
    
void View::Render(Layout& layout) {
  RenderImpl(layout); 
}

View::View() {}

View::~View() {}
