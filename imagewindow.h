#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>

#include "bddgalleryphoto.h"
#include "ui_imagewindow.h"
#include "smartdelete.h"
#include "imagebutton.h"


class ImageWindow : public QWidget, private Ui::ImageWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(const BddGalleryPhoto* pbdd, QVector<Image*> imagesTab, QWidget *parent = nullptr);
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

    QPixmap imageVide;
    QPixmap aucuneImage;
    ImageButton* boutonAdd;

    QGridLayout* grid;

    QString pathImageVide = ":/img/window/imageVide";
    QString pathAucuneImage = ":/img/window/aucuneImage";
    QString pathBoutonAdd = ":/img/button/boutonAdd";
    QString pathBoutonAddH = ":/img/button/boutonAddH";

    // Removes all layout items which span the given row and column.
      static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
          qDebug() << "Plop";
        // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
        for (int i = layout->count() - 1; i >= 0; i--) {
          int r, c, rs, cs;
          layout->getItemPosition(i, &r, &c, &rs, &cs);
          if (
              (row == -1 || (r <= row && r + rs > row)) &&
              (column == -1 || (c <= column && c + cs > column))) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
            if (deleteWidgets) {
              deleteChildWidgets(item);
            }
            delete item;
          }
        }
      }

      // Deletes all child widgets of the given layout item.
      static void deleteChildWidgets(QLayoutItem *item) {
        QLayout *layout = item->layout();
        if (layout) {
          // Process all child items recursively.
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
};

