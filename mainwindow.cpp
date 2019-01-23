#include "mainwindow.h"
#include "imagebutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    QString imageReleased = "C:/Users/theof/Pictures/ImageProjetQt/menu.png";
    QString imagePressed = "C:/Users/theof/Pictures/ImageProjetQt/menuHighlighted.png";
    ImageButton* img = new ImageButton(imagePressed, imageReleased, 75, 75, this);
    menu->addWidget(img);
}
