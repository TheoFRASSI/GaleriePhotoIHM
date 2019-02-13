#include "formcreatealbum.h"
#include "ui_formcreatealbum.h"

FormCreateAlbum::FormCreateAlbum(const BddGalleryPhoto * p_bdd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormCreateAlbum)
{
    ui->setupUi(this);
    bdd = p_bdd;
    connect(ui->selectCoverButton, SIGNAL(clicked()), this, SLOT(selectCover()));
    connect(ui->selectImagesButton, SIGNAL(clicked()), this, SLOT(selectImages()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(validateChoices()));
}

FormCreateAlbum::~FormCreateAlbum()
{
    delete ui;
}

void FormCreateAlbum::selectImages()
{
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    qsrand(static_cast<uint>(time(nullptr)));
    QString colorImg = colors[qrand() % colors.size()];

    QVector<Image> selectedImages;
    const QStringList paths = QFileDialog::getOpenFileNames(this);

    if (!paths.isEmpty()) {
        for(int i = 0; i < paths.size() ; i++) {
            const QStringList fullPath = paths[i].split("/");
            Image newImage(fullPath.last(), paths[i], QStringList(), QDate::currentDate(), colorImg, "Cool");
            selectedImages.push_back(newImage);

            this->selectedImages = selectedImages;
        }
    }
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
        Image selectedCover(fullPath.last(), path, QStringList(), QDate::currentDate(), colorImg, "Cool");

        this->selectedCover = selectedCover;
    }
}

void FormCreateAlbum::validateChoices()
{
    bool filled = true;
    selectedName = ui->textAlbumName->text();
    if(selectedName == "") {
        qDebug() << "Nom de l'album ne peut pas être vide";
        ui->textAlbumName->setPlaceholderText("OBLIGATOIRE");
        filled = false;
    }
    if(selectedCover.getName() == "") { // ça ça marche pas!!!!!!!!!!!!!!!!!!!!!!!!!!
        qDebug() << "Il faut choisir une cover pour l'album";
        filled = false;
    }
    if(selectedImages.size() == 0) {
        qDebug() << "Il faut choisir au moins une image à ajouter dans l'album";
        filled = false;
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
        Album newAlbum(selectedName, selectedCover.getPath(), selectedImages);
        bdd->insertAlbum(newAlbum);
        emit accept();
    }
}


