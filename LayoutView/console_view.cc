#include "console_view.h"
#include "layout.h"

ConsoleView::ConsoleView(Layout& layout, std::ostream& buffer) : LayoutView(layout), buffer{buffer} {}

void ConsoleView::RenderImpl(){
  //layout.GetState()
  //print out the state
}
