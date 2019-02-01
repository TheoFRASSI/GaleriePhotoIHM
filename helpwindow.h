#pragma once

#include <QWidget>
#include "ui_helpwindow.h"

class HelpWindow : public QWidget, private Ui::HelpWindow
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
};

