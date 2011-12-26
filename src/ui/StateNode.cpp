
#include "ui/StateNode.hpp"

using namespace std;

namespace PlayToLearn {
namespace UI {

/////////////////
// Constructor //
/////////////////

StateNode::StateNode(QGraphicsItem* parent, QGraphicsScene* scene)
    : Node(parent, scene),
      state_(Backend::State::ID::create())
{

}

////////////////////
// Public Methods //
////////////////////

Backend::State& StateNode::state() {
  return state_;
}

const Backend::State& StateNode::state() const {
  return state_;
}

///////////////////////
// Protected Methods //
///////////////////////

string StateNode::text() const {
  return boost::lexical_cast<string>(state_.id());
}

QRectF StateNode::bounds() const {
  return QRectF(-15, -15, 30, 30);
}

QColor StateNode::color() const {
  return QColor(255, 255, 50);
}

QColor StateNode::selected_color() const {
  return QColor(255, 255, 100);
}

void StateNode::visit(NodeVisitor* visitor) {
  visitor->accept(this);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */