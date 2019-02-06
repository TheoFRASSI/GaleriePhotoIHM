#pragma once

#include <QVector>
#include "image.h"
#include "smartdelete.h"

class Album
{
public:
    Album();

private:
    QString name;
    Image cover;
//    QVector<Image> images;
    unsigned int nbImages;
    QDate date;
    bool isFavorite;
};
