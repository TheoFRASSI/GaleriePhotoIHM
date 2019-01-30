#pragma once

#include <QVector>
#include "image.h"

class Album
{
public:
    Album();

private:
    Image cover;
    QVector<Image> images;
    unsigned int nbImages;
};
