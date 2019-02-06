#pragma once

#include <QLabel>

#include "ui_imagesshowcase.h"
#include "imagebutton.h"
#include "image.h"

class ImagesShowcase : public QWidget, private Ui::ImagesShowcase
{

    Q_OBJECT

public:

    //--Constructeur Desctructeur------------------------------
    explicit ImagesShowcase(QVector<Image*> imagesTab, QWidget *parent = nullptr);
    ~ImagesShowcase();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void fillShowCase();
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    //---------------------------------------------------------

private:
    //--Fonctions----------------------------------------------

    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    const int LABEL_SIZE = 250;

    ImageButton* leftButton;
    ImageButton* rightButton;
    int cursor = 0;
    QVector<QLabel*> labelsImage;
    int nbLabel = 5;
    QVector<Image*> imageTab;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageLeftButton = ":/img/button/left";
    QString imageRightButton = ":/img/button/right";
    QString imageLeftButtonHighlighted = ":/img/button/leftHighlighted";
    QString imageRightButtonHighlighted = ":/img/button/rightHighlighted";
    //---------------------------------------------------------

public slots:
    void changeImageRight();
    void changeImageLeft();
};
