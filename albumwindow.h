#pragma once

#include <ui_albumwindow.h>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QSqlQuery>

#include "bddgalleryphoto.h"
#include "formcreatealbum.h"
#include "smartdelete.h"
#include "imagebutton.h"
#include "clickablelabel.h"

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    //--Constructeur Destructeur------------------------------
    explicit AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~AlbumWindow();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void newBDDRequest(QVector<Album *> albTab);
    void generateAlbumAuto();
    void initMap();
    //---------------------------------------------------------
private:
    //--Attributs----------------------------------------------
    const BddGalleryPhoto* bdd;
    FormCreateAlbum * formCreateAlbum;

    ImageButton* boutonSearch;
    ImageButton* boutonSwitchG;
    ImageButton* boutonSwitchD;
    ImageButton* boutonAdd;

    QMap<QString, QString> mapColors;
    QMap<QString, QString> mapAlbums;

    QPixmap etiquette;

    QString pathBoutonSearch = ":/img/button/search";
    QString pathBoutonSwitchDroit = ":/img/button/boutonSwitchD";
    QString pathBoutonSwitchGauche = ":/img/button/boutonSwitchG";
    QString pathBoutonAdd = ":/img/button/boutonAdd";

    QString pathBoutonSearchH = ":/img/button/searchHighlighted";
    QString pathBoutonSwitchDroitH = ":/img/button/boutonSwitchDH";
    QString pathBoutonSwitchGaucheH = ":/img/button/boutonSwitchGH";
    QString pathBoutonAddH = ":/img/button/boutonAddH";

    QString pathEtiquette = ":/img/window/etiquette";
    //-----------------------------------------------------------


signals:
    void albumAutoClicked(QString name);
    void albumClicked(QString name);

public slots:
    void clickAlbum();
    void clickAlbumAuto();
    void changeTab();
    void addAlbum();

private slots:
    void searchRequest();
};
