#include "settingswindow.h"

SettingsWindow::SettingsWindow(const BddGalleryPhoto* pbdd, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    bdd = pbdd;

    connect(addPathPushButton, SIGNAL(clicked()), this, SLOT(addPath()));
    connect(supprPathPushButton, SIGNAL(clicked()), this, SLOT(suppressedPath()));
    //paths = new QMap<QString*, QString*>;
    //paths = new or<QString *>;

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
    }

    addImagesFromPath(paths.last());
}

void SettingsWindow::suppressedPath()
{
    if(!paths.isEmpty()){
        qDebug() << pathListWidget->currentItem()->text();
        selectedPath = new QString(pathListWidget->currentItem()->text());
        qDebug() << selectedPath;
        qDebug() << *selectedPath;
        //qDebug() << *paths->last();
        //qDebug() << paths->indexOf(selectedPath);

        QList<QListWidgetItem*> items = pathListWidget->selectedItems();
        foreach(QListWidgetItem * item, items) {
            delete pathListWidget->takeItem(pathListWidget->row(item));
        }

        paths.removeOne(selectedPath);
        selectedPath = nullptr;
    }
}

void SettingsWindow::addImagesFromPath(QString * path)
{
    qDebug() << __FUNCTION__ << *path;
    QFileDialog dialogue;
    dialogue.setDirectory(*path);
    //dialogue.setViewMode(QFileDialog::Detail);
    //dialogue.exec();
    qDebug() << dialogue.directory();

    QDir dir(*path);
    if(!dir.exists()) {
        qWarning("Cannot find the directory");
    } else {

        /*QStringList nameFilter;
        nameFilter << "*.jpg";
        dir.setNameFilters(nameFilter);*/

        dir.setFilter(QDir::Files);
        //dir.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); i++) {
            QFileInfo fileInfo = list.at(i);
            /*qDebug() << qPrintable(QString("%1 %2")
                                   .arg(fileInfo.size(), 10)
                                   .arg(fileInfo.fileName()));*/
            addImageToBdd(qPrintable(QString("%1/%2")
                                     .arg(*path)
                                     .arg(fileInfo.fileName())),
                          qPrintable(QString("%1").arg(fileInfo.fileName())));
        }
    }
}

void SettingsWindow::addImageToBdd(QString pathImage, QString nameImage)
{
    Image newImage(nameImage, pathImage);
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
