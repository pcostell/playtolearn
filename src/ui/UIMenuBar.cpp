
#include "UIMenuBar.hpp"

#include <iostream>

#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QMenuBar>

namespace PlayToLearn {
namespace UI {

  UIMenuBar::UIMenuBar(QWidget * parent, NodeScene * scene) 
      : QWidget(parent)
  {
    QMenuBar* menuBar = new QMenuBar(this);
    addFilePage(menuBar, scene);
    addInsertPage(menuBar, scene);
  }

  void UIMenuBar::addFilePage(QMenuBar* menuBar, NodeScene* scene) {
    QMenu *menu = menuBar->addMenu("File");
    QAction *nnode = menu->addAction("New");
    QAction *onode = menu->addAction("Open"); 
    QAction *snode = menu->addAction("Save");
    QAction *qqnode = menu->addAction("Quit");
  }

  

  void UIMenuBar::addInsertPage(QMenuBar* menuBar, NodeScene* scene) {

    QMenu *insert = menuBar->addMenu("Insert");
    QAction *frnode = insert->addAction("Free Response Question");
    connect(frnode, SIGNAL(triggered()), scene, SLOT(create_free_response_node()));

    QAction *mcnode = insert->addAction("Multiple Choice Question");
    connect(mcnode, SIGNAL(triggered()), scene, SLOT(create_multiple_choice_node()));
  }

}  // namespace UI
}  // namespace PlayToLearn
