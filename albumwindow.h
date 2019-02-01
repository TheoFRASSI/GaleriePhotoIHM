#pragma once

#include <ui_albumwindow.h>

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    explicit AlbumWindow(QWidget *parent = nullptr);

    //void openImage(const QString &fileName);
signals:

public slots:
    void changeTab();
    void searchImage();
private slots:
};
