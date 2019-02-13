#include "bddgalleryphoto.h"

#include <QSqlQuery>

BddGalleryPhoto::BddGalleryPhoto(QString path)
{
    bdd = QSqlDatabase::addDatabase("QSQLITE");
    bdd.setDatabaseName(path);

    if (!bdd.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        //qDebug() << "Database: connection ok";
        initBdd();
    }
}

BddGalleryPhoto::~BddGalleryPhoto()
{
}

QSqlDatabase BddGalleryPhoto::getBdd() const
{
    return bdd;
}

bool BddGalleryPhoto::open()
{
    return bdd.open();
}

void BddGalleryPhoto::close()
{
    return bdd.close();
}

bool BddGalleryPhoto::insertImage(Image entry) const
{
    bool success = true;
    if(!imageExists(entry.getName())) {
        QSqlQuery query;
        success = true;
        query.prepare("INSERT INTO image(name, path, albums, addDate, color, feeling) VALUES(:name, :path, :albums, :addDate, :color, :feeling)");
        query.bindValue(":name", entry.getName());
        query.bindValue(":path", entry.getPath());
        query.bindValue(":albums", entry.getAlbums());
        query.bindValue(":addDate", entry.getAddDate());
        query.bindValue(":color", entry.getColor());
        query.bindValue(":feeling", entry.getFeeling());
        if (!query.exec())
        {
            qDebug() << "Insert image error";
            success = false;
        } else {
            qDebug() << "Insert Image : " << entry.getName() << "  " << entry.getPath()
                     << "  " <<entry.getAlbums() << "  " << entry.getAddDate()
                     << "  " << entry.getColor() << "  " << entry.getFeeling() << endl;
        }
    } else {
        qDebug() << "L'image existe déjà : " << entry.getName() << endl;
    }
    return success;
}

bool BddGalleryPhoto::insertAlbum(Album entry) const
{
    bool success = false;
    if(!albumExists(entry.getName())) {
        success = true;
        QSqlQuery query;

        query.prepare("INSERT INTO album(name, cover) VALUES(:name, :cover)");
        query.bindValue(":name", entry.getName());
        qDebug() << entry.getName() << " " << entry.getCover();
        query.bindValue(":cover", entry.getCover());
        if (!query.exec())
        {
            qDebug() << "Insert album error";
            success = false;
        } else {
            qDebug() << "Insert album : " << entry.getName() << "  " << entry.getCover() << endl;
        }
    } else {
        qDebug() << "L'album existe déjà : " << entry.getName() << "  " << entry.getCover() << endl;
    }
    return success;
}

Image* BddGalleryPhoto::getImageByName(QString name) const
{

    QSqlQuery query;
    query.prepare("SELECT name, path, albums, addDate, color, feeling FROM image WHERE name = :name");
    query.bindValue(":name", name);
    if (!query.exec())
    {
        qDebug() << "get Image by name error";
    }
    if(query.size() != 0) {
        query.next();
        qDebug() << "Get Image : " << query.value(0).toString() << "  " << query.value(1).toString() << endl;
        Image* res = new Image(query.value(0).toString(), // name
                               query.value(1).toString(), // path
                               query.value(2).toStringList(), // albums
                               query.value(3).toDate(), // addDate
                               query.value(4).toString(), // color
                               query.value(5).toString()); // feeling
        return res;
    }
    return nullptr;

}

QVector<Image*> BddGalleryPhoto::getAllImages(const QString& orderBy, const QString& searchName) const
{
    QVector<Image*> v;
    QSqlQuery query;


    if(searchName != nullptr) {
        query.prepare("SELECT name, path, albums, addDate, color, feeling FROM image WHERE name LIKE '%" +searchName +"%' ORDER BY " + orderBy);
    } else {
        query.prepare("SELECT name, path, albums, addDate, color, feeling FROM image ORDER BY " + orderBy);
    }

    if (!query.exec())
    {
        qDebug() << "get All images error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), // name
                              query.value(1).toString(), // path
                              query.value(2).toStringList(), // albums
                              query.value(3).toDate(), // addDate
                              query.value(4).toString(), // color
                              query.value(5).toString())); // feeling
    }
    return v;
}

QVector<Album*> BddGalleryPhoto::getAllAlbums(const QString& orderBy, const QString& searchName) const
{
    QVector<Album*> v;
    QSqlQuery query;


    if(searchName != nullptr) {
        query.prepare("SELECT name, cover FROM album WHERE name LIKE '%" +searchName +"%' ORDER BY " + orderBy);
    } else {
        query.prepare("SELECT name, cover FROM album ORDER BY " + orderBy);
    }

    if (!query.exec())
    {
        qDebug() << "get All albums error";
    }
    while(query.next()){
        v.push_back(new Album(query.value(0).toString(), query.value(1).toString()));
    }
    return v;
}

bool BddGalleryPhoto::initBdd() {
    QSqlQuery query;
    bool success = true;

    query.prepare("CREATE TABLE image(id INTEGER PRIMARY KEY, name TEXT, path TEXT, albums TEXT, addDate DATE, color TEXT, feeling TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'image': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE album(id INTEGER PRIMARY KEY, name TEXT, cover TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'album': one might already exist.";
        success = false;
    }
    return success;
}

bool BddGalleryPhoto::destroyBdd() const {
    bool success = true;
    QSqlQuery query;
    if (!query.exec("DROP TABLE image"))
    {
        qDebug() << "Delete image error";
        success = false;
    }
    if (!query.exec("DROP TABLE album"))
    {
        qDebug() << "Delete album error";
        success = false;
    }
    return success;
}

bool BddGalleryPhoto::imageExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM image WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "image exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool BddGalleryPhoto::albumExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM album WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "album exists failed: " << checkQuery.lastError();
    }

    return exists;
}


