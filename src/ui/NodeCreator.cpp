
#include "ui/NodeCreator.hpp"

#include "ui/FreeResponseNodePolicy.hpp"
#include "ui/MultipleChoiceNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

NodeCreator::NodeCreator() {
  policies_.push_back(new FreeResponseNodePolicy);
  policies_.push_back(new MultipleChoiceNodePolicy);
}

size_t NodeCreator::size() const {
  return policies_.size();
}

std::string NodeCreator::node_name(int node_number) const {
  return policies_[node_number]->name();
}

std::string NodeCreator::state_name() const {
  return "State";
}

void NodeCreator::create_state() {
  emit state_created();
}

void NodeCreator::create_node(int node_number) {
  emit node_created(policies_[node_number]);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */