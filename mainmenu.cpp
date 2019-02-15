#include "mainmenu.h"

MainMenu::MainMenu(QFrame* container, QVBoxLayout* layoutHome, QVBoxLayout* layoutAlbum, QVBoxLayout* layoutImage, QVBoxLayout* layoutHelp)
        : container(container), layoutHome(layoutHome), layoutAlbum(layoutAlbum), layoutImage(layoutImage), layoutHelp(layoutHelp)
{
    container->setMinimumWidth(MINWIDTH);
    container->setMaximumWidth(MINWIDTH);
    buttonHome = new ImageButton(imageButtonHomePressed, imageButtonHomeReleased, 50, 50, this);
    buttonHome->setToolTip("Retour à l'accueil");
    layoutHome->addWidget(buttonHome);
    buttonAlbum = new ImageButton(imageButtonAlbumPressed, imageButtonAlbumReleased, 50, 50, this);
    buttonAlbum->setToolTip("Afficher la liste d'album");
    layoutAlbum->addWidget(buttonAlbum);
    buttonImage = new ImageButton(imageButtonImagePressed, imageButtonImageReleased, 50, 50, this);
    buttonImage->setToolTip("Afficher la liste d'image");
    layoutImage->addWidget(buttonImage);
    buttonHelp = new ImageButton(imageButtonHelpPressed, imageButtonHelpReleased, 50, 50, this);
    buttonHelp->setToolTip("Bonne chance !");
    layoutHelp->addWidget(buttonHelp);
    buttonHomeLarge = new ImageButton(imageLargeButtonHomePressed, imageLargeButtonHomeReleased, 150, 50, this);
    buttonHomeLarge->setToolTip("Retour à l'accueil");
    layoutHome->addWidget(buttonHomeLarge);
    buttonHomeLarge->setHidden(true);
    buttonAlbumLarge = new ImageButton(imageLargeButtonAlbumPressed, imageLargeButtonAlbumReleased, 150, 50, this);
    buttonAlbumLarge->setToolTip("Afficher la liste d'album");
    layoutAlbum->addWidget(buttonAlbumLarge);
    buttonAlbumLarge->setHidden(true);
    buttonImageLarge = new ImageButton(imageLargeButtonImagePressed, imageLargeButtonImageReleased, 150, 50, this);
    buttonImageLarge->setToolTip("Afficher la liste d'image");
    layoutImage->addWidget(buttonImageLarge);
    buttonImageLarge->setHidden(true);
    buttonHelpLarge = new ImageButton(imageLargeButtonHelpPressed, imageLargeButtonHelpReleased, 150, 50, this);
    buttonHelpLarge->setToolTip("Bonne chance !");
    layoutHelp->addWidget(buttonHelpLarge);
    buttonHelpLarge->setHidden(true);
}

MainMenu::~MainMenu(){
    smartDeleteMrNovelli(buttonHome);
    smartDeleteMrNovelli(buttonAlbum);
    smartDeleteMrNovelli(buttonImage);
    smartDeleteMrNovelli(buttonHelp);
    smartDeleteMrNovelli(buttonHomeLarge);
    smartDeleteMrNovelli(buttonAlbumLarge);
    smartDeleteMrNovelli(buttonImageLarge);
    smartDeleteMrNovelli(buttonHelpLarge);
}

void MainMenu::openMenu(){
    if(!open){
        container->setMinimumWidth(MAXWIDTH);
        container->setMaximumWidth(MAXWIDTH);
        changeButtons();
        open = !open;
    } else {
        container->setMinimumWidth(MINWIDTH);
        container->setMaximumWidth(MINWIDTH);
        changeButtons();
        open = !open;
    }
}

void MainMenu::changeButtons(){
    if(!open){
        buttonHomeLarge->setHidden(false);
        buttonAlbumLarge->setHidden(false);
        buttonImageLarge->setHidden(false);
        buttonHelpLarge->setHidden(false);

        buttonHome->setHidden(true);
        buttonAlbum->setHidden(true);
        buttonImage->setHidden(true);
        buttonHelp->setHidden(true);
    } else {
        buttonHomeLarge->setHidden(true);
        buttonAlbumLarge->setHidden(true);
        buttonImageLarge->setHidden(true);
        buttonHelpLarge->setHidden(true);

        buttonHome->setHidden(false);
        buttonAlbum->setHidden(false);
        buttonImage->setHidden(false);
        buttonHelp->setHidden(false);
    }
}

//--Getters Setters-----------------------------------------------------------------------------
ImageButton* MainMenu::getButtonHome(){
    return buttonHome;
}

ImageButton* MainMenu::getButtonAlbum(){
    return buttonAlbum;
}

ImageButton* MainMenu::getButtonImage(){
    return buttonImage;
}

ImageButton* MainMenu::getButtonHelp(){
    return buttonHelp;
}

ImageButton* MainMenu::getButtonHomeLarge(){
    return buttonHomeLarge;
}

ImageButton* MainMenu::getButtonAlbumLarge(){
    return buttonAlbumLarge;
}

ImageButton* MainMenu::getButtonImageLarge(){
    return buttonImageLarge;
}

ImageButton* MainMenu::getButtonHelpLarge(){
    return buttonHelpLarge;
}
//----------------------------------------------------------------------------------------------
