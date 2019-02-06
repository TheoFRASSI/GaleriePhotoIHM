#include "imagewindow.h"

ImageWindow::ImageWindow(QVector<Image*> imagesTab, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    // ----------
    /*bdd = pbdd;
    photos = new ImagesShowcase(bdd->getAllImages());
    img01HorizLayout->addWidget(photos);*/
    // ----------
    /*if(!imagesTab.isEmpty()){
        img01Label->setPixmap(QPixmap(imagesTab[0]->getPath()));
    }*/

    if(!imagesTab.isEmpty()){
        //listPhoto->addWidget(new QLabel());
        for(int i = 0; i < imagesTab.size(); i++){
            /*vectorListPhoto->push_back(new QLabel());
            vectorListPhoto->last()->setPixmap(QPixmap(imagesTab[i]->getPath()));
            listPhoto->addWidget(vectorListPhoto->last());*/
            qDebug() << imagesTab.size();
            qDebug() << imagesTab[i]->getPath();

            QLabel * label = new QLabel();
            label->setMaximumSize(250, 250);
            label->setMinimumSize(250, 250);
            label->setScaledContents(true);
            label->setPixmap(QPixmap(imagesTab[i]->getPath()));
            listPhoto->addWidget(label, 0, i);
            vectorListPhoto.push_back(label);
        }
    }
}

ImageWindow::~ImageWindow(){
    delete photos;
    photos = nullptr;

    // --------
    for (QVector<QLabel*>::iterator i = vectorListPhoto.begin(); i != vectorListPhoto.end(); i++){
        delete (*i);
        (*i) = nullptr;
    }
    vectorListPhoto.clear();
    //delete vectorListPhoto;
    //vectorListPhoto = nullptr;
    // -------
}
