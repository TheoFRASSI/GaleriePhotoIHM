#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QObject>
#include <QWidget>
#include "ui_accueilwindow.h"

#include <map>


class ImageWindow : public QWidget, private Ui::AccueilWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

private:
    //std::map<, > listButtons;

signals:

public slots:
};

#endif // IMAGEWINDOW_H
