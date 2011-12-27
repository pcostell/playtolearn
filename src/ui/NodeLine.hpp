
#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>

#include "ui/Node.hpp"

namespace PlayToLearn {
namespace UI {

class NodeLine : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  NodeLine(Node* start, Node* end, const std::string& text, QGraphicsItem* parent, QGraphicsScene* scene);

  virtual QPainterPath shape() const;

  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
  virtual QRectF boundingRect() const;

  const Node* start() const;
  const Node* end() const;

private slots:
  void nodeMoved(Node* node);

private:
  // private data
  Node* start_;
  Node* end_;
  std::string text_;
  QRectF last_rect_;

};

}  /* namespace UI */
}  /* namespace PlayToLearn */