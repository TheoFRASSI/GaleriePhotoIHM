#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QEvent>

#include "smartdelete.h"

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    //--Constructeur Destructeur-------------------------------
    ImageButton(QWidget * parent);
    ImageButton(int w, int h, QWidget * parent);
    ImageButton(const QString &file, int w, int h, QWidget * parent);
    ImageButton(const QString &filePressed, const QString &fileReleased, int w, int h, QWidget * parent);
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    bool loadImageReleased(const QString &file);
    bool loadImagePressed(const QString &file);
    void loadImageEnable(const QString &file);
    void loadImageDisable(const QString &file);
    void resizeButton(int w, int h);
    //---------------------------------------------------------

public slots:
    void pressedSlot();
    void releasedSlot();
    void setChecked(bool b);
    void setDisable(bool b);
    void setImagePressed();
    void setImageReleased();

protected:
    virtual bool event ( QEvent * e );

private:
    //--Attributs---------------------------------------------
    QPixmap imageReleased;
    QPixmap imagePressed;
    QPixmap imageEnable;
    QPixmap imageDisable;
    //--------------------------------------------------------
};
