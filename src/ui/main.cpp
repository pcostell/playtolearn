#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QGraphicsView>

#include "ui/UIMenuBar.hpp"
#include "ui/NodeCreator.hpp"
#include "ui/NodeScene.hpp"

int main( int argc, char **argv )
{

QApplication a( argc, argv );

QWidget window;

PlayToLearn::UI::NodeScene scene(&window);
scene.setSceneRect(QRectF(0, 0, 5000, 5000));
PlayToLearn::UI::UIMenuBar bar(&window, &scene);

QGraphicsView view(&scene);

QVBoxLayout layout;

//layout.addWidget(&bar);


QPushButton quit("Quit", &window);
quit.setGeometry(100, 30, 100, 100);
quit.setFont(QFont("Times", 18, QFont::Bold));
QObject::connect(&quit, SIGNAL(clicked()), &a, SLOT(quit()));

layout.insertSpacing(0, 20);
layout.addWidget(&view);
layout.addWidget(&quit);
window.setLayout(&layout);
window.show();
return a.exec();

}