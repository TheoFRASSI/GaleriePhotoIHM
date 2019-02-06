#pragma once

#include <QWidget>

#include "ui_helpwindow.h"
#include "smartdelete.h"

class HelpWindow : public QWidget, private Ui::HelpWindow
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
};

