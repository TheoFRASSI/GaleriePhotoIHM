#include "image.h"

Image::Image()
{
    name = "pname";
    path = "ppath";
}

Image::Image(QString pname, QString ppath)
{
    name = pname;
    path = ppath;
}

QString Image::getName()
{
    return name;
}

QString Image::getPath()
{
    return path;
}
