#pragma once

#include "ui_settingswindow.h"
#include "smartdelete.h"

#include <QMap>
#include <QVector>
#include <QFileDialog>
#include <QDebug>

#include "bddgalleryphoto.h"

class SettingsWindow : public QWidget, private Ui::SettingsWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~SettingsWindow();

    QString searchDirectoryPath();

private:
    const BddGalleryPhoto* bdd;

    //QMap<QString*, QString*> * paths;
    QVector<QString *> paths;
    QString * selectedPath;

signals:

public slots:
    void addPath();
    void suppressedPath();
    void addImagesFromPath(QString * path);
    void addImageToBdd(QString pathImage, QString nameImage);
    //void newBDDRequest(QVector<Image*> imagesTab);
};

