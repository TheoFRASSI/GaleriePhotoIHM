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
    connect(albPersoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(albAutoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(newAlbButton, SIGNAL(clicked()), this, SLOT(addAlbum()));

    addAlbum(); // pour pas que la requete pète TEMPORAIRE    

    newBDDRequest(bdd->getAllAlbums());

}

AlbumWindow::~AlbumWindow()
{
    //bdd->destroyBdd();
    smartDeleteMrNovelli(bdd);
}

void AlbumWindow::changeTab()
{
    if(sender() == albAutoButton) {
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == albPersoButton) {
        stackedWidget->setCurrentIndex(0);
    }
}

void AlbumWindow::addAlbum() {
    Image* img = bdd->getImageByName("599779.jpg");
    QString cover = img->getPath();
    QString name = "Alb";
    Album alb(name, cover);
    bdd->insertAlbum(alb);
    newBDDRequest(bdd->getAllAlbums());
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
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        label->setPixmap(pix);
                        listAlbum->addWidget(label, i, j);
                    } else {
                        qDebug() << "Erreur : Lors du chargement de l'image >" << albTab[k]->getCover() << "| Dans la fonction" << __FUNCTION__;
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

