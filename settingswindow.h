#pragma once

#include "ui_settingswindow.h"

class SettingsWindow : public QWidget, private Ui::SettingsWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);

signals:

public slots:
};

