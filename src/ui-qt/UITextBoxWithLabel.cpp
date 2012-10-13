
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ui/UITextBoxWithLabel.hpp"

namespace PlayToLearn {
namespace UI {

UITextBoxWithLabel::UITextBoxWithLabel(Direction direction) {
  label_ = new QLabel(this);
  field_ = new QPlainTextEdit(this);
  field_->setTabStopWidth(20);
  QBoxLayout* layout;
  switch (direction) {
    case Horizontal:
      layout = new QHBoxLayout;
      break;
    case Vertical:
      layout = new QVBoxLayout;
      break;
  }
  layout->addWidget(label_);
  layout->addWidget(field_);
  setLayout(layout);
}
/*
QSize UITextBoxWithLabel::sizeHint() const {

}
QSize UITextBoxWithLabel::minimumSizeHint() const {

}
*/
std::string UITextBoxWithLabel::text() const {
  return field_->toPlainText().toStdString();
}

void UITextBoxWithLabel::display(const std::string& label, const std::string& defaultText) {
  field_->setPlainText(defaultText.c_str());
  label_->setText(label.c_str());
}

}  /* namespace UI */
}  /* namespace PlayToLearn */