#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <ostream>
#include "layout_view.h"

class Layout;

class ConsoleView : public LayoutView {
  std::ostream& buffer;

private: 
  virtual void RenderImpl() override;

private: 
  explicit ConsoleView(Layout& layout, std::ostream& buffer);
}; 

#endif 
