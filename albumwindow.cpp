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
    boutonAdd->setToolTip("Créer un nouvel album");
    boutonSwitchD = new ImageButton(pathBoutonSwitchDroitH, pathBoutonSwitchDroit, 700, 80, this);
    boutonSwitchD->setToolTip("Acceder à l'onglet Albums Automatiques");
    boutonSwitchD->loadImageEnable(pathBoutonSwitchDroit);
    boutonSwitchD->loadImageDisable(pathBoutonSwitchDroitH);
    boutonSwitchG = new ImageButton(pathBoutonSwitchGaucheH, pathBoutonSwitchGauche, 700, 80, this);
    boutonSwitchG->setToolTip("Acceder à l'onglet mes albums");
    boutonSwitchG->loadImageEnable(pathBoutonSwitchGauche);
    boutonSwitchG->loadImageDisable(pathBoutonSwitchGaucheH);
    boutonSearch = new ImageButton(pathBoutonSearchH, pathBoutonSearch, 60, 100, this);
    boutonSearch->setToolTip("Lancer la recherche");

    etiquette = QPixmap(pathEtiquette);

    initMap();

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

    boutonSwitchG->setDisable(true);
    stackedWidget->setCurrentIndex(0);
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
                    QLabel* label = new QLabel();
                    ClickableLabel* labelName = new ClickableLabel();
                    QLabel* labelEtiquette = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    labelEtiquette->setMaximumSize(SIZE_IMAGE - SIZE_IMAGE/4, SIZE_IMAGE);
                    labelEtiquette->setMinimumSize(SIZE_IMAGE - SIZE_IMAGE/4, SIZE_IMAGE);
                    etiquette = etiquette.scaled(SIZE_IMAGE - SIZE_IMAGE/4, SIZE_IMAGE,Qt::KeepAspectRatio);

                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE - 20, SIZE_IMAGE - 20, Qt::KeepAspectRatio);
                        labelName->setText(albTab[k]->getName());
                        labelName->setStyleSheet("font-weight: bold; color: #000000; font-size: 10pt;");
                        labelName->setMaximumSize(SIZE_IMAGE - SIZE_IMAGE/3,SIZE_IMAGE);
                        labelName->setMinimumSize(SIZE_IMAGE - SIZE_IMAGE/3,SIZE_IMAGE);
                        labelName->setWordWrap(true);
                        labelName->setMargin(20);
                        labelEtiquette->setPixmap(etiquette);
                        label->setPixmap(pix);
                        label->setMargin(10);
                        listAlbum->addWidget(label, i, j);
                        listAlbum->addWidget(labelEtiquette,i ,j);
                        listAlbum->addWidget(labelName, i, j);
                        connect(labelName, SIGNAL(clicked()), this, SLOT(clickAlbum()));
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
    generateAlbumAuto();
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

    QVector<Image*> imagesFav = bdd->getAllImagesByFav();
    if(imagesFav.size() > 0) {
      Album * albFav = new Album("Album des Favoris", mapAlbums.value("FAVORIS"));
      albTab.push_back(albFav);
    }

    for(int i = 0; i < colors.size(); i++) {
        QString colorImg = colors[i];
        imagesColor = bdd->getAllImagesByColor(colorImg);
        if(imagesColor.size() > 0) {
            Album * albColor = new Album("Album " + mapColors.value(colorImg), mapAlbums.value(colorImg));
            albTab.push_back(albColor);
        }
    }

    int k = 0;
    if(!albTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(albTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < albTab.size()){
                    QLabel* label = new QLabel();
                    ClickableLabel* labelName = new ClickableLabel();
                    QLabel* labelEtiquette = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    labelEtiquette->setMaximumSize(SIZE_IMAGE , SIZE_IMAGE);
                    labelEtiquette->setMinimumSize(SIZE_IMAGE , SIZE_IMAGE);
                    etiquette = etiquette.scaled(SIZE_IMAGE - SIZE_IMAGE/4, SIZE_IMAGE,Qt::KeepAspectRatio);

                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE);
                        labelName->setText(albTab[k]->getName());
                        labelName->setStyleSheet("font-weight: bold; color: #000000; font-size: 10pt;");
                        labelName->setMaximumSize(SIZE_IMAGE - SIZE_IMAGE/3,SIZE_IMAGE);
                        labelName->setMinimumSize(SIZE_IMAGE - SIZE_IMAGE/3,SIZE_IMAGE);
                        labelName->setWordWrap(true);
                        labelName->setMargin(30);
                        labelEtiquette->setPixmap(etiquette);
                        labelEtiquette->setMargin(10);
                        label->setPixmap(pix);
                        listAlbumAuto->addWidget(label, i, j);
                        listAlbumAuto->addWidget(labelEtiquette,i ,j);
                        listAlbumAuto->addWidget(labelName, i, j);
                        connect(labelName, SIGNAL(clicked()), this, SLOT(clickAlbumAuto()));
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

void AlbumWindow::clickAlbum(){
    ClickableLabel* lab = dynamic_cast<ClickableLabel*>(sender());
    emit albumClicked(lab->text());
    qDebug() << "SIGNAL albumClicked(QString name) emit";
}

void AlbumWindow::clickAlbumAuto(){
    ClickableLabel* lab = dynamic_cast<ClickableLabel*>(sender());
    const QStringList name = lab->text().split("Album ");
    emit albumAutoClicked(mapColors.key(name.last()));
    qDebug() << "SIGNAL albumAutoClicked(QString name) emit";
}

void AlbumWindow::initMap(){
    mapColors.insert("BLEU", "Bleu");
    mapColors.insert("BLEU_CLAIR_1", "Bleu Roi");
    mapColors.insert("BLEU_CLAIR_2", "Bleu France");
    mapColors.insert("BLEU_CLAIR_3", "Bleu Azur");
    mapColors.insert("BLEU_GRIS", "Bleu-Gris");
    mapColors.insert("GRIS", "Gris");
    mapColors.insert("JAUNE", "Jaune");
    mapColors.insert("JAUNE_FONCE", "Jaune Banane");
    mapColors.insert("MAGENTA", "Magenta");
    mapColors.insert("MARRON", "Marron");
    mapColors.insert("NOIR", "Noir");
    mapColors.insert("ORANGE", "Orange");
    mapColors.insert("ORANGE_CLAIR", "Orange Clair");
    mapColors.insert("ROSE", "Rose");
    mapColors.insert("ROUGE", "Rouge");
    mapColors.insert("VERT", "Vert");
    mapColors.insert("VERT_CLAIR", "Vert Clair");
    mapColors.insert("VERT_FONCE", "Vert Foncé");
    mapColors.insert("VERT_JAUNE", "Jaune Moutarde");
    mapColors.insert("VIOLET", "Violet");
    mapColors.insert("FAVORIS", "des Favoris");

    mapAlbums.insert("BLEU", ":/img/window/albumBleu");
    mapAlbums.insert("BLEU_CLAIR_1", ":/img/window/albumBleuClair1");
    mapAlbums.insert("BLEU_CLAIR_2", ":/img/window/albumBleuClair2");
    mapAlbums.insert("BLEU_CLAIR_3", ":/img/window/albumBleuClair3");
    mapAlbums.insert("BLEU_GRIS", ":/img/window/albumBleuGris");
    mapAlbums.insert("GRIS", ":/img/window/albumGris");
    mapAlbums.insert("JAUNE", ":/img/window/albumJaune");
    mapAlbums.insert("JAUNE_FONCE", ":/img/window/albumJauneFonce");
    mapAlbums.insert("MAGENTA", ":/img/window/albumMagenta");
    mapAlbums.insert("MARRON", ":/img/window/albumMarron");
    mapAlbums.insert("NOIR", ":/img/window/albumNoir");
    mapAlbums.insert("ORANGE", ":/img/window/albumOrange");
    mapAlbums.insert("ORANGE_CLAIR", ":/img/window/albumOrangeClair");
    mapAlbums.insert("ROSE", ":/img/window/albumRose");
    mapAlbums.insert("ROUGE", ":/img/window/albumRouge");
    mapAlbums.insert("VERT", ":/img/window/albumVert");
    mapAlbums.insert("VERT_CLAIR", ":/img/window/albumVertClair");
    mapAlbums.insert("VERT_FONCE", ":/img/window/albumVertFonce");
    mapAlbums.insert("VERT_JAUNE", ":/img/window/albumVertJaune");
    mapAlbums.insert("VIOLET", ":/img/window/albumViolet");
    mapAlbums.insert("FAVORIS", ":/img/window/albumFavoris");
}
