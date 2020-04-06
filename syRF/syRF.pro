##------------------------------------------------------------------------##
##                                                                        ##
##  syRF                                                                  ##
##  Copyright (C) 2019 Francesco Urbani                                   ##
##                                                                        ##
##------------------------------------------------------------------------##
##  Author:         Francesco Urbani <https://urbanij.github.io/>         ##
##  Date:           Sat Dec  7 11:36:08 CET 2019                          ##
##  File:                                   
##  Description:    
##------------------------------------------------------------------------##

#-------------------------------------------------
#
# Project created by QtCreator 2019-11-23T10:55:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = syRF
TEMPLATE = app

#### QMAKE_INFO_PLIST = info.plist
#### ICON = icons/icns/icon3.icns

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    about.cpp \
    ccomplex.cpp \
    y_parameters.cpp

HEADERS += \
        mainwindow.h \
    about.h \
    ccomplex.h \
    y_parameters.h

FORMS += \
        mainwindow.ui \
        about.ui

RESOURCES += \
    resources.qrc \
    breeze.qrc
