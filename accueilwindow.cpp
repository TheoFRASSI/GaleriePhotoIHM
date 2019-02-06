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

    favoris = new ImagesShowcase(bdd->getAllImages("path", "wesh"));
    mostWatched = new ImagesShowcase(bdd->getAllImages("path"));
    dominantColor = new ImagesShowcase(bdd->getAllImages());

    layoutImageFavoris->addWidget(favoris);
    layoutImageColor->addWidget(dominantColor);
    layoutImageWatched->addWidget(mostWatched);

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
    smartDeleteMrNovelli(colorPicker);
    smartDeleteMrNovelli(favoris);
    smartDeleteMrNovelli(mostWatched);
    smartDeleteMrNovelli(dominantColor);
    smartDeleteMrNovelli(buttonColorPicker);
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

void AccueilWindow::initShowCase(){
    favoris->newBDDRequest(bdd->getAllImages("path", "wesh"));
    mostWatched->newBDDRequest(bdd->getAllImages("path"));
    dominantColor->newBDDRequest(bdd->getAllImages());
}

ImagesShowcase *AccueilWindow::getFavoris() const
{
    return favoris;
}

void AccueilWindow::setFavoris(ImagesShowcase *value)
{
    favoris = value;
}

ImagesShowcase *AccueilWindow::getMostWatched() const
{
    return mostWatched;
}

void AccueilWindow::setMostWatched(ImagesShowcase *value)
{
    mostWatched = value;
}

ImagesShowcase *AccueilWindow::getDominantColor() const
{
    return dominantColor;
}

void AccueilWindow::setDominantColor(ImagesShowcase *value)
{
    dominantColor = value;
}
