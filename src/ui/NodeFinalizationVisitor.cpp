
#include "backend/Object.hpp"
#include "ui/NodeFinalizationVisitor.hpp"

namespace PlayToLearn {
namespace UI {

void NodeFinalizationVisitor::accept(TransitionNode* node) {
  for(size_t i = 0; i < node->destinations().size(); ++i) {
    node->transition().add_state(static_cast<const StateNode*>(node->destinations()[i])->state().id());
  }
}

void NodeFinalizationVisitor::accept(StateNode* node) {
  for(size_t i = 0; i < node->attached_destinations().size(); ++i) {
    const TransitionNode* tnode = static_cast<const TransitionNode*>(node->attached_destinations()[i]);
    node->state().insert_object(Backend::Object::ID(tnode->transition_object_id()), tnode->transition().id());
  }
}

}  /* namespace UI */
}  /* namespace PlayToLearn */