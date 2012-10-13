
#include "ui/TransitionNodeCreator.hpp"

#include "ui/FreeResponseTransitionNodePolicy.hpp"
#include "ui/MultipleChoiceTransitionNodePolicy.hpp"
#include "ui/TextTransitionNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

TransitionNodeCreator::TransitionNodeCreator() {
  policies_.push_back(new FreeResponseTransitionNodePolicy);
  policies_.push_back(new MultipleChoiceTransitionNodePolicy);
  policies_.push_back(new TextTransitionNodePolicy);
}

size_t TransitionNodeCreator::size() const {
  return policies_.size();
}

std::string TransitionNodeCreator::node_name(int node_number) const {
  return policies_[node_number]->name();
}

std::string TransitionNodeCreator::state_name() const {
  return "State";
}

void TransitionNodeCreator::create_state() {
  emit state_created();
}

void TransitionNodeCreator::create_node(int node_number) {
  emit node_created(policies_[node_number]);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */