
#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QLabel>


namespace PlayToLearn {
namespace UI {

class UITextBoxWithLabel : public QWidget {
  Q_OBJECT
public:
  enum Direction {
    Horizontal,
    Vertical
  };

  UITextBoxWithLabel(Direction direction = Horizontal);


//  QSize sizeHint() const;
 // QSize minimumSizeHint() const;

  std::string text() const;

public slots:
  void display(const std::string& label, const std::string& defaultText);

private:
  QLabel* label_;
  QPlainTextEdit* field_;
};

}  /* namespace UI */
}  /* namespace PlayToLearn */