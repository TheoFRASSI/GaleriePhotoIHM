#pragma once

#include "ui_settingswindow.h"

#include <QMap>
#include <QVector>
#include <QFileDialog>
#include <QDebug>

class SettingsWindow : public QWidget, private Ui::SettingsWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    QString searchDirectoryPath();

private:
    //QMap<QString*, QString*> * paths;
    QVector<QString *> paths;
    QString * selectedPath;

signals:

public slots:
    void addPath();
    void suppressedPath();
};

