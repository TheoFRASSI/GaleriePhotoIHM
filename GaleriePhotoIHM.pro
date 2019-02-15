#-------------------------------------------------
#
# Project created by QtCreator 2019-01-23T08:47:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GaleriePhotoIHM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imagebutton.cpp \
    mainmenu.cpp \
    accueilwindow.cpp \
    albumwindow.cpp \
    imagewindow.cpp \
    album.cpp \
    image.cpp \
    settingswindow.cpp \
    modifimagewindow.cpp \
    helpwindow.cpp \
    headermenu.cpp \
    bddgalleryphoto.cpp \
    colorpicker.cpp \
    colorbutton.cpp \
    imagesshowcase.cpp \
    formcreatealbum.cpp \
    clickablelabel.cpp

HEADERS += \
        mainwindow.h \
    imagebutton.h \
    mainmenu.h \
    accueilwindow.h \
    albumwindow.h \
    imagewindow.h \
    album.h \
    image.h \
    settingswindow.h \
    modifimagewindow.h \
    helpwindow.h \
    headermenu.h \
    bddgalleryphoto.h \
    colorpicker.h \
    colorbutton.h \
    imagesshowcase.h \
    smartdelete.h \
    formcreatealbum.h \
    clickablelabel.h

FORMS += \
        mainwindow.ui \
    accueilwindow.ui \
    albumwindow.ui \
    imagewindow.ui \
    settingswindow.ui \
    modifimagewindow.ui \
    helpwindow.ui \
    colorpicker.ui \
    imagesshowcase.ui \
    formcreatealbum.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
