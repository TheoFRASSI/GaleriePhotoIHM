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
    settingsW = new SettingsWindow();

    stackWidget->addWidget(accueilW);
    stackWidget->addWidget(albumW);
    stackWidget->addWidget(imageW);
    stackWidget->addWidget(helpW);
    stackWidget->addWidget(settingsW);
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


    headermenu = new HeaderMenu(headerMenuFrame, menu, layoutSearch, layoutNewAlbum, layoutNewPhoto, layoutAffichage, layoutSettings, horizontalSpacer);

    connect(headermenu->getButtonSettings(),SIGNAL(clicked()),this,SLOT(changeWid()));
    connect(headermenu->getButtonMenu(),SIGNAL(clicked()),mainmenu,SLOT(openMenu()));


    //--SAAAAAAALE--------------------------------------------------------------------------------------------

    //connect(/*A INSERER*/->getButtonModifImage(),SIGNAL(clicked()),this,SLOT(changeWid()));

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

    assoTab.insert(headermenu->getButtonSettings(), settingsW);

}
