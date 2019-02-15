#pragma once

#include <QVector>
#include "image.h"
#include "smartdelete.h"

class Album
{
public:
    //--Constructeur Destructeur------------------------------
    Album();
    Album(QString name);
    Album(QString name, QString cover);
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    QString getCover() const;    
    QString getName() const;

    void setCover(QString cover);
    //---------------------------------------------------------
private:
    //--Attributs----------------------------------------------
    QString name;
    QString cover;
    //---------------------------------------------------------


    /*
    unsigned int nbImages = 1;
    QDate date;
    bool isFavorite;*/
};
