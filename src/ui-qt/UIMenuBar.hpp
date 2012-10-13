
#pragma once

#include <vector>

#include <QWidget>
#include <QMenuBar>
#include <QSignalMapper>

#include "ui/TransitionNodeCreator.hpp"
#include "ui/TransitionNodePolicy.hpp"

namespace PlayToLearn {
namespace UI {

class UIMenuBar : public QWidget {
  Q_OBJECT

public:
  UIMenuBar(QWidget* parent, TransitionNodeCreator* creator);

private:
  void addInsertPage(QMenuBar* menuBar);
  void addFilePage(QMenuBar* menuBar);

  QSignalMapper* mapper_;
  TransitionNodeCreator* creator_;
};

}  // namespace UI
}  // namespace PlayToLearn