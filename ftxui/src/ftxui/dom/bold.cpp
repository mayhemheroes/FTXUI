#include "ftxui/dom/node_decorator.hpp"
#include "ftxui/dom/elements.hpp"

namespace ftxui {
namespace dom {

class Bold : public NodeDecorator {
 public:
  Bold(Children children) : NodeDecorator(std::move(children)) {}
  ~Bold() override {}

  void Render(Screen& screen) override {
    Node::Render(screen);
    for (int y = box_.top; y <= box_.bottom; ++y) {
      for (int x = box_.left; x <= box_.right; ++x) {
        screen.PixelAt(x,y).bold = true; 
      }
    }
  }
};

std::unique_ptr<Node> bold(Child child) {
  return std::make_unique<Bold>(unpack(std::move(child)));
}

};  // namespace dom
};  // namespace ftxui
