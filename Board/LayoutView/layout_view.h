#ifndef LAYOUT_VIEW_H
#define LAYOUT_VIEW_H

#include "../../Observer/observer.h"

class Layout;

class LayoutView : public Observer {
protected: 
  Layout& layout;
  virtual void RenderImpl() = 0; 

public:
  void Render(); 
  
  explicit LayoutView(Layout& layout);
  ~LayoutView();
}; 

#endif 
