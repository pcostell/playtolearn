
#pragma once

#include <QGraphicsPolygonItem>
#include <QObject>

#include "backend/State.hpp"
#include "ui/NodeItem.hpp"

namespace PlayToLearn {
namespace UI {

class StateItem : public QObject, public QGraphicsPolygonItem
{
  Q_OBJECT
public:

  StateItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

  Backend::State& state();

protected:
  void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
  void mousePressEvent(QGraphicsSceneMouseEvent* event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
  Backend::State state_;
};


}  // namespace UI
}  // namespace PlayToLearn

