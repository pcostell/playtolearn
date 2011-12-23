#include <QtGui>
#include <QPainterPath>

#include "ui/NodeItem.hpp"
#include "ui/StateItem.hpp"
#include "util/Constants.hpp"


namespace PlayToLearn {
namespace UI {

  NodeItem::NodeItem(NodePolicy* policy, QGraphicsItem *parent, QGraphicsScene *scene)
      : QGraphicsPolygonItem(parent, scene),
        policy_(policy),
        source_(NULL),
        transition_(Backend::TransitionFn::ID::create()),
        object_id_(Util::kDefaultObject.value()),
        transition_fn_script_(policy->script(transition_))
  {
    policy_->transition_data(transition_data_);



    QPainterPath painter;
    painter.addRoundedRect(-15, -15, 15, 30, 3, 3);

    setPolygon(painter.toFillPolygon());


    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    dragging_ = false;
  }

  void NodeItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    if (isSelected()) {
      painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
      painter->setBrush(policy_->color(NodePolicy::Selected));
    } else {
      painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
      painter->setBrush(policy_->color(NodePolicy::Default));
    }

    painter->drawPolygon(polygon(), fillRule());
    painter->drawText(-15, -15, 15, 30, Qt::AlignCenter, boost::lexical_cast<std::string>(transition_.id()).c_str());

  }

  void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
  {
    QGraphicsPolygonItem::setCursor(Qt::ClosedHandCursor);
    emit node_selected(this);
    dragging_ = true;
    QGraphicsPolygonItem::mousePressEvent(event);
  }

  void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
 {
    QGraphicsPolygonItem::setCursor(Qt::OpenHandCursor);
    QList<QGraphicsItem*> colliders = collidingItems();
    if(!colliders.empty()) {
      emit collision(this, colliders);
    }
    if(has_source()) {
      setPos(get_source()->scenePos().x() + 30, get_source()->scenePos().y());
    }
    dragging_ = false;
    QGraphicsPolygonItem::mouseReleaseEvent(event);
 }

  void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
 {
    QGraphicsPolygonItem::setCursor(Qt::OpenHandCursor);
    QGraphicsPolygonItem::mouseMoveEvent(event);
  }

  Backend::AttributeMap& NodeItem::transition_data() {
    return transition_data_;
  }

  Backend::TransitionFn& NodeItem::transition() {
    return transition_;
  }

  void NodeItem::set_source(StateItem* state) {
    source_ = state;
  }

  bool NodeItem::has_source() const {
    return source_ != NULL;
  }

  StateItem* NodeItem::get_source() const {
    return source_;
  }

  void NodeItem::set_object(int id) {
    object_id_ = id;
  }

  int NodeItem::get_object() const {
    return object_id_;
  }

  void NodeItem::set_script(const std::string & script) {
    transition_fn_script_ = script;
  }

  std::string NodeItem::get_script() const {
    return transition_fn_script_;
  }

}  // namespace UI
}  // namespace PlayToLearn