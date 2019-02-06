#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>

#include "bddgalleryphoto.h"
#include "ui_imagewindow.h"
#include "smartdelete.h"

class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QVector<Image*> imagesTab, QWidget *parent = nullptr);
    ~ImageWindow();
    void newBDDRequest(QVector<Image *> imagesTab);

private:

    const int NB_IMAGES = 6;
    const int SIZE_IMAGE = 250;

    QPixmap imageVide;
    QPixmap aucuneImage;

    QString pathImageVide = ":/img/window/imageVide";
    QString pathAucuneImage = ":/img/window/aucuneImage";

signals:

public slots:
};

