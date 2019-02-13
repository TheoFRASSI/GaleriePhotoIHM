#include "image.h"

Image::Image()
{
    name = "p_name";
    path = "p_path";
}

Image::Image(QString p_name, QString p_path)
{
    name = p_name;
    path = p_path;
}

Image::Image(QString p_name, QString p_path, QStringList p_albums, QDate p_addDate, QString p_color, QString p_feeling)
{
    name = p_name;
    path = p_path;
    albums = p_albums;
    addDate = p_addDate;
    color = p_color;
    feeling = p_feeling;
}

QString Image::getName() const { return name; }

QString Image::getPath() const { return path; }

QStringList Image::getAlbums() const { return albums; }

QDate Image::getAddDate() const { return addDate; }

QString Image::getColor() const { return color; }

QString Image::getFeeling() const { return feeling; }

void Image::addAlbum(const QString alb)
{
    albums.push_back(alb);
}

void Image::setFeeling(const QString p_feeling)
{
    feeling = p_feeling;
}

void Image::incrementNbVues()
{
    nbVues++;
}

void Image::setIsFavorite(bool p_isFavorite)
{
    isFavorite = p_isFavorite;
}

void Image::setIsResized(const bool p_isResized)
{
    isResized = p_isResized;
}

void Image::setResizedDim(const int p_height, const int p_width)
{
    height = p_height;
    width = p_width;
}


