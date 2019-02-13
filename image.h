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
    Image(QString name, QString path, QStringList albums, QDate addDate, QColor color, QString feeling);

    QString getName() const;
    QString getPath() const;
    QStringList getAlbums() const;
    QDate getAddDate() const;
    QColor getColor() const;
    QString getFeeling() const;

    void addAlbum(const QString alb);
    void setFeeling(const QString feeling);
    void incrementNbVues();
    void setIsFavorite(bool isFavorite);
    void setIsResized(const bool isResized);
    void setResizedDim(const int height, const int width);

private:
    QString name;
    QStringList albums;
    QString path;
    QDate addDate;
    QColor color;    
    QString feeling;
    //EnumRotate rotation;    

    int nbVues = 0;
    bool isFavorite;
    bool isResized = false;
    int height;
    int width;

};
