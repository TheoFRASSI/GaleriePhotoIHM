#pragma once

#include <QColor>
#include <QDate>
#include <QString>

class Image
{
public:
    Image();
    Image(QString name, QString path);
    QString getName();
    QString getPath();

private:
    QString name;
    int idAlbum;
    QString path;
    QDate addDate;
    int nbVues;
    QColor color;
    bool isFavorite;
    QString feeling;
    EnumRotate rotation;
    bool isResized;
    int height;
    int width;

};
