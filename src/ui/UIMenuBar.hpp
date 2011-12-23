
#pragma once

#include <vector>

#include <QWidget>
#include <QMenuBar>
#include <QSignalMapper>

#include "ui/NodeCreator.hpp"
#include "ui/NodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class UIMenuBar : public QWidget {
  Q_OBJECT

public:
  UIMenuBar(QWidget* parent, NodeCreator* creator);

private:
  void addInsertPage(QMenuBar* menuBar);
  void addFilePage(QMenuBar* menuBar);

  QSignalMapper* mapper_;
  NodeCreator* creator_;
};

}  // namespace UI
}  // namespace PlayToLearn