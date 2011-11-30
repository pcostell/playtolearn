


#include <QtGui>
#include <QPainterPath>

#include "ui/NodeItem.hpp"

namespace PlayToLearn {
namespace UI {

  NodeItem::NodeItem(QGraphicsItem *parent, QGraphicsScene *scene) 
      : QGraphicsPolygonItem(parent, scene), state_(Backend::State::ID::create()) {

    QPainterPath painter;
    painter.addRoundedRect(-15, -15, 30, 30, 10, 10);

    setPolygon(painter.toFillPolygon());
 

    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  }  

  void NodeItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    if (isSelected()) {
      painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter->setBrush(QColor(255, 100, 100));
    } else {
      painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
      painter->setBrush(QColor(255, 0, 0));
    }
    painter->drawPolygon(polygon(), fillRule());
  }

  void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
  {
    setCursor(Qt::ClosedHandCursor);
    QGraphicsPolygonItem::mousePressEvent(event);
  }

  void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
 {
     setCursor(Qt::OpenHandCursor);
     QGraphicsPolygonItem::mouseReleaseEvent(event);
 }

  void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
 {
    setCursor(Qt::OpenHandCursor);
    QGraphicsPolygonItem::mouseMoveEvent(event);
  }


}  // namespace UI
}  // namespace PlayToLearn