#include "imagesshowcase.h"

ImagesShowcase::ImagesShowcase(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    leftButton = new ImageButton(imageLeftButtonHighlighted, imageLeftButton, 50,50, this);
    rightButton = new ImageButton(imageRightButtonHighlighted, imageRightButton, 50,50, this);

    layoutLeft->addWidget(leftButton);
    layoutRight->addWidget(rightButton);
}

ImagesShowcase::~ImagesShowcase(){
    delete leftButton;
    leftButton = nullptr;
    delete rightButton;
    rightButton = nullptr;
}
