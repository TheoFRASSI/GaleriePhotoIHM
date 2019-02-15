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
    //--Constructeur Destructeur------------------------------
    BddGalleryPhoto(QString path);
    ~BddGalleryPhoto();
    //--------------------------------------------------------

    QSqlDatabase getBdd() const;

    bool initBdd();    
    bool open();
    void close();
    bool destroyBdd() const;

    bool imageExists(const QString &name) const;
    bool albumExists(const QString &name) const;

    //--INSERT------------------------------------------------
    bool insertImage(Image entry) const;
    bool insertAlbum(Album entry) const;
    bool assocImageWithAlbum(const QVector<Image> images, const QString &nameAlb) const;
    //--------------------------------------------------------

    //--SELECT------------------------------------------------
    Image* getImageByName(QString name) const;
    QVector<Image *> getAllImages(const QString &orderBy = "name", const QString &searchName = nullptr) const;
    QVector<Album *> getAllAlbums(const QString &orderBy ="name", const QString &searchName = nullptr) const;
    QVector<Image *> getAllImagesByColor(const QString &searchColor) const;
    QVector<Image *> getAllImageByAlbum(QString nameAlb) const;
    QVector<Image *> getAllImagesByFav() const;
    QVector<Image *> getAllImagesByDate() const;
    QVector<Image *> getAllImagesByColorAndAlbum(const QString &searchColor, QString name) const;
    QVector<Image *> getAllImagesByFavAndAlbum(QString name) const;
    QVector<Image *> getAllImagesByDateAndAlbum(QString name) const;
    //--------------------------------------------------------

    //--DELETE------------------------------------------------
    bool deleteImageByName(QString name) const;
    bool deleteAlbumByName(QString name) const;
    //--------------------------------------------------------

    //--UPDATE------------------------------------------------
    bool updateAlbumName(QString oldName, QString newName) const;
    bool updateImageName(QString oldName, QString newName) const;
    void updateIsFavorite(bool fav, QString nameImg) const;
    //--------------------------------------------------------

private:
    QSqlDatabase bdd;
};

#endif // BDDGALLERYPHOTO_H
