#pragma once

#include <QDebug>

#include "ui_accueilwindow.h"
#include "imagebutton.h"
#include "colorpicker.h"
#include "imagesshowcase.h"
#include "bddgalleryphoto.h"

class AccueilWindow : public QWidget, private Ui::AccueilWindow
{
    Q_OBJECT
public:

    //--Constructeur Desctructeur------------------------------
    explicit AccueilWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~AccueilWindow();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    //---------------------------------------------------------


private:
    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    ColorPicker* colorPicker;
    ColorButton* currentColor;
    ColorButton* buttonColorPicker;
    ImagesShowcase* favoris;
    ImagesShowcase* mostWatched;
    ImagesShowcase* dominantColor;
    ImageButton* buttonMail;
    ImageButton* buttonFacebook;
    ImageButton* buttonTwitter;

    const BddGalleryPhoto * bdd;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageStar = ":/img/window/star";
    QString imageEye = ":/img/window/eye";
    QString mail = ":/img/button/mail";
    QString mailHighlighted = ":/img/button/mailHighlighted";
    QString facebook = ":/img/button/facebook";
    QString facebookHighlighted = ":/img/button/facebookHighlighted";
    QString twitter = ":/img/button/twitter";
    QString twitterHighlighted = ":/img/button/twitterHighlighted";
    //---------------------------------------------------------

public slots:
    void openColorPicker();
    void newColor();

signals:

};
