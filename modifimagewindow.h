#pragma once

#include "ui_modifimagewindow.h"
#include "smartdelete.h"

class ModifImageWindow : public QWidget, private Ui::ModifImageWindow
{
    Q_OBJECT

public:
    explicit ModifImageWindow(QWidget *parent = nullptr);
};
