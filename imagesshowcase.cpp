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
               :QWidget(parent)
{
    setupUi(this);
    imageTab.clear();
    for(int i = 0; i < 15 && i < imagesTab.size(); i++) {
        imageTab.push_back(imagesTab[i]);
    }

    leftButton = new ImageButton(imageLeftButtonHighlighted, imageLeftButton, 50,50, this);
    leftButton->setToolTip("Précédent");
    rightButton = new ImageButton(imageRightButtonHighlighted, imageRightButton, 50,50, this);
    rightButton->setToolTip("Suivant");

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

    if(imageTab.isEmpty()){
        labelsImage[static_cast<int>(nbLabel/2)]->setPixmap(aucuneImage);
        leftButton->setDisabled(true);
        rightButton->setDisabled(true);
    } else {
        for(int i = 0; i < imageTab.size(); i++){
            QPixmap pix;
            bool validate = pix.load(imageTab[i]->getPath());
            if(validate){
                pix = pix.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);
                pixmapTab.push_back(pix);
            } else {
                qDebug() << "Erreur : Lors du chargement de l'image >" << imageTab[i]->getPath() << "| Dans la fonction" << __FUNCTION__;
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
    for(int i = 0; i < imageTab.size(); i++) {
        smartDeleteMrNovelli(imageTab[i]);
    }
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
}

void ImagesShowcase::newBDDRequest(QVector<Image*> imagesTab){

    imageTab.clear();
    for(int i = 0; i < 15 && i < imagesTab.size(); i++) {
        imageTab.push_back(imagesTab[i]);
    }
    cursor = 0;
    if(imageTab.isEmpty()){
        for(int i = 0; i< nbLabel; i++){
            if(i == static_cast<int>(nbLabel/2)){
                labelsImage[static_cast<int>(nbLabel/2)]->setPixmap(aucuneImage);
            } else {
                labelsImage[i]->setPixmap(QPixmap());
            }
        }
        leftButton->setDisabled(true);
        rightButton->setDisabled(true);
    } else {
        QVector<QPixmap> pixmapTemp;
        for(int i = 0; i < imageTab.size(); i++){
            QPixmap pix;
            bool validate = pix.load(imageTab[i]->getPath());
            if(validate){
                pix = pix.scaled(LABEL_SIZE,LABEL_SIZE,Qt::KeepAspectRatio);
                pixmapTemp.push_back(pix);
            } else {
                qDebug() << "Erreur : Lors du chargement de l'image >" << imageTab[i]->getPath() << "| Dans la fonction" << __FUNCTION__;
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
