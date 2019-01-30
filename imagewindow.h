#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QObject>
#include <QWidget>

class ImageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // IMAGEWINDOW_H