
#include <string>

#include <boost/lexical_cast.hpp>

#include "ui/TransitionNode.hpp"
#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace UI {

/////////////////
// Constructor //
/////////////////

TransitionNode::TransitionNode(TransitionNodePolicy* policy,
                               QGraphicsItem* parent,
                               QGraphicsScene* scene)
    : Node(parent, scene),
      policy_(policy),
      transition_(Backend::TransitionFn::ID::create()),
      transition_script_(policy->script(transition_)),
      transition_object_id_(Util::kDefaultObject.value())
{
  policy->transition_data(transition_data_);
}

////////////////////
// Public methods //
////////////////////

Backend::TransitionFn& TransitionNode::transition() {
  return transition_;
}

const Backend::TransitionFn& TransitionNode::transition() const {
  return transition_;
}

Backend::AttributeMap& TransitionNode::transition_data() {
  return transition_data_;
}

const Backend::AttributeMap& TransitionNode::transition_data() const {
  return transition_data_;
}

string TransitionNode::transition_script() const {
  return transition_script_;
}

void TransitionNode::set_transition_script(const string& script) {
  transition_script_ = script;
}

int TransitionNode::transition_object_id() const {
  return transition_object_id_;
}

void TransitionNode::set_transition_object_id(int id) {
  transition_object_id_ = id;
}

///////////////////////
// Protected methods //
///////////////////////

string TransitionNode::text() const {
  return boost::lexical_cast<string>(transition_.id());
}

QRectF TransitionNode::bounds() const {
  return QRectF(-7.5, -15, 15, 30);
}

void TransitionNode::visit(NodeVisitor* visitor) {
  visitor->accept(this);
}

QColor TransitionNode::color() const {
  return policy_->color(TransitionNodePolicy::Default);
}

QColor TransitionNode::selected_color() const {
  return policy_->color(TransitionNodePolicy::Selected);
}

void TransitionNode::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  emit node_selected(this);
  Node::mousePressEvent(event);
}



}  /* namespace UI */
}  /* namespace PlayToLearn */