#include "modifimagewindow.h"


ModifImageWindow::ModifImageWindow(const BddGalleryPhoto* pbdd, QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    imageCorrupt = QPixmap(pathImageCorrupt);

    boutonFermer = new ImageButton(pathboutonFermerH, pathboutonFermer, 70, 70, this);
    layoutBoutonFermer_2->addWidget(boutonFermer);
    boutonEditName = new ImageButton(pathboutonEditNameH, pathboutonEditName, 70, 70, this);
    layoutBoutonEditName->addWidget(boutonEditName);
    boutonRogner = new ImageButton(pathboutonRognerH, pathboutonRogner, 70, 70, this);
    layoutRogner->addWidget(boutonRogner);
    boutonRedim = new ImageButton(pathboutonRedimH, pathboutonRedim, 70, 70, this);
    layoutRedim->addWidget(boutonRedim);
    boutonRotateG = new ImageButton(pathboutonRotateGH, pathboutonRotateG, 70, 70, this);
    layoutRotateG->addWidget(boutonRotateG);
    boutonRotateD = new ImageButton(pathboutonRotateDH, pathboutonRotateD, 70, 70, this);
    layoutRotateD->addWidget(boutonRotateD);
    boutonAddToAlbum = new ImageButton(pathboutonAddToAlbumH, pathboutonAddToAlbum, 70, 70, this);
    layoutAddInAlbum->addWidget(boutonAddToAlbum);
    boutonDelete = new ImageButton(pathboutonDeleteH, pathboutonDelete, 70, 70, this);
    layoutDelete->addWidget(boutonDelete);
    boutonFavPlein = new ImageButton(pathboutonFavPleinH, pathboutonFavPlein, 70, 70, this);
    layoutFavoris->addWidget(boutonFavPlein);
    boutonFavVide = new ImageButton(pathboutonFavVideH, pathboutonFavVide, 70, 70, this);
    layoutFavoris->addWidget(boutonFavVide);
    boutonFullScreen = new ImageButton(pathboutonFullScreenH, pathboutonFullScreen, 70, 70, this);
    layoutPleinEcran->addWidget(boutonFullScreen);

    lineEditName->hide();
    boutonFavPlein->hide();

    connect(boutonFermer, SIGNAL(clicked()), this, SLOT(fermerFenetre()));
    connect(boutonEditName, SIGNAL(clicked()), this, SLOT(updateImageName()));
    connect(boutonDelete, SIGNAL(clicked()), this, SLOT(deleteImage()));
    connect(boutonFavPlein, SIGNAL(clicked()), this, SLOT(swapIsFavorite()));
    connect(boutonFavVide, SIGNAL(clicked()), this, SLOT(swapIsFavorite()));
}

void ModifImageWindow::afficheImage(QString name) {
    Image* img = bdd->getImageByName(name);
    labelName->setText(img->getName());
    QPixmap pix = QPixmap();
    bool validate = pix.load(img->getPath());
    if(validate){
        pix = pix.scaled(1500,1000,Qt::KeepAspectRatio);
        labelImage->setPixmap(pix);
    } else {
        pix = QPixmap(imageCorrupt);
        pix = pix.scaled(1500,1000,Qt::KeepAspectRatio);
        labelImage->setPixmap(pix);
        qDebug() << "Erreur : Lors du chargement de l'image >" << img->getPath() << "| Dans la fonction" << __FUNCTION__;
    }
    if(img->getIsFavorite()){
        boutonFavPlein->show();
        boutonFavVide->hide();
    } else {
        boutonFavPlein->hide();
        boutonFavVide->show();
    }
}

void ModifImageWindow::fermerFenetre()
{
    lineEditName->setText("");
    lineEditName->hide();
    labelName->show();
    labelImage->setPixmap(QPixmap());
    boutonFavPlein->hide();
    boutonFavVide->show();

    emit goToImageWindow();
}

void ModifImageWindow::updateImageName()
{
    if(lineEditName->isHidden()){
        lineEditName->show();
        labelName->hide();
        lineEditName->setText(labelName->text());
    } else {
        if(lineEditName->text() == "" && lineEditName->text() == labelName->text()){
            lineEditName->hide();
            labelName->show();
        } else {
            if(bdd->updateImageName(labelName->text(), lineEditName->text())){
                qDebug() << "Nom de l'Image modifié";
                labelName->setText(lineEditName->text());
                lineEditName->hide();
                labelName->show();
            } else {
                qDebug() << "Nom de l'Image NON modifié";
                lineEditName->hide();
                labelName->show();
            }
        }
    }

}

void ModifImageWindow::deleteImage()
{
    bdd->deleteImageByName(labelName->text());
    fermerFenetre();
}

void ModifImageWindow::swapIsFavorite()
{
    if(boutonFavPlein->isHidden()) {
        bdd->updateIsFavorite(true, labelName->text());
        boutonFavVide->hide();
        boutonFavPlein->show();
    } else {
        bdd->updateIsFavorite(false, labelName->text());
        boutonFavPlein->hide();
        boutonFavVide->show();
    }
}
