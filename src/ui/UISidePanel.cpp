
#include <string>

#include <QPushButton>
#include <QVBoxLayout>

#include "backend/AttributeMap.hpp"

#include "ui/UISidePanel.hpp"


namespace PlayToLearn {
namespace UI {

UISidePanel::UISidePanel() : current_node_(NULL){
  QVBoxLayout* layout = new QVBoxLayout;

  table_ = new QTableWidget;//(this);
  table_->setColumnCount(2);
  layout->addWidget(table_);

  object_label_ = new UITextBoxWithLabel(UITextBoxWithLabel::Horizontal);
  layout->addWidget(object_label_);

  script_label_ = new UITextBoxWithLabel(UITextBoxWithLabel::Vertical);
  layout->addWidget(script_label_);


  QPushButton* button = new QPushButton("Save");
  connect(button, SIGNAL(clicked()), this, SLOT(save()));
  layout->addWidget(button);

  setLayout(layout);
}

void UISidePanel::display(NodeItem* node) {
  current_node_ = node;
  if (!current_node_) return;
  Backend::AttributeMap& attributes = node->transition_data();
  table_->setRowCount(attributes.size());
  int i = 0;
  for(Backend::AttributeMap::iterator it = attributes.begin();
      it != attributes.end(); ++it, ++i) {

    QTableWidgetItem* left = new QTableWidgetItem(it->first.c_str());
    left->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    QTableWidgetItem* right = new QTableWidgetItem(it->second.c_str());
    table_->setItem(i, 0, left);
    table_->setItem(i, 1, right);

  }
  object_label_->display("Object Id:", boost::lexical_cast<std::string>(current_node_->get_object()));
  script_label_->display("Script:", current_node_->get_script());

}

void UISidePanel::save() {
  if (current_node_) {
    for (int i = 0; i < table_->rowCount(); ++i) {
      current_node_->transition_data().set_value(table_->item(i, 0)->text().toStdString(),
                                               table_->item(i, 1)->text().toStdString());

      std::cout << "Setting " << table_->item(i, 0)->text().toStdString() << " : " << table_->item(i, 1)->text().toStdString() << std::endl;
    }
    int objectId = boost::lexical_cast<int>(object_label_->text());
    current_node_->set_object(objectId);

    current_node_->set_script(script_label_->text());

  }
}

QSize UISidePanel::sizeHint() const {
  return QSize(300, 500);
}

QSize UISidePanel::minimumSizeHint() const {
  return QSize(300, 500);
}

}  /* namespace UI */
}  /* namespace PlayToLearn */