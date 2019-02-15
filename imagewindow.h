#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QProgressBar>

#include "bddgalleryphoto.h"
#include "ui_imagewindow.h"
#include "smartdelete.h"
#include "imagebutton.h"
#include "colorpicker.h"
#include "clickablelabel.h"


class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    //--Constructeur Destructeur-------------------------------
    explicit ImageWindow(const BddGalleryPhoto* pbdd, QProgressBar *progressBar, QWidget *parent = nullptr);
    ~ImageWindow();
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    QFrame *getFrameAlbum() const;
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    void newBDDRequest(QVector<Image *> imagesTab);
    //---------------------------------------------------------

private:
    //--Fonctions----------------------------------------------
    void initColors();
    //---------------------------------------------------------

    //--Attributs constants----------------------------------------------
    const int NB_IMAGES = 6;
    const int SIZE_IMAGE = 250;
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    const BddGalleryPhoto* bdd;

    ColorPicker* colorPicker;
    ColorButton* currentColor;
    ColorButton* buttonColorPicker;
    QPixmap imageVide;
    QPixmap aucuneImage;
    ImageButton* boutonAdd;
    QPixmap imageCorrupt;
    ImageButton* boutonFav;
    ImageButton* boutonFeel;
    ImageButton* boutonDate;
    ImageButton* boutonAlpha;
    QProgressBar * progressBar;
    QFrame* frameAlbum;

    ImageButton* boutonFermer;
    ImageButton* boutonEditName;
    ImageButton* boutonAddImages;
    ImageButton* boutonDeleteAlbum;

    QMap<ColorButton*, QString> colors;    

    QGridLayout* grid;

    QString pathImageVide = ":/img/window/imageVide";
    QString pathAucuneImage = ":/img/window/aucuneImage";
    QString pathBoutonAdd = ":/img/button/boutonAdd";
    QString pathBoutonAddH = ":/img/button/boutonAddH";
    QString pathImageCorrupt = ":/img/window/imageCorrupt";

    QString pathFav = ":/img/button/fav";
    QString pathFavH = ":/img/button/favH";
    QString pathFeel = ":/img/button/feel";
    QString pathFeelH = ":/img/button/feelH";
    QString pathDate = ":/img/button/date";
    QString pathDateH = ":/img/button/dateH";
    QString pathAlpha = ":/img/button/alpha";
    QString pathAlphaH = ":/img/button/alphaH";

    QString pathFermer = ":/img/button/boutonQuitter";
    QString pathFermerH = ":/img/button/boutonQuitterH";
    QString pathEditName = ":/img/button/boutonEditName";
    QString pathEditNameH = ":/img/button/boutonEditNameH";
    QString pathAddImages = ":/img/button/boutonAddImagesInAlbum";
    QString pathAddImagesH = ":/img/button/boutonAddImagesInAlbumH";
    QString pathDeleteAlbum = ":/img/button/boutonDelete";
    QString pathDeleteAlbumH = ":/img/button/boutonDeleteH";
    //---------------------------------------------------------




signals:
    void imageClicked(QString name);
    void goToAlbWindow();

public slots:
    void searchImage();
    void openColorPicker();
    void newColor();
    void alphaRequest();
    void dateRequest();
    void favRequest();
    void showAlbumAuto(QString name);
    void showAlbum(QString name);

    void deleteAlbum();
    void addImages();
    void editName();
    void closeAlbum();

    void imageClick();
};

