#include "colorbutton.h"

ColorButton::ColorButton(const QString &colorHighlighted, const QString &color, const QString &colorSelectedHighlighted, const QString &colorSelected, int w, int h, QWidget * parent)
            : QPushButton(parent), imageHighlightedName(colorHighlighted), imageName(color), imageSelectedHighlightedName(colorSelectedHighlighted), imageSelectedName(colorSelected)
{
    setMouseTracking(true);
    loadImage(color);
    loadImageHighlighted(colorHighlighted);
    loadImageSelectedHighlighted(colorSelectedHighlighted);
    loadImageSelected(colorSelected);
    setFlat(true);
    setAutoFillBackground(false);
    resize(w,h);
    setIconSize (QSize(w,h));
    connect(this, SIGNAL(pressed()), this, SLOT(pressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(releasedSlot()));
    setStyleSheet("QPushButton{ border: none}");
}

ColorButton::~ColorButton() {
}

/**************
** METHODS **
**************/

bool ColorButton::loadImage(const QString &file)
{
    bool ret = image.load(file);
    setIcon(QIcon(image));
    return ret;
}

bool ColorButton::loadImageHighlighted(const QString &file)
{
    return imageHighlighted.load(file);
}

bool ColorButton::loadImageSelected(const QString &file)
{
    return imageSelected.load(file);
}

bool ColorButton::loadImageSelectedHighlighted(const QString &file)
{
    return imageSelectedHighlighted.load(file);
}

void ColorButton::resizeButton(int w, int h){
    resize(w,h);
    setIconSize (QSize(w,h));
}

/**********
** SLOTS **
**********/

void ColorButton::pressedSlot()
{
    setImagePressed();
}

void ColorButton::releasedSlot()
{
    setImageReleased();
}

void ColorButton::setSelected(bool b)
{
    selected = b;
    if (b)
        setImagePressed();
    else
        setImageReleased();
}

void ColorButton::setImagePressed()
{
    if(selected){
        if (imageSelectedHighlighted.isNull()){
            qDebug() << "Erreur : dans" << __FILE__ << "| Fonction :" << __FUNCTION__ << "| ligne" << __LINE__ << "| imageSelected renvoie NULL";
                return;
        } else {
            setIcon(QIcon(imageSelectedHighlighted));
        }
    } else {
        if (imageHighlighted.isNull()){
            qDebug() << "Erreur : dans" << __FILE__ << "| Fonction :" << __FUNCTION__ << "| ligne" << __LINE__ << "| imageHighlighted renvoie NULL";
            return;
        } else {
            setIcon(QIcon(imageHighlighted));
        }
    }
}

void ColorButton::setImageReleased()
{
    if(selected){
        if (imageSelected.isNull()){
            qDebug() << "Erreur : dans" << __FILE__ << "| Fonction :" << __FUNCTION__ << "| ligne" << __LINE__ << "| imageSelected renvoie NULL";
            return;
        } else {
            setIcon(QIcon(imageSelected));
        }
    } else {
        if (image.isNull()){
            qDebug() << "Erreur : dans" << __FILE__ << "| Fonction :" << __FUNCTION__ << "| ligne" << __LINE__ << "| image renvoie NULL";
            return;
        } else {
             setIcon(QIcon(image));
        }
    }
}

/***************
** PROTECTED **
***************/

bool ColorButton::event ( QEvent * e )
{
    if (e->type()==QEvent::Leave){
        setImageReleased();
    } else if (e->type()==QEvent::Enter){
        setImagePressed();
    } else if(e->type()==QEvent::MouseButtonPress){
        setSelected(!selected);
        setImagePressed();
    }

    return QPushButton::event(e);
}
