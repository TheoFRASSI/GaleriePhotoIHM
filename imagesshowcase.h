#pragma once

#include "ui_imagesshowcase.h"
#include "imagebutton.h"

class ImagesShowcase : public QWidget, private Ui::ImagesShowcase
{

    Q_OBJECT

public:

    //--Constructeur Desctructeur------------------------------
    explicit ImagesShowcase(QWidget *parent = nullptr);
    ~ImagesShowcase();
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
    ImageButton* leftButton;
    ImageButton* rightButton;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageLeftButton = ":/img/button/left";
    QString imageRightButton = ":/img/button/right";
    QString imageLeftButtonHighlighted = ":/img/button/leftHighlighted";
    QString imageRightButtonHighlighted = ":/img/button/rightHighlighted";
    //---------------------------------------------------------

public slots:
};
