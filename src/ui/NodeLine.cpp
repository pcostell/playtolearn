
#include <QBrush>
#include <QGraphicsScene>
#include <QPen>


#include "ui/NodeLine.hpp"

namespace PlayToLearn {
namespace UI {

NodeLine::NodeLine(Node* start, Node* end, QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsItem(parent, scene),
      start_(start),
      end_(end)
{
  connect(start, SIGNAL(moved(Node*)), this, SLOT(nodeMoved(Node*)));
  connect(end, SIGNAL(moved(Node*)), this, SLOT(nodeMoved(Node*)));
}

void NodeLine::nodeMoved(Node* node) {
  update();
}

void NodeLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  painter->setPen(QPen(QBrush(QColor(0, 0, 0)), 1));
  painter->drawPath(shape());
}

QPainterPath NodeLine::shape() const {
  QPainterPath p;
  p.moveTo(start()->pos());
  p.lineTo(end()->pos());

  return p;
}

QRectF NodeLine::boundingRect() const {
  return shape().boundingRect();
}

const Node* NodeLine::start() const {
  return start_;
}

const Node* NodeLine::end() const {
  return end_;
}


}  /* namespace UI */
}  /* namespace PlayToLearn */