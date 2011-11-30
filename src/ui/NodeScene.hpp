
#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "ui/NodeItem.hpp"

namespace PlayToLearn {
namespace UI {

class NodeScene : public QGraphicsScene {
  Q_OBJECT

public: 
  NodeScene(QObject* parent = 0);  

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
  void create_free_response_node();
  void create_multiple_choice_node();

signals:
  void node_selected(NodeItem * node);

private:
  enum NodeType {
    FreeResponseNode,
    MultipleChoiceNode,
    None
  };

  NodeType mode_;

};

}  // namespace UI
}  // namespace PlayToLearn