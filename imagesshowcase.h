#pragma once

#include <QLabel>
#include <QDebug>

#include "ui_imagesshowcase.h"
#include "imagebutton.h"
#include "image.h"
#include "smartdelete.h"

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
    void newBDDRequest(QVector<Image *> imagesTab);
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    QVector<Image*> imageTab;
    //---------------------------------------------------------


private:

    //--Attributs----------------------------------------------
    const int LABEL_SIZE = 250;

    ImageButton* leftButton;
    ImageButton* rightButton;
    int cursor = 0;
    QVector<QLabel*> labelsImage;
    int nbLabel = 5;
    QPixmap imageVide;
    QVector<QPixmap> pixmapTab;
    QPixmap aucuneImage;
    QPixmap imageCorrupt;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageLeftButton = ":/img/button/left";
    QString imageRightButton = ":/img/button/right";
    QString imageLeftButtonHighlighted = ":/img/button/leftHighlighted";
    QString imageRightButtonHighlighted = ":/img/button/rightHighlighted";
    QString pathImageVide = ":/img/window/imageVide";
    QString pathAucuneImage = ":/img/window/aucuneImage";
    QString pathImageCorrupt = ":/img/window/imageCorrupt";
    //---------------------------------------------------------

public slots:
    void changeImageRight();
    void changeImageLeft();
};
