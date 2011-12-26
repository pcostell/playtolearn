
#include "UIMenuBar.hpp"

#include <iostream>

#include <QObject>
#include <QMenuBar>

namespace PlayToLearn {
namespace UI {

  UIMenuBar::UIMenuBar(QWidget * parent, TransitionNodeCreator* creator)
      : QWidget(parent), creator_(creator)
  {
    QMenuBar* menuBar = new QMenuBar(this);
    mapper_ = new QSignalMapper(this);
    addFilePage(menuBar);
    addInsertPage(menuBar);
  }

  void UIMenuBar::addFilePage(QMenuBar* menuBar) {
    QMenu *menu = menuBar->addMenu("File");
    QAction *nnode = menu->addAction("New");
    QAction *onode = menu->addAction("Open");
    QAction *snode = menu->addAction("Save");
    QAction *qqnode = menu->addAction("Quit");
  }

  void UIMenuBar::addInsertPage(QMenuBar* menuBar) {

    QMenu* insert_menu = menuBar->addMenu("Insert");
    QAction* state_action = insert_menu->addAction(creator_->state_name().c_str());
    connect(state_action, SIGNAL(triggered()), creator_, SLOT(create_state()));

    for (int i = 0; i < creator_->size(); ++i) {
      QAction* action = insert_menu->addAction(creator_->node_name(i).c_str());
      connect(action, SIGNAL(triggered()), mapper_, SLOT(map()));
      mapper_->setMapping(action, i);
      connect(mapper_, SIGNAL(mapped(int)), creator_, SLOT(create_node(int)));
    }
  }

}  // namespace UI
}  // namespace PlayToLearn
