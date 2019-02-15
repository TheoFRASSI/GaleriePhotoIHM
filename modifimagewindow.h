#pragma once

#include "ui_modifimagewindow.h"
#include "smartdelete.h"
#include "bddgalleryphoto.h"
#include "image.h"

class ModifImageWindow : public QWidget, private Ui::ModifImageWindow
{
    Q_OBJECT

public:
    explicit ModifImageWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);

private :
    const BddGalleryPhoto* bdd;

    QPixmap imageCorrupt;

    QString pathImageCorrupt = ":/img/window/imageCorrupt";

public slots:
    void afficheImage(QString name);


    void fermerFenetre();
    void updateImageName();
    void deleteImage();
    void swapIsFavorite();

signals:
    void goToImageWindow();
};
