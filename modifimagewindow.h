#pragma once

#include "ui_modifimagewindow.h"
#include "smartdelete.h"
#include "bddgalleryphoto.h"
#include "image.h"
#include "imagebutton.h"

class ModifImageWindow : public QWidget, private Ui::ModifImageWindow
{
    Q_OBJECT

public:
    explicit ModifImageWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);

private :
    const BddGalleryPhoto* bdd;

    QPixmap imageCorrupt;

    ImageButton* boutonFermer;
    ImageButton* boutonEditName;
    ImageButton* boutonRogner;
    ImageButton* boutonRedim;
    ImageButton* boutonRotateG;
    ImageButton* boutonRotateD;
    ImageButton* boutonAddToAlbum;
    ImageButton* boutonDelete;
    ImageButton* boutonFavPlein;
    ImageButton* boutonFavVide;
    ImageButton* boutonFullScreen;

    QString pathImageCorrupt = ":/img/window/imageCorrupt";

    QString pathboutonFermer = ":/img/button/boutonQuitter";
    QString pathboutonFermerH = ":/img/button/boutonQuitterH";
    QString pathboutonEditName = ":/img/button/boutonEditName";
    QString pathboutonEditNameH = ":/img/button/boutonEditNameH";
    QString pathboutonRogner = ":/img/button/boutonRogner";
    QString pathboutonRognerH = ":/img/button/boutonRognerH";
    QString pathboutonRedim = ":/img/button/boutonRedim";
    QString pathboutonRedimH = ":/img/button/boutonRedimH";
    QString pathboutonRotateG = ":/img/button/boutonRotateG";
    QString pathboutonRotateGH = ":/img/button/boutonRotateGH";
    QString pathboutonRotateD = ":/img/button/boutonRotateD";
    QString pathboutonRotateDH = ":/img/button/boutonRotateDH";
    QString pathboutonAddToAlbum = ":/img/button/boutonAddToAlbum";
    QString pathboutonAddToAlbumH = ":/img/button/boutonAddToAlbumH";
    QString pathboutonDelete = ":/img/button/boutonDelete";
    QString pathboutonDeleteH = ":/img/button/boutonDeleteH";
    QString pathboutonFavPlein = ":/img/button/boutonFavPlein";
    QString pathboutonFavPleinH = ":/img/button/boutonFavPleinH";
    QString pathboutonFavVide = ":/img/button/boutonFavVide";
    QString pathboutonFavVideH = ":/img/button/boutonFavVideH";
    QString pathboutonFullScreen = ":/img/button/boutonPleinEcran";
    QString pathboutonFullScreenH = ":/img/button/boutonPleinEcranH";


public slots:
    void afficheImage(QString name);


    void fermerFenetre();
    void updateImageName();
    void deleteImage();
    void swapIsFavorite();

signals:
    void goToImageWindow();
};
