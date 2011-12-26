
#pragma once

#include "ui/TransitionNode.hpp"
#include "ui/StateNode.hpp"
#include "ui/NodeVisitor.hpp"

namespace PlayToLearn {
namespace UI {

class NodeAttacherVisitor : public NodeVisitor {
public:
  NodeAttacherVisitor(StateNode* state);
  void accept(TransitionNode* node);
  void accept(StateNode* node);

private:
  StateNode* state_;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */