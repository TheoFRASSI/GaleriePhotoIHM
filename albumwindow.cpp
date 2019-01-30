#include "albumwindow.h"
#include <QDesktopServices>

AlbumWindow::AlbumWindow(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    connect(albPersoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(albAutoButton, SIGNAL(clicked()), this, SLOT(changeTab()));

    //QString PicturesPath = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation);

}

void AlbumWindow::changeTab()
{
    if(sender() == albAutoButton) {
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == albPersoButton) {
        stackedWidget->setCurrentIndex(0);
    }

}

