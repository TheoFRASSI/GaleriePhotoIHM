#include "imagewindow.h"

ImageWindow::ImageWindow(QVector<Image*> imagesTab, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    imageVide = QPixmap(pathImageVide);

    aucuneImage = QPixmap(pathAucuneImage);

    grid = listPhoto;

    newBDDRequest(imagesTab);
}

ImageWindow::~ImageWindow(){
    smartDeleteMrNovelli(grid);
}

void ImageWindow::newBDDRequest(QVector<Image *> imagesTab)
{
    if(grid->count() > 0){
        removeCell(grid,-1,-1);
    }
    int k = 0;
    if(!imagesTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(imagesTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < imagesTab.size()){
                    QLabel * label = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    QPixmap pix = QPixmap();
                    bool validate = pix.load(imagesTab[k]->getPath());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        label->setPixmap(pix);
                        grid->addWidget(label, i, j);
                    } else {
                        qDebug() << "Erreur : Lors du chargement de l'image >" << imagesTab[k]->getPath() << "| Dans la fonction" << __FUNCTION__;
                    }
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap(aucuneImage));
        grid->addWidget(label, 0, 0);
    }
}
