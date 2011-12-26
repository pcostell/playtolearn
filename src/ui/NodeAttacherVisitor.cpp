
#include <QGraphicsScene>

#include "ui/NodeAttacherVisitor.hpp"
#include "ui/NodeArcLine.hpp"
#include "ui/NodeLine.hpp"

namespace PlayToLearn {
namespace UI {

NodeAttacherVisitor::NodeAttacherVisitor(StateNode* state)
    : state_(state)
{
}

void NodeAttacherVisitor::accept(TransitionNode* node) {
  if(node->attached_source()) {
    std::cout << "Adding " << state_->state().id() << " as a destination." << std::endl;
    node->connect_from(state_);
    if(node->attached_source() == state_) {
      new NodeArcLine(node, state_, NULL, node->scene());
    } else {
      new NodeLine(node, state_, NULL, node->scene());
    }
    std::cout << "scene: " << node->scene() << std::endl;
  } else {
    std::cout << "Attaching " << node->transition().id() << " to state " << state_->state().id() << std::endl;
    state_->attach_from(node);
  }
}

void NodeAttacherVisitor::accept(StateNode* node) {
  copy(node->attached_destinations().begin(),
       node->attached_destinations().end(),
       back_inserter(state_->attached_destinations()));
  copy(node->sources().begin(),
       node->sources().end(),
       back_inserter(state_->sources()));
  copy(node->destinations().begin(),
       node->destinations().end(),
       back_inserter(state_->destinations()));
  node->disable();
}

}  /* namespace UI */
}  /* namespace PlayToLearn */