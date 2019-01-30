#include "mainmenu.h"

MainMenu::MainMenu(QFrame* container, QVBoxLayout* layoutHome, QVBoxLayout* layoutAlbum, QVBoxLayout* layoutImage, QVBoxLayout* layoutHelp)
        : container(container), layoutHome(layoutHome), layoutAlbum(layoutAlbum), layoutImage(layoutImage), layoutHelp(layoutHelp)
{
    this->container->setMinimumWidth(this->MINWIDTH);
    this->container->setMaximumWidth(this->MINWIDTH);
    this->buttonHome = new ImageButton(imageButtonHomePressed, imageButtonHomeReleased, 50, 50, this);
    this->layoutHome->addWidget(buttonHome);
    this->buttonAlbum = new ImageButton(imageButtonAlbumPressed, imageButtonAlbumReleased, 50, 50, this);
    this->layoutAlbum->addWidget(buttonAlbum);
    this->buttonImage = new ImageButton(imageButtonImagePressed, imageButtonImageReleased, 50, 50, this);
    this->layoutImage->addWidget(buttonImage);
    this->buttonHelp = new ImageButton(imageButtonHelpPressed, imageButtonHelpReleased, 50, 50, this);
    this->layoutHelp->addWidget(buttonHelp);
}

MainMenu::~MainMenu(){

}

void MainMenu::openMenu(){
    if(!this->open){
        this->container->setMinimumWidth(this->MAXWIDTH);
        this->container->setMaximumWidth(this->MAXWIDTH);
        changeButtons();
        this->open = !this->open;
    } else {
        this->container->setMinimumWidth(this->MINWIDTH);
        this->container->setMaximumWidth(this->MINWIDTH);
        changeButtons();
        this->open = !this->open;
    }
}

void MainMenu::changeButtons(){
    if(!this->open){
        this->buttonHome->loadImagePressed(this->imageLargeButtonHomePressed);
        this->buttonHome->loadImageReleased(this->imageLargeButtonHomeReleased);
        this->buttonHome->setImagePressed();
        this->buttonHome->setImageReleased();
        this->buttonHome->resizeButton(150,50);

        this->buttonAlbum->loadImagePressed(this->imageLargeButtonAlbumPressed);
        this->buttonAlbum->loadImageReleased(this->imageLargeButtonAlbumReleased);
        this->buttonAlbum->setImagePressed();
        this->buttonAlbum->setImageReleased();
        this->buttonAlbum->resizeButton(150,50);

        this->buttonImage->loadImagePressed(this->imageLargeButtonImagePressed);
        this->buttonImage->loadImageReleased(this->imageLargeButtonImageReleased);
        this->buttonImage->setImagePressed();
        this->buttonImage->setImageReleased();
        this->buttonImage->resizeButton(150,50);

        this->buttonHelp->loadImagePressed(this->imageLargeButtonHelpPressed);
        this->buttonHelp->loadImageReleased(this->imageLargeButtonHelpReleased);
        this->buttonHelp->setImagePressed();
        this->buttonHelp->setImageReleased();
        this->buttonHelp->resizeButton(150,50);

    } else {
        this->buttonHome->loadImagePressed(this->imageButtonHomePressed);
        this->buttonHome->loadImageReleased(this->imageButtonHomeReleased);
        this->buttonHome->setImagePressed();
        this->buttonHome->setImageReleased();
        this->buttonHome->resizeButton(50,50);

        this->buttonAlbum->loadImagePressed(this->imageButtonAlbumPressed);
        this->buttonAlbum->loadImageReleased(this->imageButtonAlbumReleased);
        this->buttonAlbum->setImagePressed();
        this->buttonAlbum->setImageReleased();
        this->buttonAlbum->resizeButton(50,50);

        this->buttonImage->loadImagePressed(this->imageButtonImagePressed);
        this->buttonImage->loadImageReleased(this->imageButtonImageReleased);
        this->buttonImage->setImagePressed();
        this->buttonImage->setImageReleased();
        this->buttonImage->resizeButton(50,50);

        this->buttonHelp->loadImagePressed(this->imageButtonHelpPressed);
        this->buttonHelp->loadImageReleased(this->imageButtonHelpReleased);
        this->buttonHelp->setImagePressed();
        this->buttonHelp->setImageReleased();
        this->buttonHelp->resizeButton(50,50);

    }
}

//--Getters Setters-----------------------------------------------------------------------------
ImageButton* MainMenu::getButtonHome(){
    return this->buttonHome;
}

ImageButton* MainMenu::getButtonAlbum(){
    return this->buttonAlbum;
}

ImageButton* MainMenu::getButtonImage(){
    return this->buttonImage;
}
//----------------------------------------------------------------------------------------------
