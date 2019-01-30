#pragma once

#include <ui_albumwindow.h>

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    explicit AlbumWindow(QWidget *parent = nullptr);

private:

signals:

public slots:
};
