#include "headermenu.h"

HeaderMenu::HeaderMenu(QFrame* headerMenuFrame, QHBoxLayout* menu, QHBoxLayout* layoutSearch, QHBoxLayout* layoutNewAlbum, QHBoxLayout* layoutNewPhoto, QHBoxLayout* layoutDisplay, QHBoxLayout* layoutSettings,  QSpacerItem* horizontalSpacer, QLabel* labelTitre)
           :headerMenuFrame(headerMenuFrame),
            menu(menu),
            layoutSearch(layoutSearch),
            layoutNewAlbum(layoutNewAlbum),
            layoutNewPhoto(layoutNewPhoto),
            layoutDisplay(layoutDisplay),
            layoutSettings(layoutSettings),
            horizontalSpacer(horizontalSpacer),
            labelTitre(labelTitre)
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
    delete buttonMenu;
    buttonMenu = nullptr;
    delete buttonSearch;
    buttonSearch = nullptr;
    delete buttonNewAlbum;
    buttonNewAlbum = nullptr;
    delete buttonNewPhoto;
    buttonNewPhoto = nullptr;
    delete buttonDisplay;
    buttonDisplay = nullptr;
    delete buttonSettings;
    buttonSettings = nullptr;
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

QLabel *HeaderMenu::getLabelTitre()
{
    return labelTitre;
}
