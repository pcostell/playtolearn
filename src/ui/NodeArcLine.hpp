
#pragma once

#include "ui/NodeLine.hpp"

namespace PlayToLearn {
namespace UI {

class NodeArcLine : public NodeLine {
  Q_OBJECT
public:
  NodeArcLine(Node* start, Node* end, QGraphicsItem* parent, QGraphicsScene* scene);

  virtual QPainterPath shape() const;

private:
  QRectF arcRectangle() const;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */