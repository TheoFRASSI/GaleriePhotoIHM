#pragma once

#include <QDebug>

#include "ui_accueilwindow.h"
#include "imagebutton.h"
#include "colorpicker.h"

class AccueilWindow : public QWidget, private Ui::AccueilWindow
{
    Q_OBJECT
public:

    //--Constructeur Desctructeur------------------------------
    explicit AccueilWindow(QWidget *parent = nullptr);
    ~AccueilWindow();
    //---------------------------------------------------------

    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Getters Setters----------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    //---------------------------------------------------------


private:
    //--Fonctions----------------------------------------------
    //---------------------------------------------------------

    //--Attributs----------------------------------------------
    ColorPicker* colorPicker;
    ColorButton* currentColor;
    ColorButton* buttonColorPicker;
    //---------------------------------------------------------

    //--Images-------------------------------------------------
    QString imageStar = ":/img/window/star";
    QString imageEye = ":/img/window/eye";
    //---------------------------------------------------------

public slots:
    void openColorPicker();
    void newColor();

signals:

};
