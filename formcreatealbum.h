#ifndef FORMCREATEALBUM_H
#define FORMCREATEALBUM_H

#include <QDialog>
#include <QFileDialog>
#include <QDate>
#include "image.h"
#include "album.h"
#include "bddgalleryphoto.h"

namespace Ui {
class FormCreateAlbum;
}

class FormCreateAlbum : public QDialog
{
    Q_OBJECT

public:
    explicit FormCreateAlbum(const BddGalleryPhoto * bdd, QWidget *parent = nullptr);
    ~FormCreateAlbum();

    const BddGalleryPhoto * bdd;


private:
    Ui::FormCreateAlbum *ui;

    QString selectedName;
    QVector<Image> selectedImages;
    Image selectedCover;

public slots:
    void selectImages();
    void selectCover();
    void validateChoices();
};

#endif // FORMCREATEALBUM_H
