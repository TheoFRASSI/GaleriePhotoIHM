#include "mainwindow.h"
#include "imagebutton.h"
#include "mainmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    MainMenu* mainmenu = new MainMenu(layoutMainMenu);
    QString imageReleased = "img/menu.png";
    QString imagePressed = "img/menuHighlighted.png";
    ImageButton* img = new ImageButton(imagePressed, imageReleased, 50, 50, this);
    menu->addWidget(img);
    ImageButton* img2 = new ImageButton("C:/Users/theof/Pictures/ImageProjetQt/loupePressed.png","C:/Users/theof/Pictures/ImageProjetQt/loupe.png", 40, 40, this);
    layoutSearch->addWidget(img2);
    ImageButton* img3 = new ImageButton(imagePressed, imageReleased, 75, 75, this);
    layoutNewAlbum->addWidget(img3);
    ImageButton* img4 = new ImageButton(imagePressed, imageReleased, 75, 75, this);
    layoutNewPhoto->addWidget(img4);
    ImageButton* img5 = new ImageButton(imagePressed, imageReleased, 75, 75, this);
    layoutAffichage->addWidget(img5);
    ImageButton* img6 = new ImageButton(imagePressed, imageReleased, 75, 75, this);
    layoutSettings->addWidget(img6);
    layoutSearch->addSpacerItem(horizontalSpacer);

    connect(img,SIGNAL(clicked()),mainmenu,SLOT(openMenu()));
}
