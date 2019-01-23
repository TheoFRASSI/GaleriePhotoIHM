#include "mainmenu.h"

MainMenu::MainMenu(QVBoxLayout* container)
        : container(container)
{
    this->container->findChild<QFrame*>("frameMainMenu")->setMinimumWidth(this->MINWIDTH);
    this->container->findChild<QFrame*>("frameMainMenu")->setMaximumWidth(this->MINWIDTH);
}

MainMenu::~MainMenu(){

}

void MainMenu::openMenu(){
    if(!this->open){
        this->container->findChild<QFrame*>("frameMainMenu")->setMinimumWidth(this->MAXWIDTH);
        this->container->findChild<QFrame*>("frameMainMenu")->setMaximumWidth(this->MAXWIDTH);
        this->open = !this->open;
    } else {
        this->container->findChild<QFrame*>("frameMainMenu")->setMinimumWidth(this->MINWIDTH);
        this->container->findChild<QFrame*>("frameMainMenu")->setMaximumWidth(this->MINWIDTH);
        this->open = !this->open;
    }
}
