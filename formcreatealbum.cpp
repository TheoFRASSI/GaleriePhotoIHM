#include "formcreatealbum.h"
#include "ui_formcreatealbum.h"

FormCreateAlbum::FormCreateAlbum(const BddGalleryPhoto * p_bdd, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    bdd = p_bdd;
    setWindowFlags(Qt::WindowTitleHint);
    setWindowTitle("Création d'album");

    boutonOk = new ImageButton(pathBoutonOkH, pathBoutonOk, 200, 70, this);    
    layoutBoutonOk->addWidget(boutonOk);

    boutonQuitter = new ImageButton(pathBoutonQuitterH, pathBoutonQuitter, 50, 50, this);
    boutonQuitter->setToolTip("Annuler et fermer");
    layoutBoutonQuitter->addWidget(boutonQuitter);

    boutonAddCover = new ImageButton(pathBoutonAddCoverH, pathBoutonAddCover, 300, 100, this);
    boutonAddCover->setToolTip("Choisir une image en tant que couverture pour l'album");
    layoutBoutonAddCover->addWidget(boutonAddCover);

    boutonAddImages = new ImageButton(pathBoutonAddImagesH, pathBoutonAddImages, 100, 100, this);
    boutonAddImages->setToolTip("Choisir des images à ajouter à l'album");
    layoutBoutonAddImages->addWidget(boutonAddImages);

    clean();

    connect(boutonAddCover, SIGNAL(clicked()), this, SLOT(selectCover()));
    connect(boutonAddImages, SIGNAL(clicked()), this, SLOT(selectImages()));
    connect(boutonOk, SIGNAL(clicked()), this, SLOT(validateChoices()));
    connect(boutonQuitter, SIGNAL(clicked()), this, SLOT(close()));
}

FormCreateAlbum::~FormCreateAlbum()
{
    smartDeleteMrNovelli(bdd);
    smartDeleteMrNovelli(boutonOk);
    smartDeleteMrNovelli(boutonQuitter);
    smartDeleteMrNovelli(boutonAddCover);
    smartDeleteMrNovelli(boutonAddImages);

}

void FormCreateAlbum::clean(){
    labelCover->setMaximumSize(300, 300);
    labelCover->setMinimumSize(300, 300);

    lineEdit->setText("");

    this->selectedImages.clear();

    labelNbImages->setText("0");

    bool validate = imageObli.load(pathImageObli);
    if(validate){
        imageObli = imageObli.scaled(300,300,Qt::KeepAspectRatio);
    } else {
        qDebug() << "Erreur : Lors du chargement de l'image >" << pathImageObli << "| Dans la fonction" << __FUNCTION__;
    }

    validate = imageCorrupt.load(pathImageCorrupt);
    if(validate){
        imageCorrupt = imageCorrupt.scaled(300,300,Qt::KeepAspectRatio);
    } else {
        qDebug() << "Erreur : Lors du chargement de l'image >" << pathImageCorrupt << "| Dans la fonction" << __FUNCTION__;
    }

    validate = imageVide.load(pathImageVide);
    if(validate){
        imageVide = imageVide.scaled(300,300,Qt::KeepAspectRatio);
        labelCover->setPixmap(imageVide);
        const QStringList fullPath = pathImageVide.split("/");
        selectedCover = Image(fullPath.last(), pathImageVide, QDate::currentDate(), "BLEU", "Cool", 0);
    } else {
        qDebug() << "Erreur : Lors du chargement de l'image >" << pathImageVide << "| Dans la fonction" << __FUNCTION__;
    }

    lineEdit->setStyleSheet("border: 2px solid black;");
    labelNbImages->setStyleSheet("color: #FFFFFF;");
    labelExisteDeja->hide();
}

void FormCreateAlbum::selectImages()
{
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    qsrand(static_cast<uint>(time(nullptr)));

    QVector<Image> selectedImages;
    const QStringList paths = QFileDialog::getOpenFileNames(this);

    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            QString colorImg = colors[qrand() % colors.size()];
            const QStringList fullPath = paths[i].split("/");
            Image newImage(fullPath.last(), paths[i], QDate::currentDate(), colorImg, "Cool", 0);
            selectedImages.push_back(newImage);

            this->selectedImages = selectedImages;
        }
    }
    qDebug() << this->selectedImages.size();
    labelNbImages->setText(QString::number(this->selectedImages.size()));
}

void FormCreateAlbum::selectCover()
{
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    qsrand(static_cast<uint>(time(nullptr)));
    QString colorImg = colors[qrand() % colors.size()];

    const QString path = QFileDialog::getOpenFileName(this);

    if (!path.isEmpty()) {
        const QStringList fullPath = path.split("/");
        Image selectedCover(fullPath.last(), path, QDate::currentDate(), colorImg, "Cool", 0);

        bool validate = cover.load(selectedCover.getPath());
        if(validate){
            cover = cover.scaled(300,300,Qt::KeepAspectRatio);
            labelCover->setPixmap(cover);
            this->selectedCover = selectedCover;
        } else {
            qDebug() << "Erreur : Lors du chargement de l'image >" << selectedCover.getPath() << "| Dans la fonction" << __FUNCTION__;
            labelCover->setPixmap(imageCorrupt);
            selectedCover.setPath(pathImageCorrupt);
        }
    }
}

void FormCreateAlbum::validateChoices()
{
    bool filled = true;
    selectedName = lineEdit->text();
    if(selectedName == "") {
        qDebug() << "Nom de l'album ne peut pas être vide";
        lineEdit->setStyleSheet("border: 2px solid red;");
        lineEdit->setPlaceholderText("CHAMP OBLIGATOIRE");
        filled = false;
    } else {
        lineEdit->setStyleSheet("border: 2px solid black;");
        lineEdit->setPlaceholderText("Nom de l'album");
    }

    qDebug() << selectedCover.getPath();
    if((selectedCover.getPath() == pathImageObli) || (selectedCover.getPath() == pathImageVide) || (selectedCover.getPath() == pathImageCorrupt)) {
        qDebug() << "Il faut choisir une cover pour l'album";
        selectedCover.setPath(pathImageObli);
        labelCover->setPixmap(imageObli);
        filled = false;
    }

    if(selectedImages.size() == 0) {
        qDebug() << "Il faut choisir au moins une image à ajouter dans l'album";
        labelNbImages->setStyleSheet("color: #FF0000;");
        filled = false;
    } else {
        labelNbImages->setStyleSheet("color: #FFFFFF;");
    }

    if(bdd->albumExists(lineEdit->text())){
        labelExisteDeja->show();
        lineEdit->setStyleSheet("border: 2px solid red;");
        filled = false;
    } else {
        labelExisteDeja->hide();
        lineEdit->setStyleSheet("border: 2px solid black;");
    }
    if(filled) {
        if(!bdd->imageExists(selectedCover.getName())) {
            bdd->insertImage(selectedCover);
        }

        for(int i  = 0; i < selectedImages.size(); i++) {
            if(!bdd->imageExists(selectedImages[i].getName())) {
                bdd->insertImage(selectedImages[i]);
            }
        }
        Album newAlbum(selectedName, selectedCover.getPath());
        bdd->insertAlbum(newAlbum);
        bdd->assocImageWithAlbum(selectedImages, newAlbum.getName());
        emit albumAdded();
        emit accept();
    }
}


