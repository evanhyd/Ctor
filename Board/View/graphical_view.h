#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "view.h"

class Layout;

class GraphicalView : public View {
  virtual void RenderImpl(const Layout& layout) override; 
  
  using View::View;
};

#endif
