#include "imagesshowcase.h"

void ImagesShowcase::fillShowCase(){
    int j = cursor;
    for(int i = 0; i < nbLabel; i++){
        if(j < imageTab.size()){
            labelsImage[i]->setPixmap(pixmapTab[j]);
        } else {
            labelsImage[i]->setPixmap(imageVide);
        }
        j++;
    }

}

ImagesShowcase::ImagesShowcase(QVector<Image*> imagesTab, QWidget *parent)
               :QWidget(parent), imageTab(imagesTab)
{
    setupUi(this);

    leftButton = new ImageButton(imageLeftButtonHighlighted, imageLeftButton, 50,50, this);
    rightButton = new ImageButton(imageRightButtonHighlighted, imageRightButton, 50,50, this);

    leftButton->setDisabled(false);
    rightButton->setDisabled(false);

    layoutLeft->addWidget(leftButton);
    layoutRight->addWidget(rightButton);

    for(int i = 0; i < nbLabel; i++){
        QLabel* label = new QLabel();
        label->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        label->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        gridImages->addWidget(label, 0, i);
        labelsImage.push_back(label);
    }

    imageVide = QPixmap(pathImageVide);
    imageVide = imageVide.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);

    aucuneImage = QPixmap(pathAucuneImage);
    aucuneImage = aucuneImage.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);

    imageCorrupt = QPixmap(pathImageCorrupt);
    imageCorrupt = imageCorrupt.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);

    if(imagesTab.isEmpty()){
        labelsImage[static_cast<int>(nbLabel/2)]->setPixmap(aucuneImage);
        leftButton->setDisabled(true);
        rightButton->setDisabled(true);
    } else {
        for(int i = 0; i < imagesTab.size(); i++){
            QPixmap pix = QPixmap();
            bool validate = pix.load(imagesTab[i]->getPath());
            if(validate){
                pix = pix.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);
                pixmapTab.push_back(pix);
            } else {
                qDebug() << "Erreur : Lors du chargement de l'image >" << imagesTab[i]->getPath() << "| Dans la fonction" << __FUNCTION__;
                pixmapTab.push_back(QPixmap(imageCorrupt));
            }
        }
        fillShowCase();
        leftButton->setDisabled(true);
        if(cursor + nbLabel >= imageTab.size() - 1){
            rightButton->setDisabled(true);
        } else {
            rightButton->setDisabled(false);
        }
    }

    connect(rightButton, SIGNAL(clicked()), this, SLOT(changeImageRight()));
    connect(leftButton, SIGNAL(clicked()), this, SLOT(changeImageLeft()));
}

ImagesShowcase::~ImagesShowcase(){
    smartDeleteMrNovelli(leftButton);
    smartDeleteMrNovelli(rightButton);
}

void ImagesShowcase::changeImageRight()
{

    if(cursor + nbLabel <= imageTab.size() - 1){
        cursor += nbLabel;
        fillShowCase();
        leftButton->setDisabled(false);
        if(cursor + nbLabel > imageTab.size() - 1){
            rightButton->setDisabled(true);
        }
    }
    qDebug() << "Cursor :" << cursor << "Nb Images :" << imageTab.size();
}

void ImagesShowcase::changeImageLeft()
{
    if(cursor - nbLabel >= 0){
        cursor -= nbLabel;
        fillShowCase();
        rightButton->setDisabled(false);
        if(cursor - nbLabel < 0){
            leftButton->setDisabled(true);
        }
    }
    qDebug() << "Cursor :" << cursor << "Nb Images :" << imageTab.size();
}

void ImagesShowcase::newBDDRequest(QVector<Image*> imagesTab){
    imageTab = imagesTab;
    cursor = 0;
    if(imagesTab.isEmpty()){
        labelsImage[static_cast<int>(nbLabel/2)]->setPixmap(aucuneImage);
        leftButton->setDisabled(true);
        rightButton->setDisabled(true);
    } else {
        QVector<QPixmap> pixmapTemp;
        for(int i = 0; i < imagesTab.size(); i++){
            QPixmap pix = QPixmap();
            bool validate = pix.load(imagesTab[i]->getPath());
            if(validate){
                pix = pix.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);
                pixmapTemp.push_back(pix);
            } else {
                qDebug() << "Erreur : Lors du chargement de l'image >" << imagesTab[i]->getPath() << "| Dans la fonction" << __FUNCTION__;
                pixmapTemp.push_back(QPixmap(imageCorrupt));
            }
        }
        pixmapTab = pixmapTemp;
        fillShowCase();
        leftButton->setDisabled(true);
        if(cursor + nbLabel > imageTab.size() - 1){
            rightButton->setDisabled(true);
        } else {
            rightButton->setDisabled(false);
        }
    }
}
