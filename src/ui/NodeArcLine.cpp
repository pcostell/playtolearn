
#include <QBrush>
#include <QPen>

#include <algorithm>
#include <cmath>

#include "ui/NodeArcLine.hpp"

using std::max;
using std::abs;

namespace PlayToLearn {
namespace UI {

NodeArcLine::NodeArcLine(Node* start, Node* end, QGraphicsItem* parent, QGraphicsScene* scene)
    : NodeLine(start, end, parent, scene)
{
}

QPainterPath NodeArcLine::shape() const {
  QPainterPath p;
  p.moveTo(start()->pos());
  p.cubicTo(start()->pos().x(), start()->pos().y() - start()->bounds().height(),
            end()->pos().x(), end()->pos().y() - end()->bounds().height(),
            end()->pos().x(), end()->pos().y());
  //p.arcTo(arcRectangle(), 0, 180);
  return p;
}

QRectF NodeArcLine::arcRectangle() const {
  float x, y;
  float height = max(start()->bounds().height(), end()->bounds().height());
  float width = abs(float(end()->pos().x() - start()->pos().x()));

  if(start()->pos().x() < end()->pos().x()) {
    x = start()->pos().x();
    y = start()->pos().y() - height;
  } else {
    x = end()->pos().x();
    y = end()->pos().y() - height;
  }
  return QRectF(x,y ,width, height);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */