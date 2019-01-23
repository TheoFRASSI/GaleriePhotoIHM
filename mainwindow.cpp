#include "mainwindow.h"
#include "imagebutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    QString s = "C:/Users/theof/Pictures/ImageProjetQt/menu.png";
    ImageButton img(s,40,40,pushButton);
}
