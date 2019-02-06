#include "imagewindow.h"

ImageWindow::ImageWindow(QVector<Image*> imagesTab, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    imageVide = QPixmap(pathImageVide);
    aucuneImage = QPixmap(pathAucuneImage);

    newBDDRequest(imagesTab);
}

ImageWindow::~ImageWindow(){

}

void ImageWindow::newBDDRequest(QVector<Image *> imagesTab)
{
    //listPhoto = new QGridLayout();
    int k = 0;
    if(!imagesTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(imagesTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < imagesTab.size()){
                    QLabel * label = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setScaledContents(true);
                    label->setPixmap(QPixmap(imagesTab[k]->getPath()));
                    listPhoto->addWidget(label, i, j);
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap(aucuneImage));
        listPhoto->addWidget(label, 0, 0);
    }
}
