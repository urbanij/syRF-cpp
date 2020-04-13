/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019-2020 Francesco Urbani                              **
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
#include <QMainWindow>

#include <complex>
#include <typeinfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "about.h"

#include "config.h"
#include "utils.h"

#include "ccomplex.h"
#include "y_parameters.h"

#include <iostream>


QString COMPLEX_REPR_RE_IM(std::complex<float> c){
    if (c.imag() >= 0){
        return (QString::number(c.real()) + "+" + QString::number(c.imag()) + "j");
    }
    else {
        return (QString::number(c.real()) + "-" + QString::number(-c.imag()) + "j");
    }
}

QString COMPLEX_REPR_MAG_ARG(std::complex<float> c){
#if USE_DEGREES
//    return (std::to_string(MAG(c)) << "∠" << std::to_string(ARG_DEG(c)) << " deg");
    return (QString::number(MAG(c)) + "∠" + QString::number(ARG_DEG(c)) + " deg");
#elif USE_RADIANS
    return (QString::number(MAG(c)) + "∠" + QString::number(ARG_RAD(c)) + " rad");
#endif
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->f0_box_2->setFocus();
    ui->radiobutton_2n4957->setChecked(true);
        ui->y_i_box_2->setEnabled(false);
        ui->y_f_box_2->setEnabled(false);
        ui->y_o_box_2->setEnabled(false);
        ui->y_r_box_2->setEnabled(false);
        
    ui->radioButton_CE->setChecked(true);

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

    if (ui->radiobutton_2n4957->isChecked()){
        PRINT("A");
    }
    else {
        PRINT("B");
    }




    // reads inputs
    std::complex<float> y_i,
                        y_f,
                        y_r,
                        y_o,
                        y_s,
                        y_l;

    if (! ui->y_i_box_2->text().isEmpty()){
        y_i= std::complex<float> (
                    ccomplex( ui->y_i_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_i_box_2->text().toStdString()).Im()
                    );
    } else {
        y_i = std::complex<float> (0,0);  // INFINITY is the max value a float can hold
    }

    if (! ui->y_f_box_2->text().isEmpty()){
        y_f = std::complex<float> (
                    ccomplex( ui->y_f_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_f_box_2->text().toStdString()).Im()
                    );
    } else {
        y_f = std::complex<float> (0,0);
    }

    if (! ui->y_r_box_2->text().isEmpty()){
        y_r = std::complex<float> (
                    ccomplex( ui->y_r_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_r_box_2->text().toStdString()).Im()
                    );
    } else {
        y_r = std::complex<float> (0,0);
    }

    if (! ui->y_o_box_2->text().isEmpty()){
        y_o = std::complex<float> (
                    ccomplex( ui->y_o_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_o_box_2->text().toStdString()).Im()
                    );
    } else {
        y_o = std::complex<float> (0,0);
    }

    /// source and load
    if (! ui->y_s_box_2->text().isEmpty()){
        y_s = std::complex<float> (
                ccomplex( ui->y_s_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_s_box_2->text().toStdString()).Im()
                );
    } else {
        y_s = std::complex<float> (0,0);
    }

    if (! ui->y_L_box_2->text().isEmpty()){
         y_l = std::complex<float> (
                    ccomplex( ui->y_L_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_L_box_2->text().toStdString()).Im()
                    );
    } else {
         y_l = std::complex<float> (0,0);
    }



    /* displays output */
    ui->C_box_2->setText(QString::number( compute_C(y_i,y_f,y_o,y_r)) );
    ui->beta_A_box_2->setText(
                    QString::number(MAG(calculate_betaA(y_i,y_f,y_o,y_r, y_s, y_l))) + "∠" +
                    QString::number(ARG_DEG(calculate_betaA(y_i,y_f,y_o,y_r, y_s, y_l))) + " deg"
                    );
    ui->y_in_box_2->setText( COMPLEX_REPR_RE_IM(calculate_yin( y_i, y_f, y_o, y_r, y_l )) );

//    WATCH(calculate_yin( y_i, y_f, y_o, y_r, y_l ));
//    WATCH(calculate_betaA( y_i, y_f, y_o, y_r, y_s, y_l ));
//    WATCH(y_l);

    ui->y_out_box_2->setText( COMPLEX_REPR_RE_IM(calculate_yout( y_i, y_f, y_o, y_r, y_s) ));
    ui->A_V_box->setText(QString::number( MAG(calculate_A_V(y_f, y_o, y_l)) ));
    ui->vout_over_vs_box->setText(QString::number( MAG(calculate_vout_over_vs(y_i, y_f, y_o, y_r, y_s, y_l)) ));
    ui->GA_box_2->setText(QString::number( calculate_G_A(y_i, y_f, y_o, y_r, y_s)) );
    ui->GA_box_dB_2->setText(QString::number( linear_2_dB(calculate_G_A(y_i, y_f, y_o, y_r, y_s))) );
    ui->GP_box_2->setText(QString::number( calculate_G_P(y_i, y_f, y_o, y_r, y_l) ));
    ui->GP_box_dB_2->setText(QString::number( linear_2_dB(calculate_G_P(y_i, y_f, y_o, y_r, y_l) )));
    ui->GT_box_2->setText(QString::number( calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l) ));
    ui->GT_box_dB_2->setText(QString::number( linear_2_dB(calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l) )));
    ui->k_box_3->setText(QString::number( calculate_k(y_i, y_f, y_o, y_r, y_s, y_l) ));
    ui->y_s_opt_box_2->setText( COMPLEX_REPR_RE_IM(calculate_y_s_opt(y_i, y_f, y_o, y_r )) );
    ui->y_L_opt_box_2->setText( COMPLEX_REPR_RE_IM(calculate_y_l_opt( y_i, y_f, y_o, y_r )) );


}



