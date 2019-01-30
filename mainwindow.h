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
    explicit MainWindow(QWidget *parent = nullptr);

private:
    AlbumWindow* albW;
    AccueilWindow* accW;

public slots:
    void changeWid();
};

