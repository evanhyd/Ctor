#include "layout_view.h"
#include "../Layout/layout.h"
    
void LayoutView::Render() {
  RenderImpl(); 
}

LayoutView::LayoutView(Layout& layout) : layout(layout) {}

LayoutView::~LayoutView() {}
