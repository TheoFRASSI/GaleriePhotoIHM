#include "modifimagewindow.h"

ModifImageWindow::ModifImageWindow(const BddGalleryPhoto* pbdd, QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    imageCorrupt = QPixmap(pathImageCorrupt);
}

void ModifImageWindow::afficheImage(QString name) {
    Image* img = bdd->getImageByName(name);

}
