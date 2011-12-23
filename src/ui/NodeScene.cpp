
#include <string>
#include <fstream>

#include "backend/Object.hpp"
#include "ui/NodeScene.hpp"
#include "ui/NodeItem.hpp"
#include "ui/StateItem.hpp"
#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace UI {

NodeScene::NodeScene(NodeCreator* creator, QObject* parent)
    : QGraphicsScene(parent), state_(None)
{
  connect(creator, SIGNAL(node_created(NodePolicy*)),
          this, SLOT(inserting_node(NodePolicy*)));
  connect(creator, SIGNAL(state_created()),
          this, SLOT(inserting_state()));
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

  emit node_selected(NULL);
  if (state_ == InsertingNode) {
    NodeItem * node = new NodeItem(current_policy_, NULL, this);
    connect(node, SIGNAL(node_selected(NodeItem*)),
            this, SLOT(node_event(NodeItem*)));
    connect(node, SIGNAL(collision(NodeItem*,QList<QGraphicsItem*>&)),
            this, SLOT(node_collision(NodeItem*, QList<QGraphicsItem*>&)));
    addItem(node);
    node->setPos(mouseEvent->scenePos());
    nodes_.push_back(node);
  } else if (state_ == InsertingState) {
    StateItem* state = new StateItem;
    addItem(state);
    state->setPos(mouseEvent->scenePos());
    states_.push_back(state);
  }
  state_ = None;
  QGraphicsScene::mousePressEvent(mouseEvent);
}

void NodeScene::node_event(NodeItem* node) {
  emit node_selected(node);
}

void NodeScene::inserting_state() {
  state_ = InsertingState;
}

void NodeScene::inserting_node(NodePolicy* policy) {
  state_ = InsertingNode;
  current_policy_ = policy;
}

void NodeScene::node_collision(NodeItem* node, QList<QGraphicsItem*>& colliders) {
  for(size_t i = 0; i < colliders.size(); ++i) {
    StateItem* state = dynamic_cast<StateItem*>(colliders[i]);
    if(state) {
      if(node->has_source()) {
        std::cout << "Node has source, setting destination to state: " << state->state().id() << std::endl;
        node->transition().add_state(state->state().id());
      } else {
         std::cout << "Setting node source to state: " << state->state().id() << std::endl;
        node->set_source(state);
      }
      break;
    }
  }
}

Backend::StateMachine& NodeScene::state_machine() {
  return sm_;
}

void NodeScene::save() {

  stringstream level_name_ss;
  level_name_ss << Util::kLevelDirectoryPrefix << "0/";
  string level_name = level_name_ss.str();

  stringstream tfn_file_name_ss;
  tfn_file_name_ss << level_name << Util::kLevelTransitionFnFile;
  ofstream tfn_output_file(tfn_file_name_ss.str().c_str());


  map<Backend::TransitionFn::ID, Backend::AttributeMap> transition_fn_data;
  for(size_t i = 0; i < nodes_.size(); ++i) {
    if (nodes_[i]->has_source()) {
      nodes_[i]->get_source()->state().insert_object(Backend::Object::ID(nodes_[i]->get_object()), nodes_[i]->transition().id());
    }
    sm_.add_transition_fn(nodes_[i]->transition());
    transition_fn_data.insert(make_pair(nodes_[i]->transition().id(), nodes_[i]->transition_data()));
    WriteScript(level_name, nodes_[i]->transition().id(), nodes_[i]->get_script());
    tfn_output_file << nodes_[i]->transition().id() << " py\n";
  }

  for (size_t i = 0; i < states_.size(); ++i) {
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


}

void NodeScene::WriteScript(const string& level_name, Backend::TransitionFn::ID transition_fn_id, const string& code) {
  stringstream file_name_ss;
  file_name_ss << level_name << Util::kLevelTransitionFnScriptDirectory << transition_fn_id << ".py";
  ofstream output_file(file_name_ss.str().c_str());
  output_file << code;
}

}  // namespace UI

}  // namespace PlayToLearn