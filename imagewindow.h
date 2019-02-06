#pragma once

#include <QObject>
#include <QWidget>
#include "ui_imagewindow.h"
#include "bddgalleryphoto.h"
#include "imagesshowcase.h"

#include <map>


class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QVector<Image*> imagesTab, QWidget *parent = nullptr);
    ~ImageWindow();

private:
    //std::map<, > listButtons;

    ImagesShowcase* photos;

    //const BddGalleryPhoto * bdd;

    QVector<QLabel*> vectorListPhoto;

signals:

public slots:
};

