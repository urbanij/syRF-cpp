/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019-2020 Francesco Urbani                              **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sat Dec  7 11:36:08 CET 2019                          **
**  File:           about.cpp                                             **                    
**  Description:    about window                                          **
****************************************************************************/

#include "about.h"
#include "ui_about.h"

#include "config.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->label_version->setText(VERSION);    // read version from external file later !

    QString urls = "<a href=\"https://urbanij.github.io/syRF/\">Home Page</a>";
    ui->label_links->setText(urls);
    ui->label_links->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_links->setOpenExternalLinks(true);
}

About::~About(){    
    delete ui;
}
