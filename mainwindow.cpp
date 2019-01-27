#include "mainwindow.h"
#include "imagebutton.h"
#include "mainmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    MainMenu* mainmenu = new MainMenu(frameMainMenu, layoutButtonHome, layoutAlbumButton, layoutImageButton, layoutHelpButton);
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
