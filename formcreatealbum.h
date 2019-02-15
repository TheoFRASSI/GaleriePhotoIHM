#ifndef FORMCREATEALBUM_H
#define FORMCREATEALBUM_H

#include <QDialog>
#include <QFileDialog>
#include <QDate>
#include "image.h"
#include "album.h"
#include "bddgalleryphoto.h"
#include "ui_formcreatealbum.h"
#include "imagebutton.h"

class FormCreateAlbum : public QDialog, private Ui::FormCreateAlbum
{
    Q_OBJECT

public:
    //--Constructeur Destructeur------------------------------
    explicit FormCreateAlbum(const BddGalleryPhoto * bdd, QWidget *parent = nullptr);
    ~FormCreateAlbum();
    //--------------------------------------------------------

    //--Attributs---------------------------------------------
    const BddGalleryPhoto * bdd;
    //--------------------------------------------------------

    //--Fonctions---------------------------------------------
    void clean();
    //--------------------------------------------------------

private:

    //--Attributs---------------------------------------------
    QString selectedName;
    QVector<Image> selectedImages;
    Image selectedCover;

    ImageButton* boutonOk;
    ImageButton* boutonQuitter;
    ImageButton* boutonAddCover;
    ImageButton* boutonAddImages;

    QPixmap imageObli;
    QPixmap imageVide;
    QPixmap imageCorrupt;
    QPixmap cover;

    QString pathBoutonOk = ":/img/button/boutonOk";
    QString pathBoutonOkH = ":/img/button/boutonOkH";
    QString pathBoutonQuitter = ":/img/button/boutonQuitter";
    QString pathBoutonQuitterH = ":/img/button/boutonQuitterH";
    QString pathBoutonAddCover = ":/img/button/boutonAddCover";
    QString pathBoutonAddCoverH = ":/img/button/boutonAddCoverH";
    QString pathBoutonAddImages = ":/img/button/boutonAddImages";
    QString pathBoutonAddImagesH = ":/img/button/boutonAddImagesH";

    QString pathImageObli = ":/img/window/imageObli";
    QString pathImageVide = ":/img/window/imageVide";
    QString pathImageCorrupt = ":/img/window/imageCorrupt";
    //--------------------------------------------------------

signals:
    void albumAdded();
public slots:
    void selectImages();
    void selectCover();
    void validateChoices();
};

#endif // FORMCREATEALBUM_H
