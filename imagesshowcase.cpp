#include "imagesshowcase.h"

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

ImagesShowcase::ImagesShowcase(QVector<Image*> imagesTab, QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    leftButton = new ImageButton(imageLeftButtonHighlighted, imageLeftButton, 50,50, this);
    rightButton = new ImageButton(imageRightButtonHighlighted, imageRightButton, 50,50, this);

    layoutLeft->addWidget(leftButton);
    layoutRight->addWidget(rightButton);

    if(!imagesTab.isEmpty()){
        img1->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
        img2->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
        img3->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
        img4->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
        img5->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
        img6->setPixmap(QPixmap(imagesTab[random(0,imagesTab.size()-1)]->getPath()));
    }

}

ImagesShowcase::~ImagesShowcase(){
    delete leftButton;
    leftButton = nullptr;
    delete rightButton;
    rightButton = nullptr;
}
