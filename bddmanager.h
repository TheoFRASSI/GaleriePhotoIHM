#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

#include "smartdelete.h"

class BddManager
{
public:
    BddManager(const QString& path);
    ~BddManager();
    bool createTable();
    bool isOpen() const;
    bool addImage(const QString &name, const QString &path);
    QString searchImageByName(const QString &name);


    // A REVOIR //
    void printAllPersons() const;
    bool personExists(const QString &name) const;
    bool removePerson(const QString &name);
    bool addPerson(const QString &name);
    bool removeAllPersons();
    // -------------- //

private:
    QSqlDatabase bdd;


};
