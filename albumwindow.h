#pragma once

#include <ui_albumwindow.h>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QSqlQuery>

#include "bddgalleryphoto.h"
#include "smartdelete.h"
#include "imagebutton.h"

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    explicit AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~AlbumWindow();
    void newBDDRequest(QVector<Album *> albTab);
private:
    const BddGalleryPhoto* bdd;

    //void openImage(const QString &fileName);

    ImageButton* boutonSearch;
    ImageButton* boutonSwitchG;
    ImageButton* boutonSwitchD;
    ImageButton* boutonAdd;

    QString pathBoutonSearch = ":/img/button/search";
    QString pathBoutonSwitchDroit = ":/img/button/boutonSwitchD";
    QString pathBoutonSwitchGauche = ":/img/button/boutonSwitchG";
    QString pathBoutonAdd = ":/img/button/boutonAdd";

    QString pathBoutonSearchH = ":/img/button/searchHighlighted";
    QString pathBoutonSwitchDroitH = ":/img/button/boutonSwitchDH";
    QString pathBoutonSwitchGaucheH = ":/img/button/boutonSwitchGH";
    QString pathBoutonAddH = ":/img/button/boutonAddH";
signals:

public slots:
    void changeTab();
    void addAlbum();
private slots:
    void searchRequest();
};
