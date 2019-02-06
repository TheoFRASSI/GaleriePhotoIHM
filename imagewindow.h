#pragma once

#include <QObject>
#include <QWidget>

#include "ui_imagewindow.h"
#include "smartdelete.h"

class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

private:

signals:

public slots:
};

