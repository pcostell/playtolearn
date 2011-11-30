
#include "ui/NodeScene.hpp"
#include "ui/NodeItem.hpp"

namespace PlayToLearn {
namespace UI {

NodeScene::NodeScene(QObject* parent) 
    : QGraphicsScene(parent), mode_(None) {
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

  NodeItem * node;
  switch (mode_) {
    case FreeResponseNode: case MultipleChoiceNode:
      node = new NodeItem;
      addItem(node);
      node->setPos(mouseEvent->scenePos());
      break;
    default:
      break;
  }
  mode_ = None;
  QGraphicsScene::mousePressEvent(mouseEvent);
}

void NodeScene::create_free_response_node() {
  mode_ = FreeResponseNode;
}

void NodeScene::create_multiple_choice_node() {
  mode_ = MultipleChoiceNode;
}

}  // namespace UI

}  // namespace PlayToLearn