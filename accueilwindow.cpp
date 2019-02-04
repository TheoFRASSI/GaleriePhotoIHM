#include "accueilwindow.h"

AccueilWindow::AccueilWindow(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    QPixmap imgStar(imageStar);
    imgStar = imgStar.scaled(40,40);
    etoile->setPixmap(imgStar);

    QPixmap imgEye(imageEye);
    imgEye = imgEye.scaled(40,40);
    oeil->setPixmap(imgEye);

    favoris = new ImagesShowcase();
    layoutImageFavoris->addWidget(favoris);

    mostWatched = new ImagesShowcase();
    layoutImageWatched->addWidget(mostWatched);

    dominantColor = new ImagesShowcase();
    layoutImageColor->addWidget(dominantColor);

    colorPicker = new ColorPicker();

    buttonColorPicker = new ColorButton(colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, 40, 40, this);
    colorPicker->buttonjaune->setSelected(true);
    layoutColor->addWidget(buttonColorPicker);

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
