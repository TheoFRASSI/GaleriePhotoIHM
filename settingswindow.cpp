#include "settingswindow.h"

SettingsWindow::SettingsWindow(const BddGalleryPhoto* pbdd, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    connect(addPathPushButton, SIGNAL(clicked()), this, SLOT(addPath()));
    connect(supprPathPushButton, SIGNAL(clicked()), this, SLOT(suppressedPath()));

    selectedPath = nullptr;
}

SettingsWindow::~SettingsWindow()
{
    for (QVector<QString*>::iterator i = paths.begin(); i != paths.end(); i++){
        delete (*i);
        (*i) = nullptr;
    }
    paths.clear();
}

void SettingsWindow::addPath()
{
    QString directory_path = searchDirectoryPath();

    if(directory_path != nullptr){
        paths.push_back(&directory_path);
        pathListWidget->addItem(*paths.last());
        addImagesFromPath(paths.last());
    }
}

void SettingsWindow::suppressedPath()
{
    if(!paths.isEmpty()){
        qDebug() << pathListWidget->currentItem()->text();
        selectedPath = new QString(pathListWidget->currentItem()->text());
        qDebug() << selectedPath;

        QList<QListWidgetItem*> items = pathListWidget->selectedItems();
        foreach(QListWidgetItem * item, items) {
            delete pathListWidget->takeItem(pathListWidget->row(item));
        }
        deleteImagesFromPath(selectedPath);
        paths.removeOne(selectedPath);
        selectedPath = nullptr;
    }
}

void SettingsWindow::addImagesFromPath(QString * path)
{
    qDebug() << __FUNCTION__ << *path;
    QFileDialog dialogue;
    dialogue.setDirectory(*path);
    qDebug() << dialogue.directory();

    QDir dir(*path);
    if(!dir.exists()) {
        qWarning("Impossible de trouver le répertoire");
    } else {

        dir.setFilter(QDir::Files);        
        QFileInfoList list = dir.entryInfoList();        
        qsrand(static_cast<uint>(time(nullptr)));
        for (int i = 0; i < list.size(); i++) {
            QFileInfo fileInfo = list.at(i);            
            addImageToBdd(qPrintable(QString("%1/%2")
                                     .arg(*path)
                                     .arg(fileInfo.fileName())),
                          qPrintable(QString("%1").arg(fileInfo.fileName())));
        }
    }
}

void SettingsWindow::deleteImagesFromPath(QString * path)
{
    QDir dir(*path);
    if(!dir.exists()) {
        qWarning("Impossible de trouver le répertoire");
    } else {
        dir.setFilter(QDir::Files);        
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); i++) {
            QFileInfo fileInfo = list.at(i);
            bdd->deleteImageByName(qPrintable(QString("%1").arg(fileInfo.fileName())));
        }
    }
}

void SettingsWindow::addImageToBdd(QString pathImage, QString nameImage)
{
    QVector<QString> colors = {"BLEU", "BLEU_CLAIR_1", "BLEU_CLAIR_2", "BLEU_CLAIR_3", "BLEU_GRIS",
                              "GRIS", "JAUNE", "JAUNE_FONCE", "MAGENTA", "MARRON", "NOIR", "ORANGE", "ORANGE_CLAIR",
                              "ROSE", "ROUGE", "VERT", "VERT_CLAIR", "VERT_FONCE", "VERT_JAUNE", "VIOLET"};
    QString colorImg = colors[qrand() % colors.size()];
    Image newImage(nameImage, pathImage, QDate::currentDate(), colorImg, "Cool", 0);
    bdd->insertImage(newImage);
}

QString SettingsWindow::searchDirectoryPath()
{
    const QString& folderPath = QFileDialog::getExistingDirectory(this);
    if (!folderPath.isEmpty()) {
        qDebug() << folderPath;
        return folderPath;
    }
    return nullptr;
}
