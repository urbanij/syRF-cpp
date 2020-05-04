/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sat May  2 19:51:32 CEST 2020                    **
**  File:           lumpedmatching.cpp                          **
**  Description:                                                **
******************************************************************/

#include "lumpedmatching.h"
#include "ui_lumpedmatching.h"
// #import "L_section_matching"


LumpedMatching::LumpedMatching(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LumpedMatching)
{
    ui->setupUi(this);
    this->setWindowTitle("Lumped parameters matching network");
}

LumpedMatching::~LumpedMatching()
{
    delete ui;
}

void LumpedMatching::on_Calculate_button_3_clicked(){


    
#if PRINT_TO_CONSOLE
    PRINT("===================================");
    system("clear");
#endif

    complex_t Yl, Y0, Zl, Z0;
    float f0;



// read load -- Zl or Yl
    if (ui->comboBox->currentText().toStdString() == "Admittance [mS]"){

        if (! ui->input_box->text().isEmpty()){
            Yl = complex_t (
                    (float) ccomplex( ui->input_box->text().toStdString()).Re(),
                    (float) ccomplex( ui->input_box->text().toStdString()).Im()
                );
            Yl *= 0.001; // to mS
        } else {
            Yl = complex_t(NAN, NAN);
        }

        Zl = ONE_COMPLEX / Yl;

    } else {
        // you're reading an impedance

        if (! ui->input_box->text().isEmpty()){
            Zl = complex_t (
                    (float) ccomplex( ui->input_box->text().toStdString()).Re(),
                    (float) ccomplex( ui->input_box->text().toStdString()).Im()
                );
        } else {
            Zl = complex_t(NAN, NAN);
        }

        Yl = ONE_COMPLEX / Zl;

    }

// read what you want to see -- Z0 or Y0
    if (ui->comboBox_2->currentText().toStdString() == "Admittance [mS]"){
    
        if (! ui->output_box->text().isEmpty()){
            Y0 = complex_t (
                    (float) ccomplex( ui->output_box->text().toStdString()).Re(),
                    (float) ccomplex( ui->output_box->text().toStdString()).Im()
                );
            Y0 *= 0.001; // to mS
        } else {
            Y0 = complex_t(NAN, NAN);
        }

        Z0 = ONE_COMPLEX / Y0;

    } else {
        // you're reading an impedance

        if (! ui->output_box->text().isEmpty()){
            Z0 = complex_t (
                    (float) ccomplex( ui->output_box->text().toStdString()).Re(),
                    (float) ccomplex( ui->output_box->text().toStdString()).Im()
                );
        } else {
            Z0 = complex_t(NAN, NAN);
        }

        Y0 = ONE_COMPLEX / Z0;

    }


// read frequency
    if (! ui->f0_box->text().isEmpty()){
        f0 = ui->f0_box->text().toFloat();
    } else {
        f0 = NAN;
    }


#if PRINT_TO_CONSOLE
    WATCH(Zl);
    WATCH(Z0);
    WATCH(Yl);
    WATCH(Y0);
    WATCH(f0);
#endif



    // ui->textBrowser->setText(L_section_matching(Zl, Z0, f0));


}






