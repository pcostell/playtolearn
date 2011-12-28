
#include <algorithm>

#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

#include "ui/Node.hpp"

using namespace std;

namespace PlayToLearn {
namespace UI {

Node::Node(QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsPolygonItem(parent, scene),
      attached_source_(NULL),
      disabled_(false)
{
  //setCursor(Qt::OpenHandCursor);
  setAcceptedMouseButtons(Qt::LeftButton);
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Node::attach_from(Node* dest_node) {
  dest_node->attach_to(this);
}

void Node::connect_from(Node* dest_node) {
  dest_node->connect_to(this);
}

void Node::attach_to(Node* source_node) {
  if (attached_source_) {
    disconnect(attached_source_, SIGNAL(moved(Node*)),
               this, SLOT(source_moved(Node*)));
    vector<Node*>::iterator toErase = find(attached_source_->attached_destinations().begin(),
                                                 attached_source_->attached_destinations().end(),
                                                 this);
    if (toErase != attached_source_->attached_destinations().end()) {
      attached_source_->attached_destinations().erase(toErase);
    }
  }
  sources_.clear();
  attached_source_ = source_node;
  source_node->attached_destinations_.push_back(this);
  connect(source_node, SIGNAL(moved(Node*)), this,
          SLOT(source_moved(Node*)));
}

void Node::connect_to(Node* source_node) {
  sources_.push_back(source_node);
  source_node->destinations_.push_back(this);
}

///////////////////////
// Protected Methods //
///////////////////////


void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  if (disabled_) return;

  const QRectF poly_bounds = bounds();
  QPainterPath path;
  path.addRoundedRect(poly_bounds, poly_bounds.width()/5, poly_bounds.height()/5);
  setPolygon(path.toFillPolygon());

  if (isSelected()) {
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
    painter->setBrush(selected_color());
  } else {
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->setBrush(color());
  }

  painter->drawPolygon(polygon(), fillRule());
  painter->setBrush(QColor(0, 0, 0));

  painter->drawText(bounds(), Qt::AlignCenter, text().c_str());
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  //setCursor(Qt::ClosedHandCursor);
  emit selected(this);
  QGraphicsPolygonItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
  //setCursor(Qt::OpenHandCursor);
  QList<QGraphicsItem*> colliders = collidingItems();
  if (!colliders.empty()) {
    for (int i = 0; i < colliders.size(); ++i) {
      Node* collider = static_cast<Node*>(colliders[i]);
      if (collider->disabled_) continue;
      collider->emit_collision(this);
      emit collision(this, collider);
    }
  }
  if (attached_source_) {
    setPos(attached_source_->attachedPosition(this));
    emit moved(this);
  }
  QGraphicsPolygonItem::mouseReleaseEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  //setCursor(Qt::OpenHandCursor);
  emit moved(this);
  QGraphicsPolygonItem::mouseMoveEvent(event);
}

void Node::disable() {
  setFlag(QGraphicsItem::ItemIsMovable, false);
  setFlag(QGraphicsItem::ItemIsSelectable, false);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
  disabled_ = true;
  setEnabled(false);
  //repaint();
}

Node* Node::attached_source() {
  return attached_source_;
}

vector<Node*>& Node::attached_destinations() {
  return attached_destinations_;
}

vector<Node*>& Node::sources() {
  return sources_;
}

vector<Node*>& Node::destinations() {
  return destinations_;
}

///////////////////
// Private Slots //
///////////////////

void Node::source_moved(Node* source) {
  setPos(source->attachedPosition(this));
  emit moved(this);
}

/////////////////////
// Private Methods //
/////////////////////


const float Node::kAttachedBuffer = 2;

QPointF Node::attachedPosition(Node* attached_node) const {
  float x = pos().x() + bounds().x() + bounds().width();
  for (size_t i = 0; i < attached_destinations_.size(); ++i) {
    if(attached_destinations_[i] == attached_node) {
      return QPointF(x - attached_destinations_[i]->bounds().x() + kAttachedBuffer, pos().y());
    }
    x += attached_destinations_[i]->bounds().width();
  }
  return attached_node->pos();
}

void Node::emit_collision(Node* colliding_node) {
  emit accept_node(this, colliding_node);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */