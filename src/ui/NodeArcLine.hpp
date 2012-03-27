
#pragma once

#include "ui/NodeLine.hpp"

namespace PlayToLearn {
namespace UI {

/** Class Definitions **/

// represents the line between two Nodes.
class NodeArcLine : public NodeLine {
  Q_OBJECT
public:
  NodeArcLine(Node* start, Node* end, const std::string& text, QGraphicsItem* parent, QGraphicsScene* scene);

  virtual QPainterPath shape() const;

};

}  /* namespace UI */
}  /* namespace PlayToLearn */