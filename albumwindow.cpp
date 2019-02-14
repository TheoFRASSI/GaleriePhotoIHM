#include "albumwindow.h"

#include <QLabel>

static void deleteChildWidgets(QLayoutItem *item) {
  QLayout *layout = item->layout();
  if (layout) {
    int itemCount = layout->count();
    for (int i = 0; i < itemCount; i++) {
      deleteChildWidgets(layout->itemAt(i));
    }
  }
  delete item->widget();
}

static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
  // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
  for (int i = layout->count() - 1; i >= 0; i--) {
    int r, c, rs, cs;
    layout->getItemPosition(i, &r, &c, &rs, &cs);
    if (
        (row == -1 || (r <= row && r + rs > row)) &&
        (column == -1 || (c <= column && c + cs > column))) {
      QLayoutItem *item = layout->takeAt(i);
      if (deleteWidgets) {
        deleteChildWidgets(item);
      }
      delete item;
    }
  }
}

static void removeCell(QGridLayout *layout, int row, int column, bool deleteWidgets = true) {
  remove(layout, row, column, deleteWidgets);
}


AlbumWindow::AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    bdd = pbdd;

    boutonAdd = new ImageButton(pathBoutonAddH, pathBoutonAdd, 200, 100, this);
    boutonSwitchD = new ImageButton(pathBoutonSwitchDroitH, pathBoutonSwitchDroit, 700, 80, this);
    boutonSwitchD->loadImageEnable(pathBoutonSwitchDroit);
    boutonSwitchD->loadImageDisable(pathBoutonSwitchDroitH);
    boutonSwitchG = new ImageButton(pathBoutonSwitchGaucheH, pathBoutonSwitchGauche, 700, 80, this);
    boutonSwitchG->loadImageEnable(pathBoutonSwitchGauche);
    boutonSwitchG->loadImageDisable(pathBoutonSwitchGaucheH);
    boutonSearch = new ImageButton(pathBoutonSearchH, pathBoutonSearch, 60, 100, this);

    layoutBoutonAdd->addWidget(boutonAdd);
    layoutBoutonDroit->addWidget(boutonSwitchD);
    layoutBoutonGauche->addWidget(boutonSwitchG);
    layoutBoutonSearch->addWidget(boutonSearch);

    connect(boutonSwitchG, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(boutonSwitchD, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(boutonAdd, SIGNAL(clicked()), this, SLOT(addAlbum()));
    connect(boutonSearch, SIGNAL(clicked()), this, SLOT(searchRequest()));
    connect(lineEdit, SIGNAL(returnPressed()), boutonSearch, SIGNAL(clicked()));

    formCreateAlbum = new FormCreateAlbum(bdd);
    connect(formCreateAlbum, SIGNAL(albumAdded()), this, SLOT(searchRequest()));

    newBDDRequest(bdd->getAllAlbums());
    generateAlbumAuto();
}

AlbumWindow::~AlbumWindow()
{
    //bdd->destroyBdd();
    smartDeleteMrNovelli(bdd);
}

void AlbumWindow::changeTab()
{
    if(sender() == boutonSwitchD) {
        boutonSwitchD->setDisable(true);
        boutonSwitchG->setDisable(false);
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == boutonSwitchG) {
        boutonSwitchD->setDisable(false);
        boutonSwitchG->setDisable(true);
        stackedWidget->setCurrentIndex(0);
    }
}

void AlbumWindow::addAlbum() {
    formCreateAlbum->clean();
    formCreateAlbum->show();
}

void AlbumWindow::searchRequest(){
    newBDDRequest(bdd->getAllAlbums("name", lineEdit->text()));
    generateAlbumAuto();
}

void AlbumWindow::newBDDRequest(QVector<Album *> albTab)
{
    const int SIZE_IMAGE = 250;
    const int NB_IMAGES  = 5;

    if(listAlbum->count() > 0){
        removeCell(listAlbum,-1,-1);
    }
    int k = 0;
    if(!albTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(albTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < albTab.size()){
                    QLabel * label = new QLabel();
                    QLabel * labelName = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);

                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        labelName->setText(albTab[k]->getName());
                        labelName->setPalette(QPalette(QColor(0,0,0)));
                        labelName->setAutoFillBackground(true);
                        labelName->setMaximumSize(150,30);
                        label->setPixmap(pix);
                        listAlbum->addWidget(label, i, j);
                        listAlbum->addWidget(labelName, i, j);
                    } else {
                        qDebug() << "Erreur : Lors du chargement de l'image de l'album >" << albTab[k]->getCover() << "| Dans la fonction" << __FUNCTION__;
                    }
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap());
        listAlbum->addWidget(label, 0, 0);
    }

}

void AlbumWindow::generateAlbumAuto() {
    const int SIZE_IMAGE = 250;
    const int NB_IMAGES  = 5;

    if(listAlbumAuto->count() > 0){
        removeCell(listAlbumAuto,-1,-1);
    }
    QVector<Album*> albTab;
    QVector<Image*> imagesColor;
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    for(int i = 0; i < colors.size(); i++) {
        QString colorImg = colors[i];
        imagesColor = bdd->getAllImagesByColor(colorImg);
        if(imagesColor.size() > 0) {
            Album * albColor = new Album("Album " + colorImg, imagesColor[0]->getPath());
            albTab.push_back(albColor);
        }
    }


    QVector<Image*> imagesFav = bdd->getAllImagesByFav();
    if(imagesFav.size() > 0) {
      Album * albFav = new Album("Album des favoris", imagesFav[0]->getPath());
      albTab.push_back(albFav);
    }

    int k = 0;
    if(!albTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(albTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < albTab.size()){
                    QLabel * label = new QLabel();
                    QLabel * labelName = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        labelName->setText(albTab[k]->getName());
                        labelName->setPalette(QPalette(QColor(0,0,0)));
                        labelName->setAutoFillBackground(true);
                        labelName->setMaximumSize(150,30);
                        label->setPixmap(pix);
                        listAlbumAuto->addWidget(label, i, j);
                        listAlbumAuto->addWidget(labelName, i, j);
                    } else {
                        qDebug() << "Erreur : Lors du chargement de l'image de l'album >" << albTab[k]->getCover() << "| Dans la fonction" << __FUNCTION__;
                    }
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap());
        listAlbumAuto->addWidget(label, 0, 0);
    }
}

