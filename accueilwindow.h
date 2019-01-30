#pragma once

#include "ui_accueilwindow.h"

class AccueilWindow : public QWidget, private Ui::AccueilWindow
{
    Q_OBJECT
public:
    explicit AccueilWindow(QWidget *parent = nullptr);

signals:

public slots:
};
