#include "headermenu.h"

HeaderMenu::HeaderMenu(QFrame* headerMenuFrame, QHBoxLayout* menu, QHBoxLayout* layoutSearch, QHBoxLayout* layoutNewAlbum, QHBoxLayout* layoutNewPhoto, QHBoxLayout* layoutDisplay, QHBoxLayout* layoutSettings,  QSpacerItem* horizontalSpacer, QLabel* labelTitre, QLineEdit* lineEdit)
           :headerMenuFrame(headerMenuFrame),
            menu(menu),
            layoutSearch(layoutSearch),
            layoutNewAlbum(layoutNewAlbum),
            layoutNewPhoto(layoutNewPhoto),
            layoutDisplay(layoutDisplay),
            layoutSettings(layoutSettings),
            horizontalSpacer(horizontalSpacer),
            labelTitre(labelTitre),
            lineEdit(lineEdit)
{
    buttonMenu = new ImageButton(imageButtonMenuPressed, imageButtonMenuReleased, 50, 50, this);
    menu->addWidget(buttonMenu);

    buttonSearch = new ImageButton(imageButtonSearchPressed, imageButtonSearchReleased, 60, 100, this);
    layoutSearch->addWidget(buttonSearch);

    buttonNewAlbum = new ImageButton(imageButtonNewAlbumPressed, imageButtonNewAlbumReleased, 50, 50, this);
    layoutNewAlbum->addWidget(buttonNewAlbum);

    buttonNewPhoto = new ImageButton(imageButtonNewPhotoPressed, imageButtonNewPhotoReleased, 50, 50, this);
    layoutNewPhoto->addWidget(buttonNewPhoto);

    buttonDisplay = new ImageButton(imageButtonDisplayPressed, imageButtonDisplayReleased, 50, 50, this);
    layoutDisplay->addWidget(buttonDisplay);

    buttonSettings = new ImageButton(imageButtonSettingsPressed, imageButtonSettingsReleased, 50, 50, this);
    layoutDisplay->addWidget(buttonSettings);

    layoutSearch->addSpacerItem(horizontalSpacer);
}

HeaderMenu::~HeaderMenu(){
    smartDeleteMrNovelli(buttonMenu);
    smartDeleteMrNovelli(buttonSearch);
    smartDeleteMrNovelli(buttonNewAlbum);
    smartDeleteMrNovelli(buttonNewPhoto);
    smartDeleteMrNovelli(buttonDisplay);
    smartDeleteMrNovelli(buttonSettings);
}

ImageButton* HeaderMenu::getButtonMenu(){
    return buttonMenu;
}

ImageButton* HeaderMenu::getButtonSearch(){
    return buttonSearch;
}

ImageButton* HeaderMenu::getButtonNewAlbum(){
    return buttonNewAlbum;
}

ImageButton* HeaderMenu::getButtonNewPhoto(){
    return buttonNewPhoto;
}

ImageButton* HeaderMenu::getButtonDisplay(){
    return buttonDisplay;
}

ImageButton* HeaderMenu::getButtonSettings(){
    return buttonSettings;
}

QLabel* HeaderMenu::getLabelTitre(){
    return labelTitre;
}

QLineEdit* HeaderMenu::getLineEdit(){
    return lineEdit;
}
