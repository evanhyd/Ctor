#include "view.h"
#include "../Layout/layout.h"
    
void View::Render(const Layout& layout) {
  RenderImpl(layout); 
}

View::View() {}

View::~View() {}
