#pragma once

#include <QDebug>

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

    //--Getters Setters----------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    //---------------------------------------------------------


private:
    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    QMap<QObject*, QWidget*> assoTab;

    MainMenu* mainmenu;
    HeaderMenu* headermenu;

    AccueilWindow* accueilW;
    AlbumWindow* albumW;
    ImageWindow* imageW;
    HelpWindow* helpW;
    SettingsWindow* settingsW;
    ModifImageWindow* modifimageW;
    //---------------------------------------------------------

public slots:
    void changeWidget();
};