void MainWindow::on_y_i_box_2_returnPressed(){on_Calculate_button_4_clicked();}
void MainWindow::on_y_f_box_2_returnPressed(){on_Calculate_button_4_clicked();}
void MainWindow::on_y_r_box_2_returnPressed(){on_Calculate_button_4_clicked();}
void MainWindow::on_y_o_box_2_returnPressed(){on_Calculate_button_4_clicked();}
void MainWindow::on_y_s_box_2_returnPressed(){on_Calculate_button_4_clicked();}
void MainWindow::on_y_L_box_2_returnPressed(){on_Calculate_button_4_clicked();}

void MainWindow::on_radioButton_CE_clicked(){
    ui->radiobutton_2n4957->setText("2N4957 (Common Emitter config.)");
    ui->show_plots_button->setText("Show C.E. Y parameters plots");
    ui->label_20->setText("Y<sub>ie</sub>");
    ui->label_81->setText("Y<sub>fe</sub>");
    ui->label_79->setText("Y<sub>oe</sub>");
    ui->label_78->setText("Y<sub>re</sub>");
    ui->label_165->setText("V<sub>CE</sub>");
    on_Calculate_button_4_clicked();
}
void MainWindow::on_radioButton_CB_clicked(){
    ui->radiobutton_2n4957->setText("2N4957 (Common Base config.)");
    ui->show_plots_button->setText("Show C.B. Y parameters plots");
    ui->label_20->setText("Y<sub>ib</sub>");
    ui->label_81->setText("Y<sub>fb</sub>");
    ui->label_79->setText("Y<sub>ob</sub>");
    ui->label_78->setText("Y<sub>rb</sub>");
    ui->label_165->setText("V<sub>CB</sub>");
    on_Calculate_button_4_clicked();
}
void MainWindow::on_radiobutton_2n4957_clicked(){
    ui->label_165->setEnabled(true);
    ui->label_166->setEnabled(true);
    ui->label_118->setEnabled(true);
    ui->label_37->setEnabled(true);
    ui->label_38->setEnabled(true);
    ui->label_8->setEnabled(true);
    ui->radioButton_CE->setEnabled(true);
    ui->radioButton_CB->setEnabled(true);
    ui->f0_box_2->setEnabled(true);
    ui->y_i_box_2->setEnabled(false);
    ui->y_f_box_2->setEnabled(false);
    ui->y_o_box_2->setEnabled(false);
    ui->y_r_box_2->setEnabled(false);

    ui->f0_box_2->setFocus();
    on_Calculate_button_4_clicked();
}
void MainWindow::on_manual_input_y_radioButton_clicked(){
    
    ui->label_165->setEnabled(false);
    ui->label_166->setEnabled(false);
    ui->label_118->setEnabled(false);
    ui->label_37->setEnabled(false);
    ui->label_38->setEnabled(false);
    ui->label_8->setEnabled(false);
    ui->radioButton_CE->setEnabled(false);
    ui->radioButton_CB->setEnabled(false);
    ui->f0_box_2->setEnabled(false);
    ui->y_i_box_2->setEnabled(true);
    ui->y_f_box_2->setEnabled(true);
    ui->y_o_box_2->setEnabled(true);
    ui->y_r_box_2->setEnabled(true);

    ui->label_20->setText("Y<sub>i</sub>");
    ui->label_81->setText("Y<sub>f</sub>");
    ui->label_79->setText("Y<sub>o</sub>");
    ui->label_78->setText("Y<sub>r</sub>");
    ui->label_165->setText("V<sub>CE</sub>");

    ui->y_i_box_2->setFocus();
    on_Calculate_button_4_clicked();
}



void MainWindow::on_action_About_2_triggered(){
    About about;
    about.setModal(true);
    about.exec();
}



void MainWindow::closeEvent (QCloseEvent *event){
#if !DEBUG
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "syRF",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    resBtn != QMessageBox::Yes ? event->ignore() : event->accept();

#endif
}


