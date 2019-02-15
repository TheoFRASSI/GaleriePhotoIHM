#pragma once

#include <QDebug>
#include <QDialog>

#include "colorbutton.h"
#include "ui_colorpicker.h"
#include "smartdelete.h"

class ColorPicker : public QDialog, private Ui::ColorPicker
{
    Q_OBJECT

public:

    //--Constructeur Destructeur-------------
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker();
    //---------------------------------------

    //--Boutons------------------------------
    ColorButton* buttonbleu;
    ColorButton* buttonbleuClair1;
    ColorButton* buttonbleuClair2;
    ColorButton* buttonbleuClair3;
    ColorButton* buttonbleuGris;
    ColorButton* buttongris;
    ColorButton* buttonjaune;
    ColorButton* buttonjauneFonce;
    ColorButton* buttonmagenta;
    ColorButton* buttonmarron;
    ColorButton* buttonnoir;
    ColorButton* buttonorange;
    ColorButton* buttonorangeClair;
    ColorButton* buttonrose;
    ColorButton* buttonrouge;
    ColorButton* buttonvert;
    ColorButton* buttonvertClair;
    ColorButton* buttonvertFonce;
    ColorButton* buttonvertJaune;
    ColorButton* buttonviolet;
    //---------------------------------------

    //--Attributs----------------------------
    ColorButton* currentColor;
    //---------------------------------------

private:

    //--Attributs Constants------------------
    const int WIDTH = 40;
    const int HEIGHT = 40;
    //---------------------------------------

