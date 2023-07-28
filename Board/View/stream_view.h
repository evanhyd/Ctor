#ifndef STREAM_VIEW_H
#define STREAM_VIEW_H

#include <ostream>
#include "view.h"

class Layout;

class StreamView : public View {
  std::ostream& buffer;

  virtual void RenderImpl(Layout& layout) override;
  virtual void Notify(const std::string& data) override;

public:
  explicit StreamView(std::ostream& buffer);
}; 

#endif 
