#pragma once

#include <QDebug>

#include "ui_accueilwindow.h"
#include "imagebutton.h"
#include "colorpicker.h"
#include "imagesshowcase.h"
#include "bddgalleryphoto.h"
#include "smartdelete.h"

class AccueilWindow : public QWidget, private Ui::AccueilWindow
{
    Q_OBJECT
public:

    //--Constructeur Destructeur-------------------------------
    explicit AccueilWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~AccueilWindow();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void initShowCase();
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    ImagesShowcase *getFavoris() const;
    void setFavoris(ImagesShowcase *value);

    ImagesShowcase *getDominantColor() const;
    void setDominantColor(ImagesShowcase *value);
    //---------------------------------------------------------

private:
    //--Fonctions----------------------------------------------
    void initColors();
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    ColorPicker* colorPicker;
    ColorButton* currentColor;
    ColorButton* buttonColorPicker;
    ImagesShowcase* favoris;
    ImagesShowcase* dominantColor;
    ImageButton* buttonMail;
    ImageButton* buttonFacebook;
    ImageButton* buttonTwitter;
    QMap<ColorButton*, QString> colors;

    const BddGalleryPhoto * bdd;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageStar = ":/img/window/star";
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
