#ifndef BDDGALLERYPHOTO_H
#define BDDGALLERYPHOTO_H

#include <QSqlDatabase>
#include <QString>
#include <QDir>
#include <QSqlError>

#include <QtDebug>
#include "album.h"
#include "image.h"
#include "smartdelete.h"



class BddGalleryPhoto
{
public:
    BddGalleryPhoto(QString path);
    ~BddGalleryPhoto();
    bool initBdd();
    QSqlDatabase getBdd() const;
    bool open();
    void close();

    bool insertImage(Image entry) const;
    Image* getImageByName(QString name) const;
    QVector<Image *> getAllImages(const QString &orderBy = "name", const QString &searchName = nullptr) const;

    //bool insertAlbum(Album entry);

    bool destroyBdd() const;

    QVector<Album *> getAllAlbums(const QString &orderBy ="name", const QString &searchName = nullptr) const;
    bool insertAlbum(Album entry) const;
    bool imageExists(const QString &name) const;
    bool albumExists(const QString &name) const;
    QVector<Image *> getAllImagesByColor(const QString &searchColor) const;
private:
    QSqlDatabase bdd;
};

#endif // BDDGALLERYPHOTO_H
