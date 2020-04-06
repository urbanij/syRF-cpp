/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sat Dec  7 11:36:08 CET 2019                          **
**  File:           mainwindow.cpp                                        **                
**  Description:                                                          **
****************************************************************************/

#include <QMessageBox>
#include <QDesktopServices>
#include <QProcess>

#include <complex>
#include "ccomplex.h"
#include "y_parameters.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "about.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->f0_box_2->setFocus();
//    ui->radioButton_CE->toggle();
//    ui->checkBox->toggle();

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_open_datasheet_Y_button_clicked(){
//    QDesktopServices::openUrl(QUrl(":/new/docs/docs/datasheets/2N4957.pdf"));
    // QDesktopServices::openUrl(QUrl::fromLocalFile(".cpp"));

    QProcess *process = new QProcess(this);
    process->start(":/new/docs/docs/datasheets/2N4957.pdf");

}

void MainWindow::on_Calculate_button_4_clicked(){

    std::complex<float> yie = std::complex<float> (
                ccomplex( ui->y_i_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_i_box_2->text().toStdString()).Im()
                );

    std::complex<float> yfe = std::complex<float> (
                ccomplex( ui->y_f_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_f_box_2->text().toStdString()).Im()
                );

    std::complex<float> yre = std::complex<float> (
                ccomplex( ui->y_r_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_r_box_2->text().toStdString()).Im()
                );

    std::complex<float> yoe = std::complex<float> (
                ccomplex( ui->y_o_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_o_box_2->text().toStdString()).Im()
                );


    ui->C_box_2->setText(QString::number( compute_C(yie,yfe,yoe,yre)) );
}



void MainWindow::on_y_i_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}

void MainWindow::on_action_About_2_triggered(){
    About about;
    about.setModal(true);
    about.exec();
}



void MainWindow::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "syRF",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    resBtn != QMessageBox::Yes ? event->ignore() : event->accept();
}

