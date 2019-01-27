#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QEvent>

class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    ImageButton(QWidget * parent);
    ImageButton(int w, int h, QWidget * parent);
    ImageButton(const QString &file, int w, int h, QWidget * parent);
    ImageButton(const QString &filePressed, const QString &fileReleased, int w, int h, QWidget * parent);

    bool loadImageReleased(const QString &file);
    bool loadImagePressed(const QString &file);
    void resizeButton(int w, int h);

public slots:
    void pressedSlot();
    void releasedSlot();
    void setChecked(bool b);
    void setImagePressed();
    void setImageReleased();

protected:
    virtual bool event ( QEvent * e );

private:
    QPixmap imageReleased;
    QPixmap imagePressed;
};
