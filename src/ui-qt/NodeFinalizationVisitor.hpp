
#pragma once

#include "ui/NodeVisitor.hpp"
#include "ui/TransitionNode.hpp"
#include "ui/StateNode.hpp"

namespace PlayToLearn {
namespace UI {

class NodeFinalizationVisitor : public NodeVisitor {
public:

  void accept(TransitionNode* node);
  void accept(StateNode* node);
};

}  /* namespace UI */
}  /* namespace PlayToLearn */