#pragma once

#include <QObject>
#include <QWidget>
#include "ui_imagewindow.h"

#include <map>


class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

private:
    //std::map<, > listButtons;

signals:

public slots:
};

