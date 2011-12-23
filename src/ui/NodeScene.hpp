
#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QObject>

#include "backend/StateMachine.hpp"

#include "ui/NodeItem.hpp"
#include "ui/StateItem.hpp"
#include "ui/NodePolicy.hpp"
#include "ui/NodeCreator.hpp"

namespace PlayToLearn {
namespace UI {

class NodeScene : public QGraphicsScene {
  Q_OBJECT

public:
  NodeScene(NodeCreator* creator, QObject* parent = 0);

  Backend::StateMachine& state_machine();

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
  void inserting_node(NodePolicy* policy);
  void inserting_state();
  void node_collision(NodeItem* node, QList<QGraphicsItem*>& colliders);

  void save();

private slots:
  void node_event(NodeItem* node);

signals:
  void node_selected(NodeItem * node);

private:
  void WriteScript(const std::string& level_name, Backend::TransitionFn::ID transition_fn_id, const std::string& code);

  enum SceneState {
    None,
    InsertingNode,
    InsertingState
  };
  Backend::StateMachine sm_;
  SceneState state_;
  NodePolicy* current_policy_;
  std::vector<StateItem*> states_;
  std::vector<NodeItem*> nodes_;
};

}  // namespace UI
}  // namespace PlayToLearn