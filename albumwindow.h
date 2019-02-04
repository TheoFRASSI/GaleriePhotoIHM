#pragma once

#include <ui_albumwindow.h>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include "bddgalleryphoto.h"

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    explicit AlbumWindow(const BddGalleryPhoto* pbdd = nullptr, QWidget *parent = nullptr);
    ~AlbumWindow();
private:
    const BddGalleryPhoto * bdd;

    //void openImage(const QString &fileName);
signals:

public slots:
    void changeTab();
    void searchImage();
private slots:
};
