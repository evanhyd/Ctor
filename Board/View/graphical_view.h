#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "view.h"

class Layout;

class GraphicalView : public View {
  virtual void RenderImpl(Layout& layout) override;
  virtual void Notify(const std::string& data) override;
  
  using View::View;
};

#endif
