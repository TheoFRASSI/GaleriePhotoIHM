#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

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
        //paths->removeOne(pathListWidget->currentItem()->text());
        pathListWidget->removeItemWidget(pathListWidget->itemAt());
        paths.removeOne(selectedPath);
        selectedPath = nullptr;
    }
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
