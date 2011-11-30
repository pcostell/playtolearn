
#pragma once

#include <QGraphicsItem>

#include "backend/State.hpp"

namespace PlayToLearn {
namespace UI {

class NodeItem : public QGraphicsPolygonItem
{
public:
    NodeItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

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

