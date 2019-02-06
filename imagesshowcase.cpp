#include "imagesshowcase.h"

//int random(int min, int max) //range : [min, max)
//{
//   static bool first = true;
//   if (first)
//   {
//      srand( time(NULL) ); //seeding for the first time only!
//      first = false;
//   }
//   return min + rand() % (( max + 1 ) - min);
//}

void ImagesShowcase::fillShowCase(){
    for(int i = cursor; i < nbLabel; i++){
        if(i <= imageTab.size() - 1){
            labelsImage[i]->setPixmap(QPixmap(imageTab[i]->getPath()));
        }
    }

}

ImagesShowcase::ImagesShowcase(QVector<Image*> imagesTab, QWidget *parent)
               :QWidget(parent), imageTab(imagesTab)
{
    setupUi(this);

    leftButton = new ImageButton(imageLeftButtonHighlighted, imageLeftButton, 50,50, this);
    rightButton = new ImageButton(imageRightButtonHighlighted, imageRightButton, 50,50, this);

    layoutLeft->addWidget(leftButton);
    layoutRight->addWidget(rightButton);

    for(int i = 0; i < nbLabel; i++){
        QLabel* label = new QLabel();
        label->setMaximumSize(LABEL_SIZE,LABEL_SIZE);
        label->setMinimumSize(LABEL_SIZE,LABEL_SIZE);
        label->setScaledContents(true);
        gridImages->addWidget(label, 0, i);
        labelsImage.push_back(label);
    }

    if(imagesTab.isEmpty()){
        //Image Speciale
    } else {
        fillShowCase();
    }
}

ImagesShowcase::~ImagesShowcase(){
    delete leftButton;
    leftButton = nullptr;
    delete rightButton;
    rightButton = nullptr;
}

void ImagesShowcase::changeImageRight()
{
    if(cursor + nbLabel < imageTab.size() - 1){
        cursor += nbLabel;
        fillShowCase();
        if(cursor + nbLabel > imageTab.size() - 1){

        }
    }

}

void ImagesShowcase::changeImageLeft()
{

}
