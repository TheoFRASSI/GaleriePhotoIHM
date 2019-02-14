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
        query.prepare("INSERT INTO image(name, path, addDate, color, feeling, isFavorite) VALUES(:name, :path, :addDate, :color, :feeling, :isFavorite)");
        query.bindValue(":name", entry.getName());
        query.bindValue(":path", entry.getPath());
        query.bindValue(":addDate", entry.getAddDate());
        query.bindValue(":color", entry.getColor());
        query.bindValue(":feeling", entry.getFeeling());
        query.bindValue(":isFavorite", entry.getIsFavorite());
        if (!query.exec())
        {
            qDebug() << "Insert image error";
            success = false;
        } else {
            qDebug() << "Insert Image : " << entry.getName() << "  " << entry.getPath() << "  " << entry.getAddDate()
                     << "  " << entry.getColor() << "  " << entry.getFeeling() << "  " << entry.getIsFavorite() << endl;
        }
    } else {
        qDebug() << "L'image existe déjà : " << entry.getName() << endl;
    }
    return success;
}

bool BddGalleryPhoto::deleteImageByName(QString name) const
{
    bool success = true;
    if(imageExists(name)) {
        QSqlQuery query;
        success = true;
        query.prepare("DELETE FROM image WHERE name = :name");
        query.bindValue(":name", name);
        if (!query.exec())
        {
            qDebug() << "delete image error";
            success = false;
        } else {
            qDebug() << "delete image : " << name << endl;
        }
    } else {
        qDebug() << "L'image n'existe pas : " << name << endl;
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
    query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image WHERE name = :name");
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
                               query.value(3).toDate(), // addDate
                               query.value(4).toString(), // color
                               query.value(5).toString(),
                               query.value(6).toBool()); // feeling
        return res;
    }
    return nullptr;

}

Image* BddGalleryPhoto::getImageByAlbum(QString nameAlb) const
{
    QSqlQuery getAlbQuery;
    getAlbQuery.prepare("SELECT idAlb FROM album WHERE name = :nameAlb");
    getAlbQuery.bindValue(":nameAlb", nameAlb);
    if (!getAlbQuery.exec())
    {
        qDebug() << "get Image by album, getAlbQuery error";
    }
    if(!getAlbQuery.next()) {
        qDebug() << "cet album n'existe pas";
        return nullptr;
    }
    int idAlb = getAlbQuery.value(0).toInt();


    QSqlQuery query;
    query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image INNER JOIN assoc ON image.idImg = assoc.idImg WHERE idAlb = :idAlb");
    query.bindValue(":idAlb", idAlb);
    if (!query.exec())
    {
        qDebug() << "get Image by album error";
    }
    if(query.size() != 0) {
        query.next();
        qDebug() << "Get Image : " << query.value(0).toString() << "  " << query.value(1).toString() << endl;
        Image* res = new Image(query.value(0).toString(), // name
                               query.value(1).toString(), // path
                               query.value(3).toDate(), // addDate
                               query.value(4).toString(), // color
                               query.value(5).toString(),
                               query.value(6).toBool()); // feeling
        return res;
    }
    return nullptr;

}

QVector<Image*> BddGalleryPhoto::getAllImagesByColor(const QString& searchColor) const
{
    QVector<Image*> v;
    QSqlQuery query;


    if(searchColor != nullptr) {
        query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image WHERE color = '" + searchColor + "' ORDER BY name");
    }

    if (!query.exec())
    {
        qDebug() << "get All images by Color error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), // name
                              query.value(1).toString(), // path
                              query.value(3).toDate(), // addDate
                              query.value(4).toString(), // color
                              query.value(5).toString(),
                              query.value(6).toBool())); // feeling
    }
    return v;
}

QVector<Image*> BddGalleryPhoto::getAllImagesByDate() const
{
    QVector<Image*> v;
    QSqlQuery query;


    query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image ORDER BY addDate");


    if (!query.exec())
    {
        qDebug() << "get All images by Date error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), // name
                              query.value(1).toString(), // path
                              query.value(3).toDate(), // addDate
                              query.value(4).toString(), // color
                              query.value(5).toString(),
                              query.value(6).toBool())); // feeling
    }
    return v;
}

