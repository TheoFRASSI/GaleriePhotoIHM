#pragma once

#include "ui_mainwindow.h"
#include "imagebutton.h"
#include "mainmenu.h"
#include "accueilwindow.h"
#include "albumwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:

    //--Constructeur Desctructeur------------------------------
    explicit MainWindow(QWidget *parent = nullptr);
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void initMap();
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    QWidget* currentW;
    //---------------------------------------------------------


private:
    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    QMap<QObject*, QWidget*> assoTab;
    MainMenu* mainmenu;
    AccueilWindow* accW;
    AlbumWindow* albW;
    //---------------------------------------------------------

public slots:
    void changeWid();
};

