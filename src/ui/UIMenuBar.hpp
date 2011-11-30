
#pragma once

#include <vector>

#include <QWidget>
#include <QMenuBar>

#include "NodeScene.hpp"

namespace PlayToLearn {
namespace UI {

class UIMenuBar : public QWidget {
  Q_OBJECT

public:
  UIMenuBar(QWidget* parent, NodeScene* scene);

private:
  void addInsertPage(QMenuBar* menuBar, NodeScene* scene);
  void addFilePage(QMenuBar* menuBar, NodeScene* scene);
};

}  // namespace UI
}  // namespace PlayToLearn