QVector<Image*> BddGalleryPhoto::getAllImagesByFav() const
{
    QVector<Image*> v;
    QSqlQuery query;

    query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image WHERE isFavorite = 1");

    if (!query.exec())
    {
        qDebug() << "get All images by fav error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), // name
                              query.value(1).toString(), // path
                              query.value(3).toDate(), // addDate
                              query.value(4).toString(), // color
                              query.value(5).toString(), // feeling
                              query.value(6).toBool())); // fav
    }
    return v;
}

QVector<Image*> BddGalleryPhoto::getAllImages(const QString& orderBy, const QString& searchName) const
{
    QVector<Image*> v;
    QSqlQuery query;


    if(searchName != nullptr) {
        query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image WHERE name LIKE '%" +searchName +"%' ORDER BY " + orderBy);
    } else {
        query.prepare("SELECT name, path, addDate, color, feeling, isFavorite FROM image ORDER BY " + orderBy);
    }

    if (!query.exec())
    {
        qDebug() << "get All images error";
    }
    while(query.next()){
        v.push_back(new Image(query.value(0).toString(), // name
                              query.value(1).toString(), // path
                              query.value(3).toDate(), // addDate
                              query.value(4).toString(), // color
                              query.value(5).toString(),
                              query.value(6).toBool())); // feeling
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

    query.prepare("CREATE TABLE IF NOT EXISTS image(idImg INTEGER PRIMARY KEY, name TEXT, path TEXT, addDate DATE, color TEXT, feeling TEXT, isFavorite INTEGER);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'image': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE IF NOT EXISTS album(idAlb INTEGER PRIMARY KEY, name TEXT, cover TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'album': one might already exist.";
        success = false;
    }

    query.prepare("CREATE TABLE IF NOT EXISTS assoc(idImg INTEGER, idAlb INTEGER, "
                  "FOREIGN KEY (idImg) REFERENCES image(idImg), "
                  "FOREIGN KEY (idAlb) REFERENCES album(idAlb));");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'assoc'";
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
    if (!query.exec("DROP TABLE assoc"))
    {
        qDebug() << "Delete assoc error";
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

bool BddGalleryPhoto::assocImageWithAlbum(const QVector<Image> images, const QString& nameAlb) const {

    QSqlQuery getAlbQuery;
    getAlbQuery.prepare("SELECT idAlb FROM album WHERE name = :nameAlb");
    getAlbQuery.bindValue(":nameAlb", nameAlb);
    if (!getAlbQuery.exec()){
        qDebug() << "assoc Image with album, get alb query error";
        return false;
    }
    getAlbQuery.next();
    int idAlb = getAlbQuery.value(0).toInt();

    for (int i = 0; i < images.size(); i++) {
        QSqlQuery getImgQuery;
        getImgQuery.prepare("SELECT idImg FROM image WHERE name = :nameImg");
        getImgQuery.bindValue(":nameImg", images[i].getName());
        if (!getImgQuery.exec()){
            qDebug() << "assoc Image with album, get img query error";
            return false;
        }
        getImgQuery.next();
        int idImg = getImgQuery.value(0).toInt();

        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO assoc(idImg, idAlb) VALUES (:idImg, :idAlb)");
        insertQuery.bindValue(":idImg", idImg);
        insertQuery.bindValue(":idAlb", idAlb);
        if (!insertQuery.exec()){
            qDebug() << "assoc Image with album, insert query error";
            return false;
        }
        qDebug() << "img :" << images[i].getName() << "liee a" << nameAlb;
    }
    return true;
}

void BddGalleryPhoto::updateIsFavorite(bool fav, QString nameImg) {
    QSqlQuery upQuery;
    upQuery.prepare("UPDATE image SET isFavorite = :fav WHERE name = :nameImg");
    upQuery.bindValue(":nameImg", nameImg);
    upQuery.bindValue(":fav", fav);
}


