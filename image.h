#pragma once

#include <QString>

class Image
{
public:
    Image();
    Image(QString name, QString path);
    QString getName();
    QString getPath();

private:
    QString name;
    QString path;
};
