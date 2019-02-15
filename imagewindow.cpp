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

    initColors();
    buttonColorPicker = new ColorButton(colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, colorPicker->buttonvert->imageHighlightedName, colorPicker->buttonvert->imageName, 80, 80, this);
    colorPicker->buttonjaune->setSelected(true);
    layoutBoutonColor->addWidget(buttonColorPicker);

    grid = listPhoto;

    newBDDRequest(imagesTab);

    boutonFermer = new ImageButton(pathFermerH, pathFermer, 50, 50, this);
    layoutBoutonFermer->addWidget(boutonFermer);
    boutonEditName = new ImageButton(pathEditNameH, pathEditName, 50, 50, this);
    layoutEditName->addWidget(boutonEditName);
    boutonDeleteAlbum = new ImageButton(pathDeleteAlbumH, pathDeleteAlbum, 50, 50, this);
    layoutDeleteAlbum->addWidget(boutonDeleteAlbum);
    boutonAddImages = new ImageButton(pathAddImagesH, pathAddImages, 50, 50, this);
    layoutAddImage->addWidget(boutonAddImages);
    lineEditNameAlbum->hide();
    frameAfficheAlbum->hide();

    connect(boutonAdd, SIGNAL(clicked()),this, SLOT(searchImage()));
    connect(buttonColorPicker, SIGNAL(clicked()), this, SLOT(openColorPicker()));
    connect(colorPicker, SIGNAL(aboutToChoose()), this, SLOT(newColor()));
    connect(boutonFav, SIGNAL(clicked()), this, SLOT(favRequest()));
    connect(boutonDate, SIGNAL(clicked()), this, SLOT(dateRequest()));
    connect(boutonAlpha, SIGNAL(clicked()), this, SLOT(alphaRequest()));

    connect(boutonFermer, SIGNAL(clicked()), this, SLOT(closeAlbum()));
    connect(boutonEditName, SIGNAL(clicked()), this, SLOT(editName()));
    connect(boutonDeleteAlbum, SIGNAL(clicked()), this, SLOT(deleteAlbum()));
    connect(boutonAddImages, SIGNAL(clicked()), this, SLOT(addImages()));

    connect(lineEditNameAlbum, SIGNAL(returnPressed()), boutonEditName, SIGNAL(clicked()));
}

void ImageWindow::deleteAlbum(){
    if(bdd->deleteAlbumByName(labelNomAlbum->text())){
        qDebug() << "Album supprimé";
        frameAfficheAlbum->hide();
        alphaRequest();
    } else {
        qDebug() << "Echec de suppression d'album";
        alphaRequest();
    }
}

void ImageWindow::addImages(){
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    qsrand(static_cast<uint>(time(nullptr)));

    const QStringList paths = QFileDialog::getOpenFileNames(this);
    QVector<Image> v;
    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            QString colorImg = colors[qrand() % colors.size()];
            const QStringList names = paths[i].split("/");
            Image newImage(names.last(), paths[i], QDate::currentDate(), colorImg, "Cool", 0);
            v.push_back(newImage);
            bdd->insertImage(newImage);
        }

        if(bdd->assocImageWithAlbum(v, labelNomAlbum->text())){
            qDebug() << "Ajout d'image reussi";
            newBDDRequest(bdd->getAllImageByAlbum(labelNomAlbum->text()));
        } else {
            qDebug() << "Ajout d'image raté";
        }
    } else {
        qDebug() << "Ajout d'image annulé dû a 0 images sélectionnées";
    }
}

void ImageWindow::editName(){
    if(lineEditNameAlbum->isHidden()){
        lineEditNameAlbum->show();
        labelNomAlbum->hide();
        lineEditNameAlbum->setText(labelNomAlbum->text());
    } else {
        if(lineEditNameAlbum->text() == "" && lineEditNameAlbum->text() == labelNomAlbum->text()){
            lineEditNameAlbum->hide();
            labelNomAlbum->show();
        } else {
            if(bdd->updateAlbumName(labelNomAlbum->text(), lineEditNameAlbum->text())){
                qDebug() << "Nom de l'album modifié";
                labelNomAlbum->setText(lineEditNameAlbum->text());
                newBDDRequest(bdd->getAllImageByAlbum(labelNomAlbum->text()));
                lineEditNameAlbum->hide();
                labelNomAlbum->show();
            } else {
                qDebug() << "Nom de l'album NON modifié";
                lineEditNameAlbum->hide();
                labelNomAlbum->show();
            }
        }
    }
}

