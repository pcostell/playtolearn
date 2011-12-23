
#pragma once

#include <QGraphicsItem>

#include "backend/TransitionFn.hpp"
#include "backend/AttributeMap.hpp"

#include "ui/NodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class StateItem;

class NodeItem : public QObject, public QGraphicsPolygonItem
{
  Q_OBJECT
public:

  NodeItem(NodePolicy* policy, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

  Backend::AttributeMap& transition_data();
  Backend::TransitionFn& transition();

  void set_object(int id);
  int get_object() const;
  void set_source(StateItem* state);
  bool has_source() const;
  StateItem* get_source() const;
  void set_script(const std::string & script);
  std::string get_script() const;

signals:
  void node_selected(NodeItem*);
  void collision(NodeItem* node, QList<QGraphicsItem*>& colliders);


protected:
  void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
  NodePolicy* policy_;
  Backend::TransitionFn transition_;
  Backend::AttributeMap transition_data_;
  StateItem* source_;
  int object_id_;
  std::string transition_fn_script_;

  bool dragging_;
};


}  // namespace UI
}  // namespace PlayToLearn

