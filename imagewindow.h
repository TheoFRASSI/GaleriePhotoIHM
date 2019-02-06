#pragma once

#include <QObject>
#include <QWidget>
<<<<<<< HEAD
#include "ui_imagewindow.h"
#include "bddgalleryphoto.h"
#include "imagesshowcase.h"

#include <map>
=======
>>>>>>> refs/remotes/origin/master

#include "ui_imagewindow.h"
#include "smartdelete.h"

class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QVector<Image*> imagesTab, QWidget *parent = nullptr);
    ~ImageWindow();

private:

    ImagesShowcase* photos;

    //const BddGalleryPhoto * bdd;

    QVector<QLabel*> vectorListPhoto;

signals:

public slots:
};

