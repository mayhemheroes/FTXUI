#include "ftxui/dom/node_decorator.hpp"
#include "ftxui/dom/elements.hpp"

namespace ftxui {
namespace dom {

class Dim : public NodeDecorator {
 public:
  Dim(Children children) : NodeDecorator(std::move(children)) {}
  ~Dim() override {}

  void Render(Screen& screen) override {
    Node::Render(screen);
    for (int y = box_.top; y <= box_.bottom; ++y) {
      for (int x = box_.left; x <= box_.right; ++x) {
        screen.PixelAt(x,y).dim = true; 
      }
    }
  }
};

std::unique_ptr<Node> dim(Child child) {
  return std::make_unique<Dim>(unpack(std::move(child)));
}

};  // namespace dom
};  // namespace ftxui
