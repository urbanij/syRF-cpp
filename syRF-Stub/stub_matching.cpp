/*****************************************************************
**                                                              **
**  syRF-Stub                                                   **
**  Copyright (C) 2020 Francesco Urbani                         **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Fri Nov 13 2020 09:50:02 am CET                  **
**  File:           stub_matching.cpp                           **
**  Description:                                                **
******************************************************************/

#include "stub_matching.h"
#include "ui_stub_matching.h"

#include <QString>
#include <QDebug>
#include <QtMath>

#include <complex>
#include <iostream>

#include "../syRF/ccomplex.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}



const double RANGE_SCROLLBAR = 0.5;
const double MAX_SCROLLBAR   = 1000.0;

/******************************************************/
QString complex_to_QString(const std::complex<double>& c) {
    if (c.imag() >= 0){
        return (QString::number(c.real()) + "+" + QString::number(c.imag()) + "j");
    }
    else {
        return (QString::number(c.real()) + "-" + QString::number(-c.imag()) + "j");
    }
}


std::complex<double> parallel(const std::complex<double>& z1, const std::complex<double>& z2) {
    return (z1*z2)/(z1+z2);
}




/******************************************************/



void MainWindow::on_Calculate_button_clicked() {

    std::complex<double> ZL;
    double Z0;
    double Z0_stub;

    /// reading inputs ZL, Z0 and Z0_stub
    if (! ui->ZL_lineedit->text().isEmpty()) {
        ZL = std::complex<double> (
                    (float) ccomplex( ui->ZL_lineedit->text().toStdString()).Re(),
                    (float) ccomplex( ui->ZL_lineedit->text().toStdString()).Im()
                    );
    } else {
        ZL = std::complex<double>(NAN, NAN);
    }

    Z0 = ui->Z0_lineedit->text().toDouble();
    Z0_stub = ui->Z0_stub_lineedit->text().toDouble();


    double d; // load-stub distance
    double l; // stup length

    d = (double) (ui->distance_horizontalScrollBar->value() *RANGE_SCROLLBAR/MAX_SCROLLBAR);
    l = (double) (ui->length_horizontalScrollBar->value() *RANGE_SCROLLBAR/MAX_SCROLLBAR);

    ui->distance_lineedit->setText(QString::number(d));
    ui->length_lineedit->setText(QString::number(l));



    std::complex<double> Zv1;


    Zv1 = Z0 * (ZL - std::complex<double>(0, 1) * Z0 * qTan(2*M_PI*-d)) / (Z0 - std::complex<double>(0, 1) * ZL * qTan(2*M_PI*-d));






    ui->Zv1_lineedit->setText(complex_to_QString(Zv1));
}

void MainWindow::on_parallel_stub_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void MainWindow::on_series_stub_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void MainWindow::on_ZL_lineedit_returnPressed() {
    on_Calculate_button_clicked();
}

void MainWindow::on_Z0_stub_lineedit_returnPressed() {
    on_Calculate_button_clicked();
}

void MainWindow::on_OC_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void MainWindow::on_SC_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void MainWindow::on_distance_horizontalScrollBar_sliderMoved(int position) {
    on_Calculate_button_clicked();
}

void MainWindow::on_length_horizontalScrollBar_sliderMoved(int position) {
    on_Calculate_button_clicked();
}
