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

    bool destroyBdd() const;

    QVector<Album *> getAllAlbums(const QString &orderBy ="name", const QString &searchName = nullptr) const;
    bool insertAlbum(Album entry) const;
    bool imageExists(const QString &name) const;
    bool albumExists(const QString &name) const;
    QVector<Image *> getAllImagesByColor(const QString &searchColor) const;
    bool deleteImageByName(QString name) const;
    bool assocImageWithAlbum(const QVector<Image> images, const QString &nameAlb) const;
    QVector<Image *> getAllImageByAlbum(QString nameAlb) const;

    bool deleteAlbumByName(QString name) const;
    bool updateAlbumName(QString oldName, QString newName) const;

    QVector<Image *> getAllImagesByFav() const;
    QVector<Image *> getAllImagesByDate() const;
    void updateIsFavorite(bool fav, QString nameImg);
    QVector<Image *> getAllImagesByColorAndAlbum(const QString &searchColor, QString name) const;
    QVector<Image *> getAllImagesByFavAndAlbum(QString name) const;
    QVector<Image *> getAllImagesByDateAndAlbum(QString name) const;
private:
    QSqlDatabase bdd;
};

#endif // BDDGALLERYPHOTO_H
