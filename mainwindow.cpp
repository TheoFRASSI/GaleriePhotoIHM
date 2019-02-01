#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    mainmenu = new MainMenu(frameMainMenu, layoutButtonHome, layoutAlbumButton, layoutImageButton, layoutHelpButton);
    accueilW = new AccueilWindow();
    albumW = new AlbumWindow();
    imageW = new ImageWindow();
    helpW = new HelpWindow();
    stackWidget->addWidget(accueilW);
    stackWidget->addWidget(albumW);
    stackWidget->addWidget(imageW);
    stackWidget->addWidget(helpW);
    stackWidget->setCurrentWidget(accueilW);
    initMap();

    connect(mainmenu->getButtonHome(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonAlbum(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonImage(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonHelp(),SIGNAL(clicked()),this,SLOT(changeWid()));

    connect(mainmenu->getButtonHomeLarge(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonAlbumLarge(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonImageLarge(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(mainmenu->getButtonHelpLarge(),SIGNAL(clicked()),this,SLOT(changeWid()));
    //connect(/*A INSERER*/->getButtonModifImage(),SIGNAL(clicked()),this,SLOT(changeWid()));
    //connect(headermenu->getButtonSettings(),SIGNAL(clicked()),this,SLOT(changeWid()));



    //--SAAAAAAALE--------------------------------------------------------------------------------------------
    QString imageReleased = ":/img/button/menu";
    QString imagePressed = ":/img/button/menuHighlighted";
    ImageButton* img = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    menu->addWidget(img);
    ImageButton* img2 = new ImageButton(":/img/button/loupePressed",":/img/button/loupe", 40, 40, this);
    layoutSearch->addWidget(img2);
    ImageButton* img3 = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    layoutNewAlbum->addWidget(img3);
    ImageButton* img4 = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    layoutNewPhoto->addWidget(img4);
    ImageButton* img5 = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    layoutAffichage->addWidget(img5);
    ImageButton* img6 = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    layoutSettings->addWidget(img6);
    layoutSearch->addSpacerItem(horizontalSpacer);

    connect(img,SIGNAL(clicked()),mainmenu,SLOT(openMenu()));

}

void MainWindow::changeWid(){
    stackWidget->setCurrentWidget(assoTab.value(sender()));
}

void MainWindow::initMap(){
    assoTab.insert(mainmenu->getButtonHome(), accueilW);
    assoTab.insert(mainmenu->getButtonAlbum(), albumW);
    assoTab.insert(mainmenu->getButtonImage(), imageW);
    assoTab.insert(mainmenu->getButtonHelp(), helpW);
    assoTab.insert(mainmenu->getButtonHomeLarge(), accueilW);
    assoTab.insert(mainmenu->getButtonAlbumLarge(), albumW);
    assoTab.insert(mainmenu->getButtonImageLarge(), imageW);
    assoTab.insert(mainmenu->getButtonHelpLarge(), helpW);

}