    //--Images-------------------------------
    QString bleu = ":/img/button/colors/bleu";
    QString bleuClair1 = ":/img/button/colors/bleuClair1";
    QString bleuClair1Highlighted = ":/img/button/colors/bleuClair1Highlighted";
    QString bleuClair1Selected = ":/img/button/colors/bleuClair1Selected";
    QString bleuClair1SelectedHighlighted = ":/img/button/colors/bleuClair1SelectedHighlighted";
    QString bleuClair2 = ":/img/button/colors/bleuClair2";
    QString bleuClair2Highlighted = ":/img/button/colors/bleuClair2Highlighted";
    QString bleuClair2Selected = ":/img/button/colors/bleuClair2Selected";
    QString bleuClair2SelectedHighlighted = ":/img/button/colors/bleuClair2SelectedHighlighted";
    QString bleuClair3 = ":/img/button/colors/bleuClair3";
    QString bleuClair3Highlighted = ":/img/button/colors/bleuClair3Highlighted";
    QString bleuClair3Selected = ":/img/button/colors/bleuClair3Selected";
    QString bleuClair3SelectedHighlighted = ":/img/button/colors/bleuClair3SelectedHighlighted";
    QString bleuGris = ":/img/button/colors/bleuGris";
    QString bleuGrisHighlighted = ":/img/button/colors/bleuGrisHighlighted";
    QString bleuGrisSelected = ":/img/button/colors/bleuGrisSelected";
    QString bleuGrisSelectedHighlighted = ":/img/button/colors/bleuGrisSelectedHighlighted";
    QString bleuHighlighted = ":/img/button/colors/bleuHighlighted";
    QString bleuSelected = ":/img/button/colors/bleuSelected";
    QString bleuSelectedHighlighted = ":/img/button/colors/bleuSelectedHighlighted";
    QString gris = ":/img/button/colors/gris";
    QString grisHighlighted = ":/img/button/colors/grisHighlighted";
    QString grisSelected = ":/img/button/colors/grisSelected";
    QString grisSelectedHighlighted = ":/img/button/colors/grisSelectedHighlighted";
    QString jaune = ":/img/button/colors/jaune";
    QString jauneFonce = ":/img/button/colors/jauneFonce";
    QString jauneFonceHighlighted = ":/img/button/colors/jauneFonceHighlighted";
    QString jauneFonceSelected = ":/img/button/colors/jauneFonceSelected";
    QString jauneFonceSelectedHighlighted = ":/img/button/colors/jauneFonceSelectedHighlighted";
    QString jauneHighlighted = ":/img/button/colors/jauneHighlighted";
    QString jauneSelected = ":/img/button/colors/jauneSelected";
    QString jauneSelectedHighlighted = ":/img/button/colors/jauneSelectedHighlighted";
    QString magenta = ":/img/button/colors/magenta";
    QString magentaHighlighted = ":/img/button/colors/magentaHighlighted";
    QString magentaSelected = ":/img/button/colors/magentaSelected";
    QString magentaSelectedHighlighted = ":/img/button/colors/magentaSelectedHighlighted";
    QString marron = ":/img/button/colors/marron";
    QString marronHighlighted = ":/img/button/colors/marronHighlighted";
    QString marronSelected = ":/img/button/colors/marronSelected";
    QString marronSelectedHighlighted = ":/img/button/colors/marronSelectedHighlighted";
    QString noir = ":/img/button/colors/noir";
    QString noirHighlighted = ":/img/button/colors/noirHighlighted";
    QString noirSelected = ":/img/button/colors/noirSelected";
    QString noirSelectedHighlighted = ":/img/button/colors/noirSelectedHighlighted";
    QString orange = ":/img/button/colors/orange";
    QString orangeHighlighted = ":/img/button/colors/orangeHighlighted";
    QString orangeSelected = ":/img/button/colors/orangeSelected";
    QString orangeSelectedHighlighted = ":/img/button/colors/orangeSelectedHighlighted";
    QString orangeClair = ":/img/button/colors/orangeClair";
    QString orangeClairHighlighted = ":/img/button/colors/orangeClairHighlighted";
    QString orangeClairSelected = ":/img/button/colors/orangeClairSelected";
    QString orangeClairSelectedHighlighted = ":/img/button/colors/orangeClairSelectedHighlighted";
    QString rose = ":/img/button/colors/rose";
    QString roseHighlighted = ":/img/button/colors/roseHighlighted";
    QString roseSelected = ":/img/button/colors/roseSelected";
    QString roseSelectedHighlighted = ":/img/button/colors/roseSelectedHighlighted";
    QString rouge = ":/img/button/colors/rouge";
    QString rougeHighlighted = ":/img/button/colors/rougeHighlighted";
    QString rougeSelected = ":/img/button/colors/rougeSelected";
    QString rougeSelectedHighlighted = ":/img/button/colors/rougeSelectedHighlighted";
    QString vert = ":/img/button/colors/vert";
    QString vertClair = ":/img/button/colors/vertClair";
    QString vertClairHighlighted = ":/img/button/colors/vertClairHighlighted";
    QString vertClairSelected = ":/img/button/colors/vertClairSelected";
    QString vertClairSelectedHighlighted = ":/img/button/colors/vertClairSelectedHighlighted";
    QString vertFonce = ":/img/button/colors/vertFonce";
    QString vertFonceHighlighted = ":/img/button/colors/vertFonceHighlighted";
    QString vertFonceSelected = ":/img/button/colors/vertFonceSelected";
    QString vertFonceSelectedHighlighted = ":/img/button/colors/vertFonceSelectedHighlighted";
    QString vertHighlighted = ":/img/button/colors/vertHighlighted";
    QString vertJaune = ":/img/button/colors/vertJaune";
    QString vertJauneHighlighted = ":/img/button/colors/vertJauneHighlighted";
    QString vertJauneSelected = ":/img/button/colors/vertJauneSelected";
    QString vertJauneSelectedHighlighted = ":/img/button/colors/vertJauneSelectedHighlighted";
    QString vertSelected = ":/img/button/colors/vertSelected";
    QString vertSelectedHighlighted = ":/img/button/colors/vertSelectedHighlighted";
    QString violet = ":/img/button/colors/violet";
    QString violetHighlighted = ":/img/button/colors/violetHighlighted";
    QString violetSelected = ":/img/button/colors/violetSelected";
    QString violetSelectedHighlighted = ":/img/button/colors/violetSelectedHighlighted";
    //---------------------------------------

    //--Fonctions----------------------------
    void initGridColor();
    void deselectAll();
    //---------------------------------------

public slots:
    void chooseColor();

signals:
    void aboutToChoose();
};


