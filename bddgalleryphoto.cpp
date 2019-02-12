#include "bddgalleryphoto.h"

#include <QSqlQuery>

BddGalleryPhoto::BddGalleryPhoto(QString path)
{
    bdd = QSqlDatabase::addDatabase("QSQLITE");
    bdd.setDatabaseName(path);

    if (!bdd.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
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
    QSqlQuery query;
    bool success = true;
    query.prepare("INSERT INTO image(name, path) VALUES(:name, :path)");
    query.bindValue(":name", entry.getName());
    query.bindValue(":path", entry.getPath());
    if (!query.exec())
    {
        qDebug() << "Insert image error";
        success = false;
    } else {
        qDebug() << "Insert Image : " << entry.getName() << "  " << entry.getPath() << endl;
    }
    return success;
}

Image* BddGalleryPhoto::getImageByName(QString name) const
{

    QSqlQuery query;
    query.prepare("SELECT name, path FROM image WHERE name = :name");
    query.bindValue(":name", name);
    if (!query.exec())
    {
        qDebug() << "get Image by name error";
    }
    if(query.size() != 0) {
        query.next();
        qDebug() << "Get Image : " << query.value(0).toString() << "  " << query.value(1).toString() << endl;
        Image* res = new Image(query.value(0).toString(), query.value(1).toString());
        return res;
    }
    return nullptr;

}

QVector<Image*> BddGalleryPhoto::getAllImages(const QString& orderBy, const QString& searchName) const
{
    QVector<Image*> v;
    QSqlQuery query;


    if(searchName != nullptr) {
        query.prepare("SELECT name, path FROM image WHERE name LIKE '%" +searchName +"%' ORDER BY " + orderBy);
    } else {
        query.prepare("SELECT name, path FROM image ORDER BY " + orderBy);
    }

    if (!query.exec())
    {
        qDebug() << "get All images error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), query.value(1).toString()));
    }
    return v;
}

bool BddGalleryPhoto::initBdd() {
    QSqlQuery query;
    bool success = true;

    query.prepare("CREATE TABLE image(id INTEGER PRIMARY KEY, name TEXT, path TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'image': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE album(id INTEGER PRIMARY KEY, name TEXT, image INTEGER);");
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


