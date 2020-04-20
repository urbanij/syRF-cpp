/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sat Dec  7 11:36:08 CET 2019                     **
**  File:           mainwindow.cpp                              **
**  Description:                                                **
******************************************************************/

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
#include "y_parameters_data.h"


#include <iostream>


QString COMPLEX_REPR_RE_IM(complex_t c){
    if (c.imag() >= 0){
        return (QString::number(c.real()) + "+" + QString::number(c.imag()) + "j");
    }
    else {
        return (QString::number(c.real()) + "-" + QString::number(-c.imag()) + "j");
    }
}

QString COMPLEX_REPR_MAG_ARG(complex_t c){
#if USE_DEGREES
//    return (std::to_string(MAG(c)) << "∠" << std::to_string(ARG_DEG(c)) << " deg");
    return (QString::number(MAG(c)) + "∠" + QString::number(ARG_DEG(c)) + " deg");
#elif USE_RADIANS
    return (QString::number(MAG(c)) + "∠" + QString::number(ARG_RAD(c)) + " rad");
#endif
}


MainWindow::MainWindow( QWidget *parent) :
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
    #if DEBUG
        PRINT("===================================");
        system("clear");
    #endif

    // reads Y parameter inputs
    complex_t   y_i,
                y_f,
                y_r,
                y_o,
                y_s,
                y_l;


    if (ui->radiobutton_2n4957->isChecked()){
        // fetch data from y_parameters_data.h and auto-fill the y parameters input values

        float f0 = ui->f0_box_2->text().toFloat();
        #if DEBUG
            WATCH(f0);
        #endif


        if (f0 > 1500 || f0 < 45){
            // frequency out of range
            ui->statusBar->showMessage("Frequency out of range. Enter a frequency within the 45 - 1500 MHz range.");
            ui->statusBar->setStyleSheet("background-color: red; color: white;");
        } else {
            ui->statusBar->showMessage("");
            ui->statusBar->setStyleSheet("background-color: auto;");

            if (ui->radioButton_CE->isChecked()){
                ui->y_i_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_ie, f0),
                                get_value_from_dictionary(&b_ie, f0)
                            )
                        )
                );
                ui->y_f_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_fe, f0),
                                get_value_from_dictionary(&b_fe, f0)
                            )
                        )
                );
                ui->y_r_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_re, f0),
                                get_value_from_dictionary(&b_re, f0)
                            )
                        )
                );
                ui->y_o_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_oe, f0),
                                get_value_from_dictionary(&b_oe, f0)
                            )
                        )
                );

            }
            else if (ui->radioButton_CB->isChecked()){
                ui->y_i_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_ib, f0),
                                get_value_from_dictionary(&b_ib, f0)
                            )
                        )
                );
                ui->y_f_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_fb, f0),
                                get_value_from_dictionary(&b_fb, f0)
                            )
                        )
                );
                ui->y_r_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_rb, f0),
                                get_value_from_dictionary(&b_rb, f0)
                            )
                        )
                );
                ui->y_o_box_2->setText(
                        COMPLEX_REPR_RE_IM(
                            complex_t(
                                get_value_from_dictionary(&g_ob, f0),
                                get_value_from_dictionary(&b_ob, f0)
                            )
                        )
                );
            }

        }


    }
    else {
        // manually fill the y parameters values.

        if (! ui->y_i_box_2->text().isEmpty()){

            #define DUMBTEST 0
            #if DUMBTEST
            QString a = ui->y_i_box_2->text();
            std::string utf8_text = a.toUtf8().constData();
            WATCH(utf8_text);
            WATCH(ccomplex(utf8_text));
            WATCH(ccomplex(utf8_text).Re());
            WATCH(ccomplex(utf8_text).Im());
#endif

            y_i= complex_t (
                        ccomplex( ui->y_i_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_i_box_2->text().toStdString()).Im()
                        );



        } else {
            y_i = complex_t (0,0);  // INFINITY is the max value a float can hold
        }

        if (! ui->y_f_box_2->text().isEmpty()){
            y_f = complex_t (
                        ccomplex( ui->y_f_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_f_box_2->text().toStdString()).Im()
                        );
        } else {
            y_f = complex_t (0,0);
        }

        if (! ui->y_r_box_2->text().isEmpty()){
            y_r = complex_t (
                        ccomplex( ui->y_r_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_r_box_2->text().toStdString()).Im()
                        );
        } else {
            y_r = complex_t (0,0);
        }

        if (! ui->y_o_box_2->text().isEmpty()){
            y_o = complex_t (
                        ccomplex( ui->y_o_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_o_box_2->text().toStdString()).Im()
                        );
        } else {
            y_o = complex_t (0,0);
        }

        /// source and load
        if (! ui->y_s_box_2->text().isEmpty()){
            y_s = complex_t (
                    ccomplex( ui->y_s_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_s_box_2->text().toStdString()).Im()
                    );
        } else {
            y_s = complex_t (0,0);
        }

        if (! ui->y_L_box_2->text().isEmpty()){
             y_l = complex_t (
                        ccomplex( ui->y_L_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_L_box_2->text().toStdString()).Im()
                        );
        } else {
             y_l = complex_t (0,0);
        }
    }

    #if DEBUG
        WATCH(y_i);
        WATCH(y_f);
        WATCH(y_r);
        WATCH(y_o);
        WATCH(y_s);
        WATCH(y_l);
    #endif


    float       C       = compute_C(y_i,y_f,y_o,y_r);
    complex_t   betaA   = calculate_betaA(y_i,y_f,y_o,y_r, y_s, y_l);
    complex_t   y_in    = calculate_yin( y_i, y_f, y_o, y_r, y_l );
    complex_t   y_out   = calculate_yout( y_i, y_f, y_o, y_r, y_s);
    complex_t   A_V     = calculate_A_V(y_f, y_o, y_l);
    complex_t   vout_over_vs = calculate_vout_over_vs(y_i, y_f, y_o, y_r, y_s, y_l);
    float       G_A     = calculate_G_A(y_i, y_f, y_o, y_r, y_s);
    float       G_P     = calculate_G_P(y_i, y_f, y_o, y_r, y_l);
    float       G_T     = calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l);
    float       k       = calculate_k(y_i, y_f, y_o, y_r, y_s, y_l);
    complex_t   y_s_opt = calculate_y_s_opt(y_i, y_f, y_o, y_r );
    complex_t   y_l_opt = calculate_y_l_opt(y_i, y_f, y_o, y_r);


    #if DEBUG
        WATCH(C);
        WATCH(betaA);
        WATCH(y_in);
        WATCH(y_out);
        WATCH(A_V);
        WATCH(vout_over_vs);
        WATCH(G_A);
        WATCH(G_P);
        WATCH(G_T);
        WATCH(k);
        WATCH(y_s_opt);
        WATCH(y_l_opt);
    #endif

    /* displays output */
    ui->C_box_2->setText( QString::number(C));
    ui->beta_A_box_2->setText(
                            QString::number(MAG(betaA)) + "∠" +
                            QString::number(ARG_DEG(betaA)) + " deg"
                            );
    ui->y_in_box_2->setText(COMPLEX_REPR_RE_IM(y_in));
    ui->y_out_box_2->setText(COMPLEX_REPR_RE_IM(y_out));
    ui->A_V_box->setText(QString::number(MAG(A_V)));
    ui->vout_over_vs_box->setText(QString::number(MAG(vout_over_vs) ));
    ui->GA_box_2->setText(QString::number(G_A));
    ui->GA_box_dB_2->setText(QString::number( linear_2_dB(G_A)) );
    ui->GP_box_2->setText(QString::number(G_P ));
    ui->GP_box_dB_2->setText(QString::number( linear_2_dB(G_P)));
    ui->GT_box_2->setText(QString::number( G_T ));
    ui->GT_box_dB_2->setText(QString::number( linear_2_dB(G_T)));
    ui->k_box_3->setText(QString::number( k ));
    ui->y_s_opt_box_2->setText(COMPLEX_REPR_RE_IM(y_s_opt) );
    ui->y_L_opt_box_2->setText(COMPLEX_REPR_RE_IM(y_l_opt) );
}




void MainWindow::on_f0_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
    // go on manual after inserting the frequency
    ui->manual_input_y_radioButton->click();
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




void MainWindow::on_Calculate_button_5_clicked(){
    #if DEBUG
        PRINT("===================================");
        system("clear");
    #endif

    // reads S parameter inputs
    complex_t s11,
            s12,
            s21,
            s22;


    /* displays output */
    ui->D_box_2->setText( QString::number(2.23));
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
