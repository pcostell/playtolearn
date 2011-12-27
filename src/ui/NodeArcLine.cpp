
#include <QBrush>
#include <QPen>

#include <algorithm>
#include <cmath>

#include "ui/NodeArcLine.hpp"

using std::max;
using std::abs;

namespace PlayToLearn {
namespace UI {

NodeArcLine::NodeArcLine(Node* start, Node* end, const std::string& text, QGraphicsItem* parent, QGraphicsScene* scene)
    : NodeLine(start, end, text, parent, scene)
{
}

QPainterPath NodeArcLine::shape() const {
  QPainterPath p;
  p.moveTo(start()->pos());
  p.cubicTo(start()->pos().x(), start()->pos().y() - 2*start()->bounds().height(),
            end()->pos().x(), end()->pos().y() - 2*end()->bounds().height(),
            end()->pos().x(), end()->pos().y());
  return p;
}

}  /* namespace UI */
}  /* namespace PlayToLearn */