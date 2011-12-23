#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QGraphicsView>

#include "ui/UIMenuBar.hpp"
#include "ui/NodeCreator.hpp"
#include "ui/NodeScene.hpp"
#include "ui/FreeResponseNodePolicy.hpp"
#include "ui/MultipleChoiceNodePolicy.hpp"
#include "ui/UISidePanel.hpp"

int main( int argc, char **argv )
{

QApplication a( argc, argv );

QWidget window;

PlayToLearn::UI::NodeCreator* creator = new PlayToLearn::UI::NodeCreator;
PlayToLearn::UI::NodeScene* scene = new PlayToLearn::UI::NodeScene(creator, &window);
scene->setSceneRect(QRectF(0, 0, 5000, 5000));
PlayToLearn::UI::UIMenuBar bar(&window, creator);
PlayToLearn::UI::UISidePanel sidePanel;
QObject::connect(scene, SIGNAL(node_selected(NodeItem*)), &sidePanel, SLOT(display(NodeItem*)));

QGraphicsView view(scene);
QHBoxLayout layout;
//QVBoxLayout layout;

//layout.addWidget(&bar);


QPushButton save("Save", &window);
save.setGeometry(100, 30, 100, 100);
save.setFont(QFont("Times", 18, QFont::Bold));
QObject::connect(&save, SIGNAL(clicked()), scene, SLOT(save()));

//layout.insertSpacing(0, 20);
layout.addWidget(&view);
layout.addStretch();
layout.addWidget(&sidePanel);
layout.addWidget(&save);

window.setLayout(&layout);
window.show();
return a.exec();

}