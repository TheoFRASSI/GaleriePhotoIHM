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


class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(const BddGalleryPhoto* pbdd, QProgressBar *progressBar, QWidget *parent = nullptr);
    ~ImageWindow();
    void newBDDRequest(QVector<Image *> imagesTab);

    // Removes the contents of the given layout row.
      static void removeRow(QGridLayout *layout, int row, bool deleteWidgets = true) {
        remove(layout, row, -1, deleteWidgets);
        layout->setRowMinimumHeight(row, 0);
        layout->setRowStretch(row, 0);
      }

      // Removes the contents of the given layout column.
      static void removeColumn(QGridLayout *layout, int column, bool deleteWidgets = true) {
        remove(layout, -1, column, deleteWidgets);
        layout->setColumnMinimumWidth(column, 0);
        layout->setColumnStretch(column, 0);
      }

      // Removes the contents of the given layout cell.
      static void removeCell(QGridLayout *layout, int row, int column, bool deleteWidgets = true) {
        remove(layout, row, column, deleteWidgets);
      }

private:

    const int NB_IMAGES = 6;
    const int SIZE_IMAGE = 250;

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

    QMap<ColorButton*, QString> colors;

    void initColors();

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

      static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
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

signals:

public slots:
    void searchImage();
    void openColorPicker();
    void newColor();
    void alphaRequest();
    void dateRequest();
    void favRequest();
};

