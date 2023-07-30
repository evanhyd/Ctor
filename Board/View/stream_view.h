#ifndef STREAM_VIEW_H
#define STREAM_VIEW_H

#include <ostream>
#include <string>
#include "view.h"
#include "../../Observer/observer.h"
#include "../Layout/layout.h"

class StreamView : public View, public Observer<std::string, Layout> {
  std::ostream& buffer;

  std::string FV(int vertex, const Layout& layout); // Format Vertex
  std::string FE(int edge, const Layout& layout); // Format Edge
  std::string FR(int tile, const Layout& layout); // Format Robber
  std::string FTN(int tile, const Layout& layout); // Format Tile Name
  std::string FTNum(int tile, const Layout& layout); // Format Tile Number

  virtual void RenderImpl(const Layout& layout) override;
  virtual void Notify(const Layout& layout) override;
  virtual void Notify(const std::string& data) override;
public:
  explicit StreamView(std::ostream& buffer);
}; 

#endif 


