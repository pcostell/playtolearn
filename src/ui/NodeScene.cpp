
#include <string>
#include <fstream>

#include "backend/Object.hpp"
#include "ui/NodeAttacherVisitor.hpp"
#include "ui/NodeFinalizationVisitor.hpp"
#include "ui/NodeScene.hpp"
#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace UI {

NodeScene::NodeScene(TransitionNodeCreator* creator, QObject* parent)
    : QGraphicsScene(parent), state_(None)
{
  connect(creator, SIGNAL(node_created(TransitionNodePolicy*)),
          this, SLOT(inserting_node(TransitionNodePolicy*)));
  connect(creator, SIGNAL(state_created()),
          this, SLOT(inserting_state()));
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

  emit node_selected(NULL);
  if (state_ == InsertingNode) {
    TransitionNode * node = new TransitionNode(current_policy_, NULL, this);
    connect(node, SIGNAL(node_selected(TransitionNode*)),
            this, SLOT(node_event(TransitionNode*)));
    //addItem(node);
    node->setPos(mouseEvent->scenePos());
    nodes_.push_back(node);
  } else if (state_ == InsertingState) {
    StateNode* state = new StateNode(NULL, this);
    connect(state, SIGNAL(accept_node(Node*,Node*)),
            this, SLOT(collision(Node*, Node*)));
    //addItem(state);
    state->setPos(mouseEvent->scenePos());
    states_.push_back(state);
  }
  state_ = None;
  QGraphicsScene::mousePressEvent(mouseEvent);
}


///////////
// Slots //
///////////

void NodeScene::collision(Node* node1, Node* node2) {
  std::cout << "Collision detected." << std::endl;
  NodeAttacherVisitor* v = new NodeAttacherVisitor(static_cast<StateNode*>(node1));
  node2->visit(v);
  delete v;
}

void NodeScene::node_event(TransitionNode* node) {
  emit node_selected(node);
}

void NodeScene::inserting_state() {
  state_ = InsertingState;
}

void NodeScene::inserting_node(TransitionNodePolicy* policy) {
  state_ = InsertingNode;
  current_policy_ = policy;
}

Backend::StateMachine& NodeScene::state_machine() {
  return sm_;
}

void NodeScene::save() {
  std::cout << "Saving...";
  stringstream level_name_ss;
  level_name_ss << Util::kLevelDirectoryPrefix << "0/";
  string level_name = level_name_ss.str();

  stringstream tfn_file_name_ss;
  tfn_file_name_ss << level_name << Util::kLevelTransitionFnFile;
  ofstream tfn_output_file(tfn_file_name_ss.str().c_str());

  NodeVisitor* finalizer = new NodeFinalizationVisitor;

  map<Backend::TransitionFn::ID, Backend::AttributeMap> transition_fn_data;
  for(size_t i = 0; i < nodes_.size(); ++i) {
    nodes_[i]->visit(finalizer);
    sm_.add_transition_fn(nodes_[i]->transition());
    transition_fn_data.insert(make_pair(nodes_[i]->transition().id(), nodes_[i]->transition_data()));
    WriteScript(level_name, nodes_[i]->transition().id(), nodes_[i]->transition_script());
    tfn_output_file << nodes_[i]->transition().id() << " py\n";
  }

  for (size_t i = 0; i < states_.size(); ++i) {
    states_[i]->visit(finalizer);
    sm_.add_state(states_[i]->state());
  }

  stringstream sm_file_name_ss;
  sm_file_name_ss << level_name << Util::kLevelStateMachineFile;
  ofstream sm_output_file(sm_file_name_ss.str().c_str());
  boost::archive::xml_oarchive sm_output_archive(sm_output_file);
  sm_output_archive << boost::serialization::make_nvp("StateMachine", sm_);

  stringstream tfn_data_file_name_ss;
  tfn_data_file_name_ss << level_name << Util::kLevelTransitionDataFile;
  ofstream tfn_data_output_file(tfn_data_file_name_ss.str().c_str());
  boost::archive::xml_oarchive tfn_data_output_archive(tfn_data_output_file);
  tfn_data_output_archive << boost::serialization::make_nvp("transition_data", transition_fn_data);

  std::cout << "Done." << std::endl;
}

void NodeScene::WriteScript(const string& level_name, Backend::TransitionFn::ID transition_fn_id, const string& code) {
  stringstream file_name_ss;
  file_name_ss << level_name << Util::kLevelTransitionFnScriptDirectory << transition_fn_id << ".py";
  ofstream output_file(file_name_ss.str().c_str());
  output_file << code;
}

}  // namespace UI

}  // namespace PlayToLearn