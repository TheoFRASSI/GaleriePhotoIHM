#pragma once

#include <iostream>
#include <QVBoxLayout>
#include <QFrame>
#include <QEvent>

class MainMenu : public QVBoxLayout
{
    Q_OBJECT

public:
    MainMenu(QVBoxLayout* container);
    ~MainMenu();

private:
    const int MINWIDTH = 100;
    const int MAXWIDTH = 300;
    QVBoxLayout* container;
    bool open = false;

public slots:
    void openMenu();
};