void ImageWindow::closeAlbum(){
    lineEditNameAlbum->setText("");
    lineEditNameAlbum->hide();
    labelNomAlbum->show();
    frameAfficheAlbum->hide();
    alphaRequest();
}

void ImageWindow::alphaRequest(){
    if(frameAfficheAlbum->isHidden()){
        newBDDRequest(bdd->getAllImages());
    } else {
        newBDDRequest(bdd->getAllImageByAlbum(labelNomAlbum->text()));
    }
}

void ImageWindow::dateRequest(){
    if(frameAfficheAlbum->isHidden()){
        newBDDRequest(bdd->getAllImagesByDate());
    } else {
        newBDDRequest(bdd->getAllImagesByDateAndAlbum(labelNomAlbum->text()));
    }
}

void ImageWindow::favRequest(){
    if(frameAfficheAlbum->isHidden()){
        newBDDRequest(bdd->getAllImagesByFav());
    } else {
        newBDDRequest(bdd->getAllImagesByFavAndAlbum(labelNomAlbum->text()));
    }
}

void ImageWindow::openColorPicker(){
    colorPicker->show();
}

void ImageWindow::showAlbumAuto(QString name){
    qDebug() << "Ouverture de l'album :" << name << "demandé...";
    frameAfficheAlbum->hide();
    if(name == "FAVORIS"){
        newBDDRequest(bdd->getAllImagesByFav());
    } else {
        buttonColorPicker->loadImage(colors.key(name)->imageName);
        buttonColorPicker->loadImageHighlighted(colors.key(name)->imageHighlightedName);
        buttonColorPicker->loadImageSelected(colors.key(name)->imageName);
        buttonColorPicker->loadImageSelectedHighlighted(colors.key(name)->imageHighlightedName);
        currentColor = colors.key(name);
        newBDDRequest(bdd->getAllImagesByColor(colors.value(currentColor)));
    }

}

void ImageWindow::showAlbum(QString name){
    qDebug() << "Ouverture de l'album :" << name << "demandé...";
    frameAfficheAlbum->show();
    QVector<Album*> albVec = bdd->getAllAlbums("name", name);
    if(albVec.size() == 0){
        qDebug() << "Erreur : Album" << name << "inexistant dans la table <album> (problème d'affichage ?) dans " << __FUNCTION__;
    } else {
        QPixmap pix = QPixmap();
        bool validate = pix.load(albVec[0]->getCover());
        if(validate){
            pix = pix.scaled(100,100,Qt::KeepAspectRatio);
            labelImageAlbum->setPixmap(pix);
        } else {
            qDebug() << "Erreur : Lors du chargement de l'image >" << albVec[0]->getCover() << "| Dans la fonction" << __FUNCTION__;
        }
        labelNomAlbum->setText(albVec[0]->getName());
        newBDDRequest(bdd->getAllImageByAlbum(name));
    }
}

void ImageWindow::newColor(){
    currentColor = colorPicker->currentColor;
    buttonColorPicker->loadImage(currentColor->imageName);
    buttonColorPicker->loadImageHighlighted(currentColor->imageHighlightedName);
    buttonColorPicker->loadImageSelected(currentColor->imageName);
    buttonColorPicker->loadImageSelectedHighlighted(currentColor->imageHighlightedName);
    colorPicker->close();
    if(frameAfficheAlbum->isHidden()){
        newBDDRequest(bdd->getAllImagesByColor(colors.value(currentColor)));
    } else {
        newBDDRequest(bdd->getAllImagesByColorAndAlbum(colors.value(currentColor), labelNomAlbum->text()));
    }
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
