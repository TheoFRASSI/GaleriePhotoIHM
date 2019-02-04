#ifndef IMAGESSHOWCASE_H
#define IMAGESSHOWCASE_H

#include "ui_imagesshowcase.h"

class ImagesShowcase : public QWidget, private Ui::ImagesShowcase
{
    Q_OBJECT

public:
    explicit ImagesShowcase(QWidget *parent = nullptr);
};

#endif // IMAGESSHOWCASE_H
