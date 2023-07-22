#ifdef LAYOUT_VIEW_H
#define LAYOUT_VIEW_H

class LayoutView{
public: 
    void Render(); 
protected: 
    virtual RenderImpl() = 0; 
}; 

#endif 
