#pragma once

#include <QVector>
#include "image.h"
#include "smartdelete.h"

class Album
{
public:
    Album();
    Album(QString name);
    Album(QString name, QString cover);
    Album(QString name, QString cover, QVector<Image> images);

    QString getCover() const;

    void setCover(QString cover);
    QString getName() const;
private:
    QString name;
    QString cover;
    QVector<Image> images;
    unsigned int nbImages = 1;
    QDate date;
    bool isFavorite;
};
