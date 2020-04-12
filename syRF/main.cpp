/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sat Dec  7 11:36:08 CET 2019                          **
**  File:           main.cpp                                              **                       
**  Description:                                                          **
****************************************************************************/

#include "mainwindow.h"
#include "config.h"
#include <QApplication>

#include <QTextStream>
#include <QFile>// required for the dark theme

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // applying dark theme
    QFile file(":/dark.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    // a.setStyleSheet(stream.readAll());    // by just commenting this line out you go back to default theme



    MainWindow w;

    w.setWindowTitle("syRF " VERSION);

    w.show();

    return a.exec();
}
