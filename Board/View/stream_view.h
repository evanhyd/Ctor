#ifndef STREAM_VIEW_H
#define STREAM_VIEW_H

#include <ostream>
#include "view.h"

class Layout;

class StreamView : public View {
  std::ostream& buffer;

  virtual void RenderImpl(Layout& layout) override;
  virtual void Notify(const std::string& data) override;
  std::string VF(int vertex); // Vertex Format
  std::string EF(int edge); // Edge Format
  std::string GA(int tile); // Goose At
public:
  explicit StreamView(std::ostream& buffer);
}; 

#endif 


