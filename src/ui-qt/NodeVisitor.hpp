
#pragma once

namespace PlayToLearn {
namespace UI {
// Pre-declaration for visitor pattern
class TransitionNode;
class StateNode;

class NodeVisitor {
public:

  virtual void accept(TransitionNode* node) {};
  virtual void accept(StateNode* node) {};

};

}  /* namespace UI */
}  /* namespace PlayToLearn */
