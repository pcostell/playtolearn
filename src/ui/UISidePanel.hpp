
#pragma once

#include <QWidget>
#include <QTableWidget>

#include "ui/NodeItem.hpp"
#include "ui/UITextBoxWithLabel.hpp"

namespace PlayToLearn {
namespace UI {

class UISidePanel : public QWidget {
  Q_OBJECT
public:
  UISidePanel();

  QSize sizeHint() const;
  QSize minimumSizeHint() const;


public slots:
  void display(NodeItem* item);
  void save();

private:
  QTableWidget* table_;
  UITextBoxWithLabel* object_label_;
  UITextBoxWithLabel* script_label_;
  NodeItem* current_node_;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */