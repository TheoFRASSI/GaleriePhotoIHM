#ifndef BDDGALLERYPHOTO_H
#define BDDGALLERYPHOTO_H

#include <QSqlDatabase>
#include <QString>
#include <QDir>

#include <QtDebug>
#include "album.h"
#include "image.h"



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



private:
    QSqlDatabase bdd;
};

#endif // BDDGALLERYPHOTO_H
