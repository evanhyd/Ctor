#include "stream_view.h"
#include "../Layout/layout.h"

StreamView::StreamView(std::ostream& buffer) : buffer{buffer} {}

void StreamView::RenderImpl(Layout& layout){
  //layout.GetState()
  //print out the state
}

void StreamView::Notify(const std::string& data) {

}
