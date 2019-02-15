#include "accueilwindow.h"

AccueilWindow::AccueilWindow(const BddGalleryPhoto* pbdd, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    QPixmap imgStar(imageStar);
    imgStar = imgStar.scaled(40,40);
    etoile->setPixmap(imgStar);

    favoris = new ImagesShowcase(bdd->getAllImagesByFav());

    layoutImageFavoris->addWidget(favoris);

    colorPicker = new ColorPicker();

    buttonColorPicker = new ColorButton(colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, colorPicker->buttonjaune->imageHighlightedName, colorPicker->buttonjaune->imageName, 40, 40, this);
    colorPicker->buttonjaune->setSelected(true);
    colorPicker->setToolTip("Changer de couleur");
    layoutColor->addWidget(buttonColorPicker);
    colorPicker->currentColor = colorPicker->buttonjaune;

    initColors();
    dominantColor = new ImagesShowcase(bdd->getAllImagesByColor(colors.value(colorPicker->currentColor)));
    layoutImageColor->addWidget(dominantColor);

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
    dominantColor->newBDDRequest(bdd->getAllImagesByColor(colors.value(colorPicker->currentColor)));
}

void AccueilWindow::initShowCase(){
    favoris->newBDDRequest(bdd->getAllImagesByFav());
    dominantColor->newBDDRequest(bdd->getAllImagesByColor(colors.value(colorPicker->currentColor)));
}

void AccueilWindow::initColors()
{
    colors.insert(colorPicker->buttonbleu, "BLEU");
    colors.insert(colorPicker->buttonbleuClair1, "BLEU_CLAIR_1");
    colors.insert(colorPicker->buttonbleuClair2, "BLEU_CLAIR_2");
    colors.insert(colorPicker->buttonbleuClair3, "BLEU_CLAIR_3");
    colors.insert(colorPicker->buttonbleuGris, "BLEU_GRIS");
    colors.insert(colorPicker->buttongris, "GRIS");
    colors.insert(colorPicker->buttonjaune, "JAUNE");
    colors.insert(colorPicker->buttonjauneFonce, "JAUNE_FONCE");
    colors.insert(colorPicker->buttonmagenta, "MAGENTA");
    colors.insert(colorPicker->buttonmarron, "MARRON");
    colors.insert(colorPicker->buttonnoir, "NOIR");
    colors.insert(colorPicker->buttonorange, "ORANGE");
    colors.insert(colorPicker->buttonorangeClair, "ORANGE_CLAIR");
    colors.insert(colorPicker->buttonrose, "ROSE");
    colors.insert(colorPicker->buttonrouge, "ROUGE");
    colors.insert(colorPicker->buttonvert, "VERT");
    colors.insert(colorPicker->buttonvertClair, "VERT_CLAIR");
    colors.insert(colorPicker->buttonvertFonce, "VERT_FONCE");
    colors.insert(colorPicker->buttonvertJaune, "VERT_JAUNE");
    colors.insert(colorPicker->buttonviolet, "VIOLET");
}

ImagesShowcase *AccueilWindow::getFavoris() const
{
    return favoris;
}

void AccueilWindow::setFavoris(ImagesShowcase *value)
{
    favoris = value;
}

ImagesShowcase *AccueilWindow::getDominantColor() const
{
    return dominantColor;
}

void AccueilWindow::setDominantColor(ImagesShowcase *value)
{
    dominantColor = value;
}
