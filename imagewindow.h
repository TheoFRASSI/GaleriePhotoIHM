#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>

#include "bddgalleryphoto.h"
#include "ui_imagewindow.h"
#include "smartdelete.h"

#include <QFileDialog>

class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(const BddGalleryPhoto* pbdd, QVector<Image*> imagesTab, QWidget *parent = nullptr);
    ~ImageWindow();
    void newBDDRequest(QVector<Image *> imagesTab);


private:

    const int NB_IMAGES = 6;
    const int SIZE_IMAGE = 250;

    const BddGalleryPhoto* bdd;

    QPixmap imageVide;
    QPixmap aucuneImage;

    QString pathImageVide = ":/img/window/imageVide";
    QString pathAucuneImage = ":/img/window/aucuneImage";

signals:

public slots:
    void searchImage();
};

