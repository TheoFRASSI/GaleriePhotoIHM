#include "album.h"

Album::Album(QString p_name)
{
    name = p_name;
}

Album::Album(QString p_name, QString p_cover)
{
    name = p_name;
    cover = p_cover;
}

Album::Album(QString p_name, QString p_cover, QVector<Image> p_images)
{
    name = p_name;
    cover = p_cover;
    images = p_images;
}

QString Album::getName() const
{
    return name;
}

QString Album::getCover() const
{
    return cover;
}

void Album::setCover(QString p_cover)
{
    cover = p_cover;
}
