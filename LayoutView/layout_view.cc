#include "layout_view.h"
#include "layout.h"
    
void LayoutView::Render() {
  RenderImpl(); 
}

LayoutView::LayoutView(Layout& layout) : layout(layout) {}

LayoutView::~LayoutView() {}
