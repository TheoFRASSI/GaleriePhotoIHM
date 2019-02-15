#pragma once

#include <QDebug>
#include <QDir>

#include "ui_mainwindow.h"
#include "imagebutton.h"
#include "mainmenu.h"
#include "accueilwindow.h"
#include "albumwindow.h"
#include "imagewindow.h"
#include "helpwindow.h"
#include "settingswindow.h"
#include "modifimagewindow.h"
#include "headermenu.h"
#include "bddgalleryphoto.h"
#include "smartdelete.h"
#include "modifimagewindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:

    //--Constructeur Desctructeur------------------------------
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void initMap();
    //---------------------------------------------------------


private:

    //--Attributs----------------------------------------------
    QMap<QObject*, QWidget*> assoTab;

    MainMenu* mainmenu;
    HeaderMenu* headermenu;
    AccueilWindow* accueilW;
    ImageWindow* imageW;
    HelpWindow* helpW;
    SettingsWindow* settingsW;
    ModifImageWindow* modifimageW;
    AlbumWindow* albumW;
    BddGalleryPhoto* bdd;
    //---------------------------------------------------------

public slots:
    void changeWidget();
    void openImageW();
    void addImage();
    void addAlbum();
    void openModifImageW();
};

