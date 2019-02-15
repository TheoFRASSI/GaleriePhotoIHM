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

void ModifImageWindow::fermerFenetre()
{
    lineEditNameImage->setText("");
    lineEditNameImage->hide();
    labelNomImage->show();

    emit goToImageWindow();
}

/* ICI C'EST BIEN ROUGE */
void ModifImageWindow::updateImageName()
{
    if(lineEditNameImage->isHidden()){
        lineEditNameImage->show();
        labelNomImage->hide();
        lineEditNameImage->setText(labelNomImage->text());
    } else {
        if(lineEditNameImage->text() == "" && lineEditNameImage->text() == labelNomImage->text()){
            lineEditNameImage->hide();
            labelNomImage->show();
        } else {
            if(bdd->updateImageName(labelNomImage->text(), lineEditNameImage->text())){
                qDebug() << "Nom de l'Image modifié";
                labelNomImage->setText(lineEditNameImage->text());
                //newBDDRequest(bdd->getImageByName(labelNomImage->text()));
                lineEditNameImage->hide();
                labelNomImage->show();
            } else {
                qDebug() << "Nom de l'Image NON modifié";
                lineEditNameImage->hide();
                labelNomImage->show();
            }
        }
    }

}

void ModifImageWindow::deleteImage()
{
    bdd->deleteImageByName(labelNomImage->text());
    fermerFenetre();
}

void ModifImageWindow::swapIsFavorite()
{
    if(favoriteButtonJaune->isHidden()) {
        bdd->updateIsFavorite(true, labelNomImage->text());
        favoriteButtonVide->hide();
        favoriteButtonJaune->show();
    } else {
        bdd->updateIsFavorite(false, labelNomImage->text());
        favoriteButtonJaune->hide();
        favoriteButtonVide->show();
    }
}
