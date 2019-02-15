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

    void deleteImagesFromPath(QString *path);

private:
    const BddGalleryPhoto* bdd;

    QVector<QString *> paths;
    QString * selectedPath;

signals:

public slots:
    void addPath();
    void suppressedPath();
    void addImagesFromPath(QString * path);
    void addImageToBdd(QString pathImage, QString nameImage);
};

