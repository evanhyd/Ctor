#ifndef VIEW_H
#define VIEW_H

class Layout;

class View {
protected: 
  virtual void RenderImpl(const Layout& layout) = 0; 

public:
  void Render(const Layout& layout); 
  
  explicit View();
  virtual ~View();
}; 

#endif 
