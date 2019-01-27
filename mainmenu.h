#pragma once

#include <iostream>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <imagebutton.h>

class MainMenu : public QFrame
{
    Q_OBJECT

public:
    MainMenu(QFrame* container, QVBoxLayout* layoutHome, QVBoxLayout* layoutAlbum, QVBoxLayout* layoutImage, QVBoxLayout* layoutHelp);
    ~MainMenu();

private:
    const int MINWIDTH = 70;
    const int MAXWIDTH = 170;
    bool open = false;

    QFrame* container;

    //--Layouts boutons----------------------
    QVBoxLayout* layoutHome;
    QVBoxLayout* layoutAlbum;
    QVBoxLayout* layoutImage;
    QVBoxLayout* layoutHelp;
    //---------------------------------------

    //--Boutons------------------------------
    ImageButton* buttonHome;
    ImageButton* buttonAlbum;
    ImageButton* buttonImage;
    ImageButton* buttonHelp;
    //---------------------------------------

    //--Images-------------------------------
    QString imageButtonHomeReleased = ":/img/button/home";
    QString imageButtonHomePressed = ":/img/button/homeHighlighted";
    QString imageButtonAlbumReleased = ":/img/button/album";
    QString imageButtonAlbumPressed = ":/img/button/albumHighlighted";
    QString imageButtonImageReleased = ":/img/button/image";
    QString imageButtonImagePressed = ":/img/button/imageHighlighted";
    QString imageButtonHelpReleased = ":/img/button/help";
    QString imageButtonHelpPressed = ":/img/button/helpHighlighted";
    QString imageLargeButtonHomeReleased = ":/img/button/homeLarge";
    QString imageLargeButtonHomePressed = ":/img/button/homeHighlightedLarge";
    QString imageLargeButtonAlbumReleased = ":/img/button/albumLarge";
    QString imageLargeButtonAlbumPressed = ":/img/button/albumHighlightedLarge";
    QString imageLargeButtonImageReleased = ":/img/button/imageLarge";
    QString imageLargeButtonImagePressed = ":/img/button/imageHighlightedLarge";
    QString imageLargeButtonHelpReleased = ":/img/button/helpLarge";
    QString imageLargeButtonHelpPressed = ":/img/button/helpHighlightedLarge";
    //---------------------------------------

    //--Fonctions----------------------------
    void changeButtons();
    //---------------------------------------

public slots:
    void openMenu();
};
