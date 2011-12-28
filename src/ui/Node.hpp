
#pragma once

#include <string>
#include <vector>

#include <QColor>
#include <QGraphicsPolygonItem>
#include <QGraphicsObject>
#include <QRect>

#include "ui/NodeVisitor.hpp"

namespace PlayToLearn {
namespace UI {

class Node : public QObject, public QGraphicsPolygonItem {
  Q_OBJECT
public:
  Node(QGraphicsItem *parent = 0, QGraphicsScene* scene = 0);

  Node* attached_source();
  std::vector<Node*>& attached_destinations();
  std::vector<Node*>& sources();
  std::vector<Node*>& destinations();

  void attach_to(Node* source_node);
  void connect_to(Node* source_node);
  void attach_from(Node* dest_node);
  void connect_from(Node* dest_node);

  void disable();

  void setPos(const QPointF& point);

  virtual QRectF bounds() const = 0;

  // Visitor pattern for subclasses
  virtual void visit(NodeVisitor* visitor) = 0;

protected:

  virtual std::string text() const = 0;
  virtual QColor color() const = 0;
  virtual QColor selected_color() const = 0;


  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

signals:
  void collision(Node* dragged, Node* accepting);
  void accept_node(Node* accepting, Node* dragged);
  void selected(Node* node);
  void moved(Node* node);

private slots:
  void source_moved(Node* node);
  void move_animation(qreal frame);

private:
  static const float kAttachedBuffer;
  // Member data
  Node* attached_source_;
  std::vector<Node*> attached_destinations_;
  std::vector<Node*> sources_;
  std::vector<Node*> destinations_;
  bool disabled_;

  // Member functions
  QPointF attachedPosition(Node* attached_node) const;
  void emit_collision(Node* colliding_node);
};

}
}  /* namespace PlayToLearn */