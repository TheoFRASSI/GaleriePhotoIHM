#include "modifimagewindow.h"


ModifImageWindow::ModifImageWindow(const BddGalleryPhoto* pbdd, QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    imageCorrupt = QPixmap(pathImageCorrupt);

    ImageButton* boutonFermer = new ImageButton(pathboutonFermerH, pathboutonFermer, 50, 50, this);
    layoutBoutonFermer->addWidget(boutonFermer);
    ImageButton* boutonEditName = new ImageButton(pathboutonEditNameH, pathboutonEditName, 50, 50, this);
    layoutBoutonEditName->addWidget(boutonEditName);
    ImageButton* boutonRogner = new ImageButton(pathboutonRognerH, pathboutonRogner, 50, 50, this);
    layoutRogner->addWidget(boutonRogner);
    ImageButton* boutonRedim = new ImageButton(pathboutonRedimH, pathboutonRedim, 50, 50, this);
    layoutRedim->addWidget(boutonRedim);
    ImageButton* boutonRotateG = new ImageButton(pathboutonRotateGH, pathboutonRotateG, 50, 50, this);
    layoutRotateG->addWidget(boutonRotateG);
    ImageButton* boutonRotateD = new ImageButton(pathboutonRotateDH, pathboutonRotateD, 50, 50, this);
    layoutRotateD->addWidget(boutonRotateD);
    ImageButton* boutonAddToAlbum = new ImageButton(pathboutonAddToAlbumH, pathboutonAddToAlbum, 50, 50, this);
    layoutAddInAlbum->addWidget(boutonAddToAlbum);
    ImageButton* boutonDelete = new ImageButton(pathboutonDeleteH, pathboutonDelete, 50, 50, this);
    layoutDelete->addWidget(boutonDelete);
    ImageButton* boutonFavPlein = new ImageButton(pathboutonFavPleinH, pathboutonFavPlein, 50, 50, this);
    layoutFavoris->addWidget(boutonFavPlein);
    ImageButton* boutonFavVide = new ImageButton(pathboutonFavVideH, pathboutonFavVide, 50, 50, this);
    layoutFavoris->addWidget(boutonFavVide);
    ImageButton* boutonFullScreen = new ImageButton(pathboutonFullScreenH, pathboutonFullScreen, 50, 50, this);
    layoutPleinEcran->addWidget(boutonFullScreen);

    lineEditName->hide();
    boutonFavVide->hide();

    connect(boutonFermer, SIGNAL(clicked()), this, SLOT(fermerFenetre()));
    connect(boutonEditName, SIGNAL(clicked()), this, SLOT(updateImageName()));
    connect(boutonDelete, SIGNAL(clicked()), this, SLOT(deleteImage()));
    connect(boutonFavPlein, SIGNAL(clicked()), this, SLOT(swapIsFavorite()));
    connect(boutonFavVide, SIGNAL(clicked()), this, SLOT(swapIsFavorite()));
}

void ModifImageWindow::afficheImage(QString name) {
    qDebug() << "name :" << name;
    Image* img = bdd->getImageByName(name);
    qDebug() << "Coucou2";
    labelName->setText(img->getName());
    qDebug() << "Coucou3";
    QPixmap pix = QPixmap();
    bool validate = pix.load(img->getPath());
    if(validate){
        pix = pix.scaled(500,1000,Qt::KeepAspectRatio);
        labelImage->setPixmap(pix);
    } else {
        qDebug() << "Erreur : Lors du chargement de l'image >" << img->getPath() << "| Dans la fonction" << __FUNCTION__;
    }
    qDebug() << "Coucou4";
    if(img->getIsFavorite()){
        qDebug() << "Coucou5";
        //boutonFavPlein->show();
        qDebug() << "Coucou5.5";
        //boutonFavVide->hide();
        qDebug() << "Coucou5.75";
    } else {
        qDebug() << "Coucou6";
        //boutonFavPlein->hide();
        qDebug() << "Coucou6.5";
        //boutonFavVide->show();
        qDebug() << "Coucou6.75";
    }
    qDebug() << "Coucou7";

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
