
#pragma once

#include <vector>

#include <QObject>

#include "ui/NodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class NodeCreator : public QObject {
  Q_OBJECT
public:
  NodeCreator();
  size_t size() const;
  std::string node_name(int node_number) const;
  std::string state_name() const;

public slots:
  void create_node(int node_number);
  void create_state();

signals:
  void node_created(NodePolicy* policy);
  void state_created();

private:
  std::vector<NodePolicy*> policies_;
};


}  /* namespace UI */
}  /* namespace PlayToLearn */