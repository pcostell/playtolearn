
#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QObject>

#include "backend/StateMachine.hpp"

#include "ui/TransitionNode.hpp"
#include "ui/StateNode.hpp"
#include "ui/TransitionNodePolicy.hpp"
#include "ui/TransitionNodeCreator.hpp"

namespace PlayToLearn {
namespace UI {

class NodeScene : public QGraphicsScene {
  Q_OBJECT

public:
  NodeScene(TransitionNodeCreator* creator, QObject* parent = 0);

  Backend::StateMachine& state_machine();

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:
  void inserting_node(TransitionNodePolicy* policy);
  void inserting_state();
 // void node_collision(NodeItem* node, QList<QGraphicsItem*>& colliders);

  void save();

private slots:
  void node_event(TransitionNode* node);
  void collision(Node* node1, Node* node2);

signals:
  void node_selected(TransitionNode* node);

private:
  void WriteScript(const std::string& level_name, Backend::TransitionFn::ID transition_fn_id, const std::string& code);

  enum SceneState {
    None,
    InsertingNode,
    InsertingState
  };
  Backend::StateMachine sm_;
  SceneState state_;
  TransitionNodePolicy* current_policy_;
  std::vector<StateNode*> states_;
  std::vector<TransitionNode*> nodes_;
};

}  // namespace UI
}  // namespace PlayToLearn