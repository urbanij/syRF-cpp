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

#include "../syRF/ccomplex.h"

StubMatching::StubMatching(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StubMatching)
{
    ui->setupUi(this);


    ui->ZL_lineedit->setFocus();

    ui->parallel_stub_radioButton->setChecked(true);
    this->setWindowTitle("Parallel Stub Matching");

}

StubMatching::~StubMatching() {
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




void StubMatching::on_Calculate_button_clicked() {

    if (ui->parallel_stub_radioButton->isChecked()) {
        ui->Plot_impendace_admittance_button->setText("Plot Y(z)");
    }
    else if (ui->series_stub_radioButton->isChecked()) {
        ui->Plot_impendace_admittance_button->setText("Plot Z(z)");
    }


    if (ui->parallel_stub_radioButton->isChecked()) {
        this->setWindowTitle("Parallel Stub Matching");
    }
    else if (ui->series_stub_radioButton->isChecked()) {
        this->setWindowTitle("Series Stub Matching");
    }



    std::complex<double> ZL;
    double Z0;
    double Z0_stub;

    /// reading inputs ZL, Z0 and Z0_stub
    if (! ui->ZL_lineedit->text().isEmpty()) {
        ZL = std::complex<double> (
            (double) ccomplex(ui->ZL_lineedit->text().toStdString()).Re(),
            (double) ccomplex(ui->ZL_lineedit->text().toStdString()).Im()
        );
    } else {
        ZL = std::complex<double>(NAN, NAN);
    }

    Z0 = ui->Z0_lineedit->text().toDouble();
    Z0_stub = ui->Z0_stub_lineedit->text().toDouble();



    double d; // load-stub distance
    double l; // stup length

    d = (double) (ui->distance_horizontalScrollBar->value() * RANGE_SCROLLBAR / MAX_SCROLLBAR);
    // qInfo() << d ;
    l = (double) (ui->length_horizontalScrollBar->value() * RANGE_SCROLLBAR / MAX_SCROLLBAR);


    /// starts computing:

    std::complex<double> Zv1;
    std::complex<double> Zstub;
    std::complex<double> Zv2;

    /// ZV1 is the impedance seen from the TL at distance d from the load.
    Zv1 = Z0 * (ZL - std::complex<double>(0, 1) * Z0 * qTan(2*M_PI*-d)) / (Z0 - std::complex<double>(0, 1) * ZL * qTan(2*M_PI*-d));

    /// Zstub is the impedance seen from the line, into the stub.
    if (ui->OC_radioButton->isChecked()) {
        Zstub = std::complex<double>(0.0, -1.0) * Z0_stub / qTan(2*M_PI*l);
    } else {
        Zstub = std::complex<double>(0.0,  1.0) * Z0_stub * qTan(2*M_PI*l);
    }

    /// Zv2 is the composition between Zv1 and Zstub.
    if (ui->parallel_stub_radioButton->isChecked()) {
        if (Zstub == qInf()) {
            Zv2 = Zv1;
        } else {
            Zv2 = parallel(Zv1, Zstub);
        }
    }
    else if (ui->series_stub_radioButton->isChecked()) {
        Zv2 = Zv1 + Zstub;
    }


    std::complex<double> zv1 = Zv1/Z0;
    std::complex<double> Yv1 = std::complex<double>(1.0, 0.0) / Zv1;
    std::complex<double> yv1 = std::complex<double>(1.0, 0.0) / zv1;

    std::complex<double> zv2 = Zv2/Z0;
    std::complex<double> Yv2 = std::complex<double>(1.0, 0.0) / Zv2;
    std::complex<double> yv2 = std::complex<double>(1.0, 0.0) / zv2;



    /// displaying stuff

    ui->distance_lineedit->setText(QString::number(d));
    ui->length_lineedit->setText(QString::number(l));


    /*-------------------------------------------------*/

    ui->Zv1_lineedit->setText(complex_to_QString(Zv1));
    ui->zv1_lineedit->setText(complex_to_QString(zv1));

    ui->Yv1_lineedit->setText(complex_to_QString(Yv1));
    ui->yv1_lineedit->setText(complex_to_QString(yv1));

    /*-------------------------------------------------*/

    ui->Zv2_lineedit->setText(complex_to_QString(Zv2));
    ui->zv2_lineedit->setText(complex_to_QString(zv2));

    ui->Yv2_lineedit->setText(complex_to_QString(Yv2));
    ui->yv2_lineedit->setText(complex_to_QString(yv2));




    /* color stuff -- not a big deal but let's do it anyway... */

    const double THRESHOLD_OK_VAL = 0.05;
    if (ui->series_stub_radioButton->isChecked()) {
        if ( abs((zv1).real() - 1) < THRESHOLD_OK_VAL ) {
            ui->zv1_lineedit->setStyleSheet("color: green");
            ui->distance_lineedit->setStyleSheet("color: green");
        }
        else {
            ui->zv1_lineedit->setStyleSheet("color: red");
            ui->distance_lineedit->setStyleSheet("color: black");
        }
    }
    else if (ui->parallel_stub_radioButton->isChecked()) {
        ui->zv1_lineedit->setStyleSheet("color: black");
    }


    if (ui->parallel_stub_radioButton->isChecked()) {
        if ( abs(yv1.real() - 1) < THRESHOLD_OK_VAL ) {
            ui->yv1_lineedit->setStyleSheet("color: green");
            ui->distance_lineedit->setStyleSheet("color: green");
        }
        else {
            ui->yv1_lineedit->setStyleSheet("color: red");
            ui->distance_lineedit->setStyleSheet("color: black");
        }
    }
    else if (ui->series_stub_radioButton->isChecked()) {
        ui->yv1_lineedit->setStyleSheet("color: black");
    }


    if (ui->series_stub_radioButton->isChecked()) {
        if (abs(zv2.real() - 1) <= THRESHOLD_OK_VAL && abs(zv2.imag()) <= THRESHOLD_OK_VAL) {
            ui->zv2_lineedit->setStyleSheet("color: green");
            ui->length_lineedit->setStyleSheet("color: green");
        }
        else {
            ui->zv2_lineedit->setStyleSheet("color: red");
            ui->length_lineedit->setStyleSheet("color: black");
        }
    }
    else if (ui->parallel_stub_radioButton->isChecked()) {
        ui->zv2_lineedit->setStyleSheet("color: black");
    }


    if (ui->parallel_stub_radioButton->isChecked()) {
        if (abs(yv2.real() - 1) <= THRESHOLD_OK_VAL && abs(yv2.imag()) <= THRESHOLD_OK_VAL) {
            ui->yv2_lineedit->setStyleSheet("color: green");
            ui->length_lineedit->setStyleSheet("color: green");
        } 
        else {
            ui->yv2_lineedit->setStyleSheet("color: red");
            ui->length_lineedit->setStyleSheet("color: black");
        }
    }
    else if (ui->series_stub_radioButton->isChecked()) {
        ui->yv2_lineedit->setStyleSheet("color: black");
    }





}

void StubMatching::on_parallel_stub_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void StubMatching::on_series_stub_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void StubMatching::on_ZL_lineedit_returnPressed() {
    on_Calculate_button_clicked();
}

void StubMatching::on_Z0_stub_lineedit_returnPressed() {
    on_Calculate_button_clicked();
}

void StubMatching::on_OC_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void StubMatching::on_SC_radioButton_clicked() {
    on_Calculate_button_clicked();
}

void StubMatching::on_distance_horizontalScrollBar_valueChanged(int value) {
    on_Calculate_button_clicked();
}

void StubMatching::on_length_horizontalScrollBar_valueChanged(int value) {
    on_Calculate_button_clicked();
}
