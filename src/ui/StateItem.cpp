#include <QtGui>
#include <QPainterPath>

#include "ui/StateItem.hpp"

namespace PlayToLearn {
namespace UI {

  StateItem::StateItem(QGraphicsItem *parent, QGraphicsScene *scene)
      : QGraphicsPolygonItem(parent, scene),
        state_(Backend::State::ID::create())
  {
    QPainterPath painter;
    painter.addRoundedRect(-15, -15, 30, 30, 10, 10);

    setPolygon(painter.toFillPolygon());


    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  }

  void StateItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    if (isSelected()) {
      painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter->setBrush(QColor(255, 255, 100));
    } else {
      painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
      painter->setBrush(QColor(255, 255, 50));
    }
    painter->drawPolygon(polygon(), fillRule());
    painter->setBrush(QColor(0, 0, 0));
    painter->drawText(-15, -15, 30, 30, Qt::AlignCenter, boost::lexical_cast<std::string>(state_.id()).c_str());
  }

  void StateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
  {
    setCursor(Qt::ClosedHandCursor);
    QGraphicsPolygonItem::mousePressEvent(event);
  }

  void StateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
 {
     setCursor(Qt::OpenHandCursor);
     QGraphicsPolygonItem::mouseReleaseEvent(event);
 }

  void StateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
 {
    setCursor(Qt::OpenHandCursor);
    QGraphicsPolygonItem::mouseMoveEvent(event);
  }

  Backend::State& StateItem::state() {
    return state_;
  };


}  // namespace UI
}  // namespace PlayToLearn