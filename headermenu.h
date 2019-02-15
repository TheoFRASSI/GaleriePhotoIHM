#pragma once

#include <iostream>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>
#include <imagebutton.h>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>

#include "smartdelete.h"

class HeaderMenu : public QFrame
{
    Q_OBJECT

public:

    //--Constructeur Destructeur-------------
    HeaderMenu(QFrame* headerMenuFrame, QHBoxLayout* menu, QHBoxLayout* layoutSearch, QHBoxLayout* layoutNewAlbum, QHBoxLayout* layoutNewPhoto,
               QHBoxLayout* layoutDisplay, QHBoxLayout* layoutSettings, QSpacerItem* horizontalSpacer, QLabel* labelTitre, QLineEdit* lineEdit, QProgressBar* progBar);
    ~HeaderMenu();
    //---------------------------------------

    //--Getters------------------------------
    ImageButton* getButtonMenu();
    ImageButton* getButtonSearch();
    ImageButton* getButtonNewAlbum();
    ImageButton* getButtonNewPhoto();
    ImageButton* getButtonDisplay();
    ImageButton* getButtonSettings();
    QLabel* getLabelTitre();
    QLineEdit* getLineEdit();
    QProgressBar *getProgressBar();
    //---------------------------------------

private:

    //--Attributs----------------------------
    QFrame* headerMenuFrame;
    QSpacerItem* horizontalSpacer;
    QLabel* labelTitre;
    QLineEdit* lineEdit;
    QProgressBar * progressBar;
    //---------------------------------------

    //--Layouts boutons----------------------
    QHBoxLayout* menu;
    QHBoxLayout* layoutSearch;
    QHBoxLayout* layoutNewAlbum;
    QHBoxLayout* layoutNewPhoto;
    QHBoxLayout* layoutDisplay;
    QHBoxLayout* layoutSettings;
    //---------------------------------------

    //--Boutons------------------------------
    ImageButton* buttonMenu;
    ImageButton* buttonSearch;
    ImageButton* buttonNewAlbum;
    ImageButton* buttonNewPhoto;
    ImageButton* buttonDisplay;
    ImageButton* buttonSettings;
    //---------------------------------------

    //--Images-------------------------------
    QString imageButtonMenuReleased = ":/img/button/menu";
    QString imageButtonMenuPressed = ":/img/button/menuHighlighted";
    QString imageButtonSearchReleased = ":/img/button/search";
    QString imageButtonSearchPressed = ":/img/button/searchHighlighted";
    QString imageButtonNewAlbumReleased = ":/img/button/albumAdd";
    QString imageButtonNewAlbumPressed = ":/img/button/albumAddHighlighted";
    QString imageButtonNewPhotoReleased = ":/img/button/imageAdd";
    QString imageButtonNewPhotoPressed = ":/img/button/imageAddHighlighted";
    QString imageButtonDisplayReleased = ":/img/button/display";
    QString imageButtonDisplayPressed = ":/img/button/displayHighlighted";
    QString imageButtonSettingsReleased = ":/img/button/settings";
    QString imageButtonSettingsPressed = ":/img/button/settingsHighlighted";
    //---------------------------------------

};
