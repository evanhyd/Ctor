#ifndef VIEW_H
#define VIEW_H

#include "../../Observer/observer.h"
#include <string>

class Layout;

class View : public Observer<std::string> {
protected: 
  virtual void RenderImpl(Layout& layout) = 0; 

public:
  void Render(Layout& layout); 
  
  explicit View();
  ~View();
}; 

#endif 
