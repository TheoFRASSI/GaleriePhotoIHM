#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    QDir dir;
    QString path = dir.currentPath()+"GalleryPhotoBDD.db";
    bdd = new BddGalleryPhoto(path);

    mainmenu = new MainMenu(frameMainMenu, layoutButtonHome, layoutAlbumButton, layoutImageButton, layoutHelpButton);
    progressBar->setVisible(false);
    headermenu = new HeaderMenu(headerMenuFrame, menu, layoutSearch, layoutNewAlbum, layoutNewPhoto, layoutAffichage, layoutSettings, horizontalSpacer, labelTitre, lineEdit, progressBar);

    accueilW = new AccueilWindow(bdd);
    albumW = new AlbumWindow(bdd);
    imageW = new ImageWindow(bdd, progressBar);
    helpW = new HelpWindow();
    settingsW = new SettingsWindow(bdd);

    stackWidget->addWidget(accueilW);
    stackWidget->addWidget(albumW);
    stackWidget->addWidget(imageW);
    stackWidget->addWidget(helpW);
    stackWidget->addWidget(settingsW);
    stackWidget->setCurrentWidget(accueilW);

    initMap();

    connect(mainmenu->getButtonHome(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonAlbum(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonImage(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonHelp(),SIGNAL(clicked()),this,SLOT(changeWidget()));

    connect(mainmenu->getButtonHomeLarge(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonAlbumLarge(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonImageLarge(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(mainmenu->getButtonHelpLarge(),SIGNAL(clicked()),this,SLOT(changeWidget()));


    connect(headermenu->getButtonSettings(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(headermenu->getButtonSearch(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(headermenu->getButtonNewAlbum(),SIGNAL(clicked()),this,SLOT(changeWidget()));
    connect(headermenu->getButtonNewPhoto(),SIGNAL(clicked()),this,SLOT(changeWidget()));

    connect(headermenu->getButtonMenu(),SIGNAL(clicked()),mainmenu,SLOT(openMenu()));

    connect(headermenu->getButtonSearch(), SIGNAL(clicked()), this, SLOT(changeWidget()));
    connect(lineEdit, SIGNAL(returnPressed()), headermenu->getButtonSearch(), SIGNAL(clicked()));
    connect(albumW, SIGNAL(albumClicked(QString)), imageW, SLOT(showAlbum(QString)));
    connect(albumW, SIGNAL(albumAutoClicked(QString)), imageW, SLOT(showAlbumAuto(QString)));
    connect(albumW, SIGNAL(albumClicked(QString)), this, SLOT(openImageW()));
    connect(albumW, SIGNAL(albumAutoClicked(QString)), this, SLOT(openImageW()));

}

MainWindow::~MainWindow(){
    smartDeleteMrNovelli(mainmenu);
    smartDeleteMrNovelli(headermenu);
    smartDeleteMrNovelli(accueilW);
    smartDeleteMrNovelli(albumW);
    smartDeleteMrNovelli(imageW);
    smartDeleteMrNovelli(helpW);
    smartDeleteMrNovelli(settingsW);
    smartDeleteMrNovelli(modifimageW);
}

void MainWindow::changeWidget(){
    stackWidget->setCurrentWidget(assoTab.value(sender()));
    if(assoTab.value(sender()) == albumW) {
        headermenu->getLabelTitre()->setText("Albums");
    } else if(assoTab.value(sender()) == imageW) {
        headermenu->getLabelTitre()->setText("Photos");
        if(imageW->getModified() && lineEdit->text() != "") {
            imageW->newBDDRequest(bdd->getAllImages("name", lineEdit->text()));
        }
    } else if (assoTab.value(sender()) == accueilW) {
        headermenu->getLabelTitre()->setText("Accueil");
        accueilW->initShowCase();
    } else if (assoTab.value(sender()) == helpW) {
        headermenu->getLabelTitre()->setText("Aide");
    } else if (assoTab.value(sender()) == settingsW) {
        headermenu->getLabelTitre()->setText("Réglages");
    }

}

void MainWindow::openImageW(){
    stackWidget->setCurrentWidget(imageW);
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
    assoTab.insert(headermenu->getButtonNewAlbum(), albumW);
    assoTab.insert(headermenu->getButtonNewPhoto(), imageW);
    assoTab.insert(headermenu->getButtonSearch(), imageW);
}
