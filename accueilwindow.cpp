#include "accueilwindow.h"

AccueilWindow::AccueilWindow(const BddGalleryPhoto* pbdd, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    QPixmap imgStar(imageStar);
    imgStar = imgStar.scaled(40,40);
    etoile->setPixmap(imgStar);

    QPixmap imgEye(imageEye);
    imgEye = imgEye.scaled(40,40);
    oeil->setPixmap(imgEye);

    favoris = new ImagesShowcase(bdd->getAllImages());
    layoutImageFavoris->addWidget(favoris);

    mostWatched = new ImagesShowcase(bdd->getAllImages());
    layoutImageWatched->addWidget(mostWatched);

    dominantColor = new ImagesShowcase(bdd->getAllImages());
    layoutImageColor->addWidget(dominantColor);

    colorPicker = new ColorPicker();

    buttonColorPicker = new ColorButton(colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, 40, 40, this);
    colorPicker->buttonjaune->setSelected(true);
    layoutColor->addWidget(buttonColorPicker);

    buttonMail = new ImageButton(mailHighlighted, mail, 40, 40, this);
    layoutMail->addWidget(buttonMail);

    buttonFacebook = new ImageButton(facebookHighlighted, facebook, 40, 40, this);
    layoutFacebook->addWidget(buttonFacebook);

    buttonTwitter = new ImageButton(twitterHighlighted, twitter, 40, 40, this);
    layoutTwitter->addWidget(buttonTwitter);

    connect(buttonColorPicker, SIGNAL(clicked()), this, SLOT(openColorPicker()));
    connect(colorPicker, SIGNAL(aboutToChoose()), this, SLOT(newColor()));

}

AccueilWindow::~AccueilWindow(){
    delete colorPicker;
    colorPicker = nullptr;
    delete favoris;
    favoris = nullptr;
    delete mostWatched;
    mostWatched = nullptr;
    delete dominantColor;
    dominantColor = nullptr;
    delete buttonColorPicker;
    buttonColorPicker = nullptr;
}

void AccueilWindow::openColorPicker(){
    colorPicker->show();
}

void AccueilWindow::newColor(){
    currentColor = colorPicker->currentColor;
    buttonColorPicker->loadImage(currentColor->imageName);
    buttonColorPicker->loadImageHighlighted(currentColor->imageHighlightedName);
    buttonColorPicker->loadImageSelected(currentColor->imageName);
    buttonColorPicker->loadImageSelectedHighlighted(currentColor->imageHighlightedName);
    colorPicker->close();
}
