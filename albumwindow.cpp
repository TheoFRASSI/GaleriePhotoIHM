#include "albumwindow.h"

AlbumWindow::AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    bdd = pbdd;
    connect(albPersoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(albAutoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(newImageButton, SIGNAL(clicked()),this, SLOT(searchImage()));

    Image* image = bdd->getImageByName("Image 1");
    QPixmap *pixmap = new QPixmap(image->getPath());
    labelImg->setPixmap(*pixmap);
}

AlbumWindow::~AlbumWindow()
{
    //bdd->destroyBdd();
    smartDeleteMrNovelli(bdd);
}

void AlbumWindow::changeTab()
{
    if(sender() == albAutoButton) {
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == albPersoButton) {
        stackedWidget->setCurrentIndex(0);
    }

}
void AlbumWindow::searchImage()
{
    const QStringList paths = QFileDialog::getOpenFileNames(this);
    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            qDebug() << paths[i];
            QPixmap *img = new QPixmap(paths[i]);
            labelImg->setPixmap(*img);

            const QStringList names = paths[i].split("/");
            qDebug() << names[names.size()-2]; // nom du dossier de l'image
            Image newImage(names.last(), paths[i]);
            bdd->insertImage(newImage);
        }


    }

        //openImage(fileName);
}

/*void AlbumWindow::openImage(const QString &fileName)
{

    QFile file(fileName);

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}*/

