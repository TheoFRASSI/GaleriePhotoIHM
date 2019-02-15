#include "imagewindow.h"

ImageWindow::ImageWindow(const BddGalleryPhoto* pbdd, QProgressBar * p_progressBar, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    bdd = pbdd;
    progressBar = p_progressBar;
    imageVide = QPixmap(pathImageVide);

    aucuneImage = QPixmap(pathAucuneImage);

    imageCorrupt = QPixmap(pathImageCorrupt);

    boutonAdd = new ImageButton(pathBoutonAddH, pathBoutonAdd, 200, 100, this);
    boutonLayout->addWidget(boutonAdd);

    boutonFav = new ImageButton(pathFavH, pathFav, 100, 100, this);
    boutonFeel = new ImageButton(pathFeelH, pathFeel, 100, 100, this);
    boutonDate = new ImageButton(pathDateH, pathDate, 100, 100, this);
    boutonAlpha = new ImageButton(pathAlphaH, pathAlpha, 100, 100, this);

    layoutBoutonFav->addWidget(boutonFav);
    layoutBoutonFeel->addWidget(boutonFeel);
    layoutBoutonDate->addWidget(boutonDate);
    layoutBoutonAlpha->addWidget(boutonAlpha);

    colorPicker = new ColorPicker();

    initColors();
    buttonColorPicker = new ColorButton(colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, 80, 80, this);
    colorPicker->buttonjaune->setSelected(true);
    layoutBoutonColor->addWidget(buttonColorPicker);

    grid = listPhoto;

    //newBDDRequest(imagesTab);

    connect(boutonAdd, SIGNAL(clicked()),this, SLOT(searchImage()));
    connect(buttonColorPicker, SIGNAL(clicked()), this, SLOT(openColorPicker()));
    connect(colorPicker, SIGNAL(aboutToChoose()), this, SLOT(newColor()));
    connect(boutonFav, SIGNAL(clicked()), this, SLOT(favRequest()));
    connect(boutonDate, SIGNAL(clicked()), this, SLOT(dateRequest()));
    connect(boutonAlpha, SIGNAL(clicked()), this, SLOT(alphaRequest()));
}

void ImageWindow::alphaRequest(){
    newBDDRequest(bdd->getAllImages());
}

void ImageWindow::dateRequest(){
    newBDDRequest(bdd->getAllImagesByDate());
}

void ImageWindow::favRequest(){
    newBDDRequest(bdd->getAllImagesByFav());
}

void ImageWindow::openColorPicker(){
    colorPicker->show();
}

void ImageWindow::newColor(){
    currentColor = colorPicker->currentColor;
    buttonColorPicker->loadImage(currentColor->imageName);
    buttonColorPicker->loadImageHighlighted(currentColor->imageHighlightedName);
    buttonColorPicker->loadImageSelected(currentColor->imageName);
    buttonColorPicker->loadImageSelectedHighlighted(currentColor->imageHighlightedName);
    colorPicker->close();
    newBDDRequest(bdd->getAllImagesByColor(colors.value(currentColor)));
}

ImageWindow::~ImageWindow(){
    smartDeleteMrNovelli(grid);
    smartDeleteMrNovelli(buttonColorPicker);
    smartDeleteMrNovelli(colorPicker);

    smartDeleteMrNovelli(boutonAdd);
    smartDeleteMrNovelli(boutonFav);
    smartDeleteMrNovelli(boutonFeel);
    smartDeleteMrNovelli(layoutBoutonDate);
    smartDeleteMrNovelli(layoutBoutonAlpha);
    smartDeleteMrNovelli(bdd);
}

void ImageWindow::newBDDRequest(QVector<Image *> imagesTab)
{
    if(grid->count() > 0){
        removeCell(grid,-1,-1);
    }
    int k = 0;
    if(!imagesTab.isEmpty()){
        progressBar->setVisible(true);
        progressBar->setRange(0,imagesTab.size()-1);
        progressBar->setFormat("%v images chargées sur %m (%p%)");
        int progressValue = 0;
        progressBar->setValue(progressValue);
        for(int i = 0; i < static_cast<int>(imagesTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < imagesTab.size()){
                    QLabel * label = new QLabel();
                    progressValue += 1;
                    progressBar->setValue(progressValue);
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    QPixmap pix = QPixmap();
                    bool validate = pix.load(imagesTab[k]->getPath());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        label->setPixmap(pix);
                        grid->addWidget(label, i, j);
                    } else {
                        QLabel * label = new QLabel();
                        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                        label->setScaledContents(true);
                        label->setPixmap(QPixmap(imageCorrupt));
                        grid->addWidget(label, i, j);
                        qDebug() << "Erreur : Lors du chargement de l'image >" << imagesTab[k]->getPath() << "| Dans la fonction" << __FUNCTION__;
                    }
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap(aucuneImage));
        grid->addWidget(label, 0, 0);
    }
    progressBar->setVisible(false);
}

void ImageWindow::initColors()
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

void ImageWindow::searchImage()
{
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    qsrand(static_cast<uint>(time(nullptr)));

    const QStringList paths = QFileDialog::getOpenFileNames(this);
    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            QString colorImg = colors[qrand() % colors.size()];
            const QStringList names = paths[i].split("/");
            Image newImage(names.last(), paths[i], QDate::currentDate(), colorImg, "Cool", 0);
            bdd->insertImage(newImage);
        }


    }
    newBDDRequest(bdd->getAllImages());
}
