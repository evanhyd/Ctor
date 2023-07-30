#ifndef STREAM_VIEW_H
#define STREAM_VIEW_H

#include <ostream>
#include "view.h"

class Layout;

class StreamView : public View {
  std::ostream& buffer;

  virtual void RenderImpl(Layout& layout) override;
  virtual void Notify(const std::string& data) override;
  std::string FV(int vertex, Layout& layout); // Format Vertex
  std::string FE(int edge, Layout& layout); // Format Edge
  std::string FR(int tile, Layout& layout); // Format Robber
  std::string FTN(int tile, Layout& layout); // Format Tile Name
  std::string FTNum(int tile, Layout& layout); // Format Tile Number
public:
  explicit StreamView(std::ostream& buffer);
}; 

#endif 


