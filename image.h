#pragma once

#include <QColor>
#include <QDate>
#include <QString>

#include "smartdelete.h"

class Image
{
public:
    Image();
    Image(QString name, QString path);
    Image(QString name, QString path, QDate addDate, QString color, QString feeling, bool isFavorite);

    QString getName() const;
    QString getPath() const;
    QDate getAddDate() const;
    QString getColor() const;
    QString getFeeling() const;
    bool getIsFavorite() const;

    void setFeeling(const QString feeling);    
    void setIsFavorite(bool isFavorite);

    /*void incrementNbVues();
    void setIsResized(const bool isResized);
    void setResizedDim(const int height, const int width);*/

    void setPath(const QString &value);

private:
    QString name;
    QString path;
    QDate addDate;
    QString color;
    QString feeling;
    bool isFavorite;

    /*EnumRotate rotation;
    int nbVues = 0;
    bool isResized = false;
    int height;
    int width;*/

};
