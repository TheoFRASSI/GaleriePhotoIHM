#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QEvent>
#include <QDebug>

#include "smartdelete.h"

class ColorButton : public QPushButton
{
    Q_OBJECT

public:
    //--Constructeur Destructeur------------------------------
    ColorButton(const QString &colorHighlighted, const QString &color, const QString &colorSelectedHighlighted, const QString &colorSelected, int w, int h, QWidget * parent);
    ~ColorButton();
    //--------------------------------------------------------

    //--Fonctions----------------------------------------------
    bool loadImage(const QString &file);
    bool loadImageHighlighted(const QString &file);
    bool loadImageSelectedHighlighted(const QString &file);
    bool loadImageSelected(const QString &file);
    void resizeButton(int w, int h);
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    QString imageHighlightedName;
    QString imageName;
    QString imageSelectedHighlightedName;
    QString imageSelectedName;
    //---------------------------------------------------------

public slots:
    void pressedSlot();
    void releasedSlot();
    void setImagePressed();
    void setImageReleased();
    void setSelected(bool b);

protected:
    virtual bool event ( QEvent * e );

private:
    //--Attributs----------------------------------------------
    QPixmap imageHighlighted;
    QPixmap image;
    QPixmap imageSelectedHighlighted;
    QPixmap imageSelected;

    bool selected = false;
    //---------------------------------------------------------

};
