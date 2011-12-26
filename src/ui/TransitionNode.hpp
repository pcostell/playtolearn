
#pragma once

#include <string>

#include "backend/TransitionFn.hpp"
#include "backend/AttributeMap.hpp"
#include "ui/Node.hpp"
#include "ui/TransitionNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class TransitionNode : public Node {
  Q_OBJECT
public:
  TransitionNode(TransitionNodePolicy* policy,
                 QGraphicsItem* parent = 0,
                 QGraphicsScene* scene = 0);

  Backend::TransitionFn& transition();
  const Backend::TransitionFn& transition() const;

  Backend::AttributeMap& transition_data();
  const Backend::AttributeMap& transition_data() const;

  std::string transition_script() const;
  void set_transition_script(const std::string & script);

  int transition_object_id() const;
  void set_transition_object_id(int id);

  virtual QRectF bounds() const;

  virtual void visit(NodeVisitor* visitor);

signals:
  void node_selected(TransitionNode* node);

protected:
  virtual std::string text() const;
  virtual QColor color() const;
  virtual QColor selected_color() const;

  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
  // Member data
  TransitionNodePolicy* policy_;
  Backend::TransitionFn transition_;
  Backend::AttributeMap transition_data_;
  std::string transition_script_;
  int transition_object_id_;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */