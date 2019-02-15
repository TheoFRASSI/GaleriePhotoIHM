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
    if (bdd.isOpen()) {
            bdd.close();
    }
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

    QSqlQuery query;

    if(name != nullptr) {
        if(imageExists(name)) {
            query.prepare("SELECT idImg FROM image WHERE name = :name ");
            query.bindValue(":name", name);

            if (!query.exec())
            {
                qDebug() << "Erreur : requete pour récupérer <idImg> dans la table <image> a échoué, dans" << __FUNCTION__;
                success = false;
            }
            query.next();
            int id = query.value(0).toInt();

            query.prepare("DELETE FROM assoc WHERE idImg = :idImg");
            query.bindValue(":idImg", id);

            if (!query.exec())
            {
                qDebug() << "Erreur : la suppression des images dans la table <assoc> suivant le parametre <idImg> =" << id << "a échoué, dans" << __FUNCTION__;
                success = false;
            }else {
                qDebug() << "delete image : " << name << endl;

                query.prepare("DELETE FROM image WHERE idImg = :idImg");
                query.bindValue(":idImg", id);

                if (!query.exec())
                {
                    qDebug() << "Erreur : la suppression de l'image dans la table <image> suivant le parametre <idImg> =" << id << "a échoué, dans" << __FUNCTION__;
                    success = false;
                } else {
                    if (!imageExists(name))
                    {
                        qDebug() << "Image" << name << "supprimée avec succes";
                        return success;
                    } else {
                        qDebug() << "Erreur : la suppression de l'image dans la table <image> suivant le parametre <idImg> =" << id << "a échoué, dans" << __FUNCTION__;
                        success = false;
                    }
                }
            }
        } else {
            qDebug() << "Erreur : L'image" << name << "n'existe pas dans la table <image>, dans" << __FUNCTION__;
            success = false;
        }
    } else {
        qDebug() << "Erreur : Le parametre <name> est NULL, dans" << __FUNCTION__;
        success = false;
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

QVector<Image *> BddGalleryPhoto::getAllImageByAlbum(QString nameAlb) const
{
    QSqlQuery getAlbQuery;
    QVector<Image *> albVec;
    getAlbQuery.prepare("SELECT idAlb FROM album WHERE name = :nameAlb");
    getAlbQuery.bindValue(":nameAlb", nameAlb);
    if (!getAlbQuery.exec())
    {
        qDebug() << "get Image by album, getAlbQuery error";
    }
    if(!getAlbQuery.next()) {
        qDebug() << "cet album n'existe pas";
        return albVec;
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
        while(query.next()){
            qDebug() << "Get Image : " << query.value(0).toString() << "  " << query.value(1).toString() << endl;
            albVec.push_back(new Image(query.value(0).toString(), // name
                                   query.value(1).toString(), // path
                                   query.value(3).toDate(), // addDate
                                   query.value(4).toString(), // color
                                   query.value(5).toString(),
                                   query.value(6).toBool())); // feeling
        }
    }
    return albVec;
}

bool BddGalleryPhoto::deleteAlbumByName(QString name) const{

    bool success = true;

    QSqlQuery query;

    if(name != nullptr) {
        if(albumExists(name)) {
            query.prepare("SELECT idAlb FROM album WHERE name = :name ");
            query.bindValue(":name", name);

            if (!query.exec())
            {
                qDebug() << "Erreur : requete pour récupérer <idAlb> dans la table <albums> a échoué, dans" << __FUNCTION__;
                success = false;
            }

            query.next();
            int id = query.value(0).toInt();

            query.prepare("DELETE FROM assoc WHERE idAlb = :idAlb");
            query.bindValue(":idAlb", id);

            if (!query.exec())
            {
                qDebug() << "Erreur : la suppression des images dans la table <assoc> suivant le parametre <idAlb> =" << id << "a échoué, dans" << __FUNCTION__;
                success = false;
            } else {
                qDebug() << "delete album : " << name << endl;

                query.prepare("DELETE FROM album WHERE idAlb = :idAlb");
                query.bindValue(":idAlb", id);

                if (!query.exec())
                {
                    qDebug() << "Erreur : la suppression de l'album dans la table <album> suivant le parametre <idAlb> =" << id << "a échoué, dans" << __FUNCTION__;
                    success = false;
                } else {
                    if (!albumExists(name))
                    {
                        qDebug() << "Album" << name << "supprimé avec succes";
                        return success;
                    } else {
                        qDebug() << "Erreur : la suppression de l'album dans la table <album> suivant le parametre <idAlb> =" << id << "a échoué, dans" << __FUNCTION__;
                        success = false;
                    }
                }
            }
        } else {
            qDebug() << "Erreur : L'album" << name << "n'existe pas dans la table <album>, dans" << __FUNCTION__;
            success = false;
        }
    } else {
        qDebug() << "Erreur : Le parametre <name> est NULL, dans" << __FUNCTION__;
        success = false;
    }
    return success;
}

bool BddGalleryPhoto::updateAlbumName(QString oldName, QString newName) const{
    bool success = true;
    QSqlQuery query;

    if(oldName != nullptr) {
        if(albumExists(newName) == false) {
            query.prepare("UPDATE album SET name = :newName WHERE name = :oldName");
            query.bindValue(":oldName", oldName);
            query.bindValue(":newName", newName);

            if (!query.exec())
            {
                qDebug() << "Erreur : le renommage de l'album" << oldName << "dans la table <album> avec le nouveau nom :" << newName << "a échoué, dans" << __FUNCTION__;
                success = false;
            } else {
                qDebug() << "Album" << oldName << "renommé avec succes en" << newName;
                return success;
            }
        }else {
            qDebug() << "Erreur : L'album" << newName << "existe deja dans la table <album>, dans" << __FUNCTION__;
            success = false;
        }
    } else {
        qDebug() << "Erreur : Le parametre <oldName> est NULL, dans" << __FUNCTION__;
        success = false;
    }
    return success;
}

bool BddGalleryPhoto::updateImageName(QString oldName, QString newName) const{
    bool success = true;
    QSqlQuery query;

    if(oldName != nullptr) {
        if(imageExists(newName) == false) {
            query.prepare("UPDATE image SET name = :newName WHERE name = :oldName");
            query.bindValue(":oldName", oldName);
            query.bindValue(":newName", newName);

            if (!query.exec())
            {
                qDebug() << "Erreur : le renommage de l'image" << oldName << "dans la table <image> avec le nouveau nom :" << newName << "a échoué, dans" << __FUNCTION__;
                success = false;
            } else {
                qDebug() << "image" << oldName << "renommé avec succes en" << newName;
                return success;
            }
        }else {
            qDebug() << "Erreur : L'image" << newName << "existe deja dans la table <image>, dans" << __FUNCTION__;
            success = false;
        }
    } else {
        qDebug() << "Erreur : Le parametre <oldName> est NULL, dans" << __FUNCTION__;
        success = false;
    }
    return success;
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

QVector<Image*> BddGalleryPhoto::getAllImagesByColorAndAlbum(const QString& searchColor, QString name) const
{
    QVector<Image*> v;
    QSqlQuery query;

    if(searchColor != nullptr) {
        query.prepare("SELECT image.name, image.path, image.addDate, image.color, image.feeling, image.isFavorite FROM (image INNER JOIN assoc ON image.idImg = assoc.idImg) INNER JOIN album ON assoc.idAlb = album.idAlb WHERE image.color = '" + searchColor + "' AND album.name = '" + name + "'ORDER BY image.name");
    }

    if (!query.exec())
    {
        qDebug() << "get All images by Color and Album error";
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

QVector<Image*> BddGalleryPhoto::getAllImagesByDateAndAlbum(QString name) const
{
    QVector<Image*> v;
    QSqlQuery query;

    query.prepare("SELECT image.name, image.path, image.addDate, image.color, image.feeling, image.isFavorite FROM (image INNER JOIN assoc ON image.idImg = assoc.idImg) INNER JOIN album ON assoc.idAlb = album.idAlb WHERE album.name = '" + name +"' ORDER BY image.addDate");

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

QVector<Image*> BddGalleryPhoto::getAllImagesByFavAndAlbum(QString name) const
{
    QVector<Image*> v;
    QSqlQuery query;

    query.prepare("SELECT image.name, image.path, image.addDate, image.color, image.feeling, image.isFavorite FROM (image INNER JOIN assoc ON image.idImg = assoc.idImg) INNER JOIN album ON assoc.idAlb = album.idAlb WHERE image.isFavorite = 1 AND album.name = '" + name + "'");

    if (!query.exec())
    {
        qDebug() << "get All images by fav and album error";
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

void BddGalleryPhoto::updateIsFavorite(bool fav, QString nameImg) const {
    QSqlQuery upQuery;
    upQuery.prepare("UPDATE image SET isFavorite = :fav WHERE name = :nameImg");
    upQuery.bindValue(":nameImg", nameImg);
    upQuery.bindValue(":fav", fav);
    if (!upQuery.exec()){
        qDebug() << "update Favoris fail";
    }
}


