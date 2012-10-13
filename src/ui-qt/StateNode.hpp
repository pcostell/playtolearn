
#pragma once

#include "backend/State.hpp"
#include "ui/Node.hpp"

namespace PlayToLearn {
namespace UI {

class StateNode : public Node {
public:
  StateNode(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

  Backend::State& state();
  const Backend::State& state() const;
  virtual QRectF bounds() const;

  virtual void visit(NodeVisitor* visitor);

protected:
  virtual std::string text() const;
  virtual QColor color() const;
  virtual QColor selected_color() const;


private:
  Backend::State state_;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */