#include "imagewindow.h"

ImageWindow::ImageWindow(const BddGalleryPhoto* pbdd, QVector<Image*> imagesTab, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    bdd = pbdd;

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

    buttonColorPicker = new ColorButton(colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, 80, 80, this);
    colorPicker->buttonjaune->setSelected(true);
    layoutBoutonColor->addWidget(buttonColorPicker);

    grid = listPhoto;

    newBDDRequest(imagesTab);

    connect(boutonAdd, SIGNAL(clicked()),this, SLOT(searchImage()));
    connect(buttonColorPicker, SIGNAL(clicked()), this, SLOT(openColorPicker()));
    connect(colorPicker, SIGNAL(aboutToChoose()), this, SLOT(newColor()));
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
}

ImageWindow::~ImageWindow(){
    smartDeleteMrNovelli(grid);
}

void ImageWindow::newBDDRequest(QVector<Image *> imagesTab)
{
    if(grid->count() > 0){
        removeCell(grid,-1,-1);
    }
    int k = 0;
    if(!imagesTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(imagesTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < imagesTab.size()){
                    QLabel * label = new QLabel();
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
}

void ImageWindow::searchImage()
{
    const QStringList paths = QFileDialog::getOpenFileNames(this);
    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            const QStringList names = paths[i].split("/");
            Image newImage(names.last(), paths[i], QStringList(), QDate::currentDate(), QColor(255,0,0), "drôle");
            bdd->insertImage(newImage);
        }


    }
    newBDDRequest(bdd->getAllImages());
        //openImage(fileName);
}

/*void ImageWindow::openImage(const QString &fileName)
{

    QFile file(fileName);

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}*/
