#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QEvent>
#include <QDebug>

class ColorButton : public QPushButton
{
    Q_OBJECT

public:
    ColorButton(const QString &colorHighlighted, const QString &color, const QString &colorSelectedHighlighted, const QString &colorSelected, int w, int h, QWidget * parent);
    ~ColorButton();

    bool loadImage(const QString &file);
    bool loadImageHighlighted(const QString &file);
    bool loadImageSelectedHighlighted(const QString &file);
    bool loadImageSelected(const QString &file);
    void resizeButton(int w, int h);

    QString imageHighlightedName;
    QString imageName;
    QString imageSelectedHighlightedName;
    QString imageSelectedName;

public slots:
    void pressedSlot();
    void releasedSlot();
    void setImagePressed();
    void setImageReleased();
    void setSelected(bool b);

protected:
    virtual bool event ( QEvent * e );

private:
    QPixmap imageHighlighted;
    QPixmap image;
    QPixmap imageSelectedHighlighted;
    QPixmap imageSelected;

    bool selected = false;
};
