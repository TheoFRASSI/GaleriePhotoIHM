#include "imagebutton.h"

ImageButton::ImageButton(QWidget* parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setFlat(true);
    connect(this, SIGNAL(pressed()), this, SLOT(pressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(releasedSlot()));
    setStyleSheet("QPushButton{ border: none}");
}

ImageButton::ImageButton(int w, int h, QWidget * parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setFlat(true);
    resize(w,h);
    setIconSize (QSize(w,h));
    connect(this, SIGNAL(pressed()), this, SLOT(pressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(releasedSlot()));
    setStyleSheet("QPushButton{ border: none}");
}

ImageButton::ImageButton(const QString &file, int w, int h, QWidget * parent) : QPushButton(parent)
{
    setMouseTracking(true);
    loadImageReleased(file);
    setFlat(true);
    resize(w,h);
    setIconSize (QSize(w,h));
    connect(this, SIGNAL(pressed()), this, SLOT(pressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(releasedSlot()));
    setStyleSheet("QPushButton{ border: none}");
}

ImageButton::ImageButton(const QString &filePressed, const QString &fileReleased, int w, int h, QWidget * parent) : QPushButton(parent)
{
    setMouseTracking(true);
    loadImageReleased(fileReleased);
    loadImagePressed(filePressed);
    setFlat(true);
    setAutoFillBackground(false);
    resize(w,h);
    setIconSize (QSize(w,h));
    connect(this, SIGNAL(pressed()), this, SLOT(pressedSlot()));
    connect(this, SIGNAL(released()), this, SLOT(releasedSlot()));
    setStyleSheet("QPushButton{ border: none}");
}

/**************
** METHODS **
**************/

bool ImageButton::loadImageReleased(const QString &file)
{
    bool result=imageReleased.load(file);
    setIcon(QIcon(imageReleased));
    return result;
}

bool ImageButton::loadImagePressed(const QString &file)
{
    return imagePressed.load(file);
}

void ImageButton::resizeButton(int w, int h){
    resize(w,h);
    setIconSize (QSize(w,h));
}

/**********
** SLOTS **
**********/

void ImageButton::pressedSlot()
{
    if (!isCheckable()){
        setImagePressed();
    }
}

void ImageButton::releasedSlot()
{
    if (isCheckable())
    {
        if (isChecked())
            setImagePressed();
        else
            setImageReleased();
    }
    else
        setImageReleased();

}

void ImageButton::setChecked(bool b)
{
    QAbstractButton::setChecked(b);
    if (b)
        setImagePressed();
    else
        setImageReleased();
}

void ImageButton::setDisable(bool b){
    QAbstractButton::setEnabled(!b);
    if (b)
        setIcon(QIcon(imageDisable));
    else
        setIcon(QIcon(imageEnable));
}

void ImageButton::loadImageDisable(const QString &file){
    imageDisable.load(file);
}

void ImageButton::loadImageEnable(const QString &file){
    imageEnable.load(file);
}

void ImageButton::setImagePressed()
{
    if (imagePressed.isNull())
            return;
    setIcon(QIcon(imagePressed));
}

void ImageButton::setImageReleased()
{
    if (imageReleased.isNull())
            return;
    setIcon(QIcon(imageReleased));
}

/***************
** PROTECTED **
***************/

bool ImageButton::event ( QEvent * e )
{
    if (!isCheckable())
    {
        if (e->type()==QEvent::Leave)
                setImageReleased();
        else if (e->type()==QEvent::Enter)
            setImagePressed();
    }

    return QPushButton::event(e);
}
