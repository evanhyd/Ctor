#ifndef GRAPHICAL_VIEW_H
#define GRAPHICAL_VIEW_H

#include "layout_view.h"

class Layout;

class GraphicalView : public LayoutView {
  virtual void RenderImpl() override;

  using LayoutView::LayoutView;
};

#endif
