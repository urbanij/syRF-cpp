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


#include <QDesktopServices>
#include <QProcess>
#include <QMainWindow>

#include <complex>
#include <typeinfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"

///////// other windows
#include "about.h"
#include "lumpedmatching.h"
#include "../syRF-Stub/stub_matching.h"
/////////


#include "config.h"
#include "utils.h"

#include "ccomplex.h"
#include "y_parameters.h"
#include "y_parameters_data.h"


#include "s_parameters.h"
#include "s_parameters_data.h"


#include <iostream>


std::string COMPLEX_REPR_RE_IM_console(complex_t c) {
    if (c.imag() >= 0){
        return (std::to_string(c.real()) + "+" + std::to_string(c.imag()) + "j");
    }
    else {
        return (std::to_string(c.real()) + "-" + std::to_string(-c.imag()) + "j");
    }
}

QString COMPLEX_REPR_RE_IM(complex_t c) {
    if (c.imag() >= 0){
        return (QString::number(c.real()) + "+" + QString::number(c.imag()) + "j");
    }
    else {
        return (QString::number(c.real()) + "-" + QString::number(-c.imag()) + "j");
    }
}

QString COMPLEX_REPR_MAG_ARG(complex_t c) {
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

    /////////////
    ///// Y /////
    ui->f0_box_2->setFocus();
    ui->radiobutton_2n4957->setChecked(true);
            ui->y_i_box_2->setReadOnly(true);
            ui->y_f_box_2->setReadOnly(true);
            ui->y_o_box_2->setReadOnly(true);
            ui->y_r_box_2->setReadOnly(true);

    ui->radiobutton_2n4957->setChecked(true);
    ui->radioButton_CE->setChecked(true);

    /////////////
    ///// S /////

    ui->radioButton1_MRF571->setChecked(true);
            ui->s11_box->setReadOnly(true);
            ui->s11_box_arg->setReadOnly(true);
            ui->s12_box->setReadOnly(true);
            ui->s12_box_arg->setReadOnly(true);
            ui->s21_box->setReadOnly(true);
            ui->s21_box_arg->setReadOnly(true);
            ui->s22_box->setReadOnly(true);
            ui->s22_box_arg->setReadOnly(true);

            ui->NFmindb_box_2->setReadOnly(true);
            ui->rn_box_2->setReadOnly(true);
            ui->gamma_s_on_box->setReadOnly(true);
            ui->gamma_s_on_box_2->setReadOnly(true);



    ui->radioButton_input_as_Z->setChecked(true);
            ui->label_250->setEnabled(false);
            ui->ZS_box_2->setEnabled(false);
            ui->label_257->setEnabled(false);
            ui->ZS_box_5->setEnabled(false);
            ui->label_264->setEnabled(false);
            ui->ZS_box_4->setEnabled(false);
            ui->label_265->setEnabled(false);
            ui->ZS_box_3->setEnabled(false);



    this->setWindowTitle("syRF");
    this->setWindowModified(false);

}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_open_datasheet_Y_button_clicked() {
#if 0
    std::cout << "trying to open the 2n4957 datasheet" << '\n';
#endif

//    QDesktopServices::openUrl(QUrl("qrc:/2N4957.pdf"));

//    QFile HelpFile("qrc:/new/docs/docs/datasheets/2N4957.pdf");
//    HelpFile.copy(qApp->applicationDirPath().append("/2N4957.pdf"));

    // could open the PDF from local resource so I went this route instead which works pretty alright.
    QDesktopServices::openUrl(QUrl(URL_2N4957));


    //QProcess *process = new QProcess(this);
    //process->start(":/new/docs/docs/datasheets/2N4957.pdf");

}



void MainWindow::on_Calculate_button_4_clicked() {
    #if PRINT_TO_CONSOLE
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

        double f0 = ui->f0_box_2->text().toFloat();
        #if PRINT_TO_CONSOLE
            WATCH(f0);
            std::cout << "\n";
        #endif


        /** radio button is checked meaning: i've choosen to use my 2N4957 transistor
         *  and i'm going to use it data which will be retrieved from `y_parameters_data.h` file.
         *
         *  First off: fill the boxes with the values, and
         *  second:    assign the values to the variables.
         */


        if (f0 > 1500 || f0 < 45){
            // display out of range frequency error message in the status bar at the bottom.
            ui->statusBar->showMessage("Frequency out of range. Enter a frequency within the 45 - 1500 MHz range.");
            ui->statusBar->setStyleSheet("background-color: red; color: white;");
        } else {
            ui->statusBar->showMessage("");
            ui->statusBar->setStyleSheet("background-color: auto;");

            if (ui->radioButton_CE->isChecked()){

                y_i = complex_t(get_value_from_dictionary(g_ie, f0),
                                get_value_from_dictionary(b_ie, f0));
                y_f = complex_t(get_value_from_dictionary(g_fe, f0),
                                get_value_from_dictionary(b_fe, f0));
                y_r = complex_t(get_value_from_dictionary(g_re, f0),
                                get_value_from_dictionary(b_re, f0));
                y_o = complex_t(get_value_from_dictionary(g_oe, f0),
                                get_value_from_dictionary(b_oe, f0));
            }

            else if (ui->radioButton_CB->isChecked()){

                y_i = complex_t(get_value_from_dictionary(g_ib, f0),
                                get_value_from_dictionary(b_ib, f0));
                y_f = complex_t(get_value_from_dictionary(g_fb, f0),
                                get_value_from_dictionary(b_fb, f0));
                y_r = complex_t(get_value_from_dictionary(g_rb, f0),
                                get_value_from_dictionary(b_rb, f0));
                y_o = complex_t(get_value_from_dictionary(g_ob, f0),
                                get_value_from_dictionary(b_ob, f0));
            }

            ui->y_i_box_2->setText(COMPLEX_REPR_RE_IM(y_i));
            ui->y_f_box_2->setText(COMPLEX_REPR_RE_IM(y_f));
            ui->y_r_box_2->setText(COMPLEX_REPR_RE_IM(y_r));
            ui->y_o_box_2->setText(COMPLEX_REPR_RE_IM(y_o));

        }


    }
    else {
        // manually fill the y parameters values.

        if (! ui->y_i_box_2->text().isEmpty()){
            y_i= complex_t (
                        (double) ccomplex( ui->y_i_box_2->text().toStdString()).Re(),
                        (double) ccomplex( ui->y_i_box_2->text().toStdString()).Im()
                        );
        } else {
            y_i = complex_t(NAN, NAN); // complex_t (0,0);  // INFINITY is the max value a double can hold
        }

        if (! ui->y_f_box_2->text().isEmpty()){
            y_f = complex_t (
                        (double) ccomplex( ui->y_f_box_2->text().toStdString()).Re(),
                        (double) ccomplex( ui->y_f_box_2->text().toStdString()).Im()
                        );
        } else {
            y_f = complex_t(NAN, NAN); // complex_t (0,0);
        }

        if (! ui->y_r_box_2->text().isEmpty()){
            y_r = complex_t (
                        (double) ccomplex( ui->y_r_box_2->text().toStdString()).Re(),
                        (double) ccomplex( ui->y_r_box_2->text().toStdString()).Im()
                        );
        } else {
            y_r = complex_t(NAN, NAN); // complex_t (0,0);
        }

        if (! ui->y_o_box_2->text().isEmpty()){
            y_o = complex_t (
                        (double) ccomplex( ui->y_o_box_2->text().toStdString()).Re(),
                        (double) ccomplex( ui->y_o_box_2->text().toStdString()).Im()
                        );
        } else {
            y_o = complex_t(NAN, NAN); // complex_t (0,0);
        }

    }

    /// read source and load values
    if (! ui->y_s_box_2->text().isEmpty()){
        y_s = complex_t (
                ccomplex( ui->y_s_box_2->text().toStdString()).Re(),
                ccomplex( ui->y_s_box_2->text().toStdString()).Im()
                );
    } else {
        y_s = complex_t(NAN, NAN); // complex_t (0,0);
    }

    if (! ui->y_L_box_2->text().isEmpty()){
         y_l = complex_t (
                    ccomplex( ui->y_L_box_2->text().toStdString()).Re(),
                    ccomplex( ui->y_L_box_2->text().toStdString()).Im()
                    );
    } else {
         y_l = complex_t(NAN, NAN); // complex_t (0,0);
    }



    #if PRINT_TO_CONSOLE
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_i = " << COMPLEX_REPR_RE_IM_console(y_i) << "\t == " << MAG(y_i) << "∠" << ARG_DEG(y_i) << " deg" << "\n";
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_f = " << COMPLEX_REPR_RE_IM_console(y_f) << "\t == " << MAG(y_f) << "∠" << ARG_DEG(y_f) << " deg" << "\n";
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_r = " << COMPLEX_REPR_RE_IM_console(y_r) << "\t == " << MAG(y_r) << "∠" << ARG_DEG(y_r) << " deg" << "\n";
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_o = " << COMPLEX_REPR_RE_IM_console(y_o) << "\t == " << MAG(y_o) << "∠" << ARG_DEG(y_o) << " deg" << "\n";
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_s = " << COMPLEX_REPR_RE_IM_console(y_s) << "\t == " << MAG(y_s) << "∠" << ARG_DEG(y_s) << " deg" << "\n";
        std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_l = " << COMPLEX_REPR_RE_IM_console(y_l) << "\t == " << MAG(y_l) << "∠" << ARG_DEG(y_l) << " deg" << "\n";
        std::cout << "\n";
    #endif


    // compute actual stuff

    double       C       = compute_C(y_i,y_f,y_o,y_r);
    complex_t   betaA   = calculate_betaA(y_i,y_f,y_o,y_r, y_s, y_l);
    complex_t   y_in    = calculate_yin( y_i, y_f, y_o, y_r, y_l );
    complex_t   y_out   = calculate_yout( y_i, y_f, y_o, y_r, y_s);
    complex_t   A_V     = calculate_A_V(y_f, y_o, y_l);
    complex_t   vout_over_vs = calculate_vout_over_vs(y_i, y_f, y_o, y_r, y_s, y_l);
    
    double       G_A     = calculate_G_A(y_i, y_f, y_o, y_r, y_s);
    double       G_P     = calculate_G_P(y_i, y_f, y_o, y_r, y_l);
    double       G_T     = calculate_G_T(y_i, y_f, y_o, y_r, y_s, y_l);

    double       k       = calculate_k(y_i, y_f, y_o, y_r, y_s, y_l);
    complex_t   y_s_opt = calculate_y_s_opt(y_i, y_f, y_o, y_r );
    complex_t   y_l_opt = calculate_y_l_opt(y_i, y_f, y_o, y_r);

    double       G_A_max = calculate_G_A(y_i, y_f, y_o, y_r, y_s_opt);
    double       G_P_max = calculate_G_P(y_i, y_f, y_o, y_r, y_l_opt);
    double       G_T_max = calculate_G_T(y_i, y_f, y_o, y_r, y_s_opt, y_l_opt);
    



#if PRINT_TO_CONSOLE
    WATCH(C);
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "betaA = " << COMPLEX_REPR_RE_IM_console(betaA) << "\t == " << MAG(betaA) << "∠" << ARG_DEG(betaA) << " deg" << "\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_in = " << COMPLEX_REPR_RE_IM_console(y_in) << "\t == " << MAG(y_in) << "∠" << ARG_DEG(y_in) << " deg" << "\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "A_V = " << COMPLEX_REPR_RE_IM_console(A_V) << "\t == " << MAG(A_V) << "∠" << ARG_DEG(A_V) << " deg" << "\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "vout_over_vs = " << COMPLEX_REPR_RE_IM_console(vout_over_vs) << "\t == " << MAG(vout_over_vs) << "∠" << ARG_DEG(vout_over_vs) << " deg" << "\n";
    std::cout << "\n";

    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_A = " << G_A << "\t == " << linear_2_dB(G_A) << " dB\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_P = " << G_P << "\t == " << linear_2_dB(G_P) << " dB\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_T = " << G_T << "\t == " << linear_2_dB(G_T) << " dB\n";

    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_A_max = " << G_A_max << "\t == " << linear_2_dB(G_A_max) << " dB\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_P_max = " << G_P_max << "\t == " << linear_2_dB(G_P_max) << " dB\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "G_T_max = " << G_T_max << "\t == " << linear_2_dB(G_T_max) << " dB\n";
    std::cout << "\n";

    WATCH(k);
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_s_opt = " << COMPLEX_REPR_RE_IM_console(y_s_opt) << "\t == " << MAG(y_s_opt) << "∠" << ARG_DEG(y_s_opt) << " deg" << "\n";
    std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "y_l_opt = " << COMPLEX_REPR_RE_IM_console(y_l_opt) << "\t == " << MAG(y_l_opt) << "∠" << ARG_DEG(y_l_opt) << " deg" << "\n";
#endif


    ui->C_box_2->setText(QString::number(C));    

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
        
    ui->k_box_3->setText(QString::number(k));
    
    ui->y_s_opt_box_2->setText(COMPLEX_REPR_RE_IM(y_s_opt) );
    ui->y_L_opt_box_2->setText(COMPLEX_REPR_RE_IM(y_l_opt) );
    

    #define PUS_LABEL       "<i><font color=" ORANGE ">Potentially unstable system</font></i>"
    #define USS_LABEL       "<i><font color=" GREEN ">Unconditionally stable system</font></i>"

    #define  SS_LABEL       "<font color=" GREEN ">Stable system</font>"
    #define  US_LABEL       "<font color=" RED ">Unstable system</font>"

    
    /*
    **                \k | <1 |  >1 | nan
    **               C|--+----+-----+------ 
    **                |    
    **     between 0-1|    U    S      US
    **          1     |    U    S      MS
    ** not between 0-1|    U    S      PU
    **                |
    **
    **     U: unstable
    **     S: stable
    **    US: unconditionally stable
    **    PS: potentially unstable
    **    MS: marginally stable
    */
    

    std::string stability_status;

    if (std::isnan(C)){
        ui->C_box_2->setStyleSheet(styleSheet());
        ui->k_box_3->setStyleSheet(styleSheet());
        stability_status = "";
    }
    else if (std::isnan(k)){
        if (C < 0.0 || C>1.0){
            stability_status = PUS_LABEL;
            ui->C_box_2->setStyleSheet("border: 0.1ex solid " ORANGE);
        }
        else if (C > 0.0 && C<1.0){
            stability_status = USS_LABEL;
            ui->C_box_2->setStyleSheet("border: 0.1ex solid " GREEN);
        }else{
            // C == 1.0
            stability_status = "<i><font color=orange>Marginally stable system</font></i>";
            ui->C_box_2->setStyleSheet("border: 0.1ex solid " ORANGE);
        }
    }
    else {
        if (k>1.0){
            stability_status = SS_LABEL;
            ui->k_box_3->setStyleSheet("border: 0.1ex solid " GREEN);
        } else {
            stability_status = US_LABEL;
            ui->k_box_3->setStyleSheet("border: 0.1ex solid " RED);
        }
    }
    
    ui->label_Y_tab->setText(QString::fromStdString(stability_status));

    
    this->setWindowTitle("syRF");
    this->setWindowModified(false);
}



void MainWindow::on_f0_box_2_textEdited(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}
void MainWindow::on_f0_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
    /* go on manual after inserting the frequency */
    // ui->manual_input_y_radioButton->click();
}




void MainWindow::on_y_i_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_i_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_f_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_f_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_r_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_r_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_o_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_o_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_s_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_s_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_L_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_L_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


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
    

    // ui->y_i_box_2->setEnabled(false);
    // ui->y_f_box_2->setEnabled(false);
    // ui->y_o_box_2->setEnabled(false);
    // ui->y_r_box_2->setEnabled(false);

    ui->y_i_box_2->setReadOnly(true);
    ui->y_f_box_2->setReadOnly(true);
    ui->y_o_box_2->setReadOnly(true);
    ui->y_r_box_2->setReadOnly(true);

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


    // ui->y_i_box_2->setEnabled(true);
    // ui->y_f_box_2->setEnabled(true);
    // ui->y_o_box_2->setEnabled(true);
    // ui->y_r_box_2->setEnabled(true);

    ui->y_i_box_2->setReadOnly(false);
    ui->y_f_box_2->setReadOnly(false);
    ui->y_o_box_2->setReadOnly(false);
    ui->y_r_box_2->setReadOnly(false);

    ui->label_20->setText("Y<sub>i</sub>");
    ui->label_81->setText("Y<sub>f</sub>");
    ui->label_79->setText("Y<sub>o</sub>");
    ui->label_78->setText("Y<sub>r</sub>");
    ui->label_165->setText("V<sub>CE</sub>");

    ui->y_i_box_2->setFocus();

    on_Calculate_button_4_clicked();
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


struct S_tab_data {
    complex_t   Cs;
    double       rs;
    complex_t   Cl;
    double       rl;
    complex_t   gamma_in;
    complex_t   gamma_out;
    complex_t   gamma_L;
    complex_t   gamma_S;
    double       GA_dB;
    complex_t   Ca;
    double       ra;
    double       NF_dB;
    complex_t   Cnf;
    double       rnf;
    double       GT_dB;
    complex_t   Ct;
    double       rt;
    double       GP_dB;
    complex_t   Cp;
    double       rp;
    complex_t   constant_gamma_circle;
    complex_t   ZS;
    complex_t   ZL;
    complex_t   Z0;
    complex_t   gamma_S_visualized;
    complex_t   gamma_L_visualized;

    std::string label_gamma_inout;
    double       vce;
    double       ic;
    double       f;
    std::string bjt;
};
// gloabal 
struct S_tab_data Sdata = {};




void MainWindow::on_Calculate_button_5_clicked(){
    
#if PRINT_TO_CONSOLE
        PRINT("===================================");
        system("clear");
#endif

    // these variables will hold the value of the s parameters
    std::complex<double>    s11,        // complex_t is an alias for std::complex<double>        
                            s12,
                            s21,
                            s22;
    
    std::pair<double,double>  s11_polar,  // could have used its alias S_parameter_t
                            s12_polar,
                            s21_polar,
                            s22_polar;

    complex_t zs;
    complex_t zl;
    complex_t gamma_s;
    complex_t gamma_l;

    double z0;


    double NFmin_db;
    double Rn;
    complex_t gamma_s_on;
    complex_t z_s_on;




    if (ui->radioButton1_MRF571->isChecked()){

        std::string combobox_entry = ui->comboBox_MRF_bias->currentText().toStdString();

        WATCH(combobox_entry);

        if (combobox_entry != ""){

            std::string transistor_name;
            int         Vce;
            int         Ic;
            int         f0;
            filter_S_transistor_bias_settings(combobox_entry, transistor_name, Vce, Ic, f0);



            s11_polar = std::make_pair(
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s11"].first,    // mag
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s11"].second    // phase in deg
                        );

            s12_polar = std::make_pair(
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s12"].first,
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s12"].second
                        );

            s21_polar = std::make_pair(
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s21"].first,
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s21"].second
                        );

            s22_polar = std::make_pair(
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s22"].first,
                            MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s22"].second
                        );


            s11 = polar_2_rect(s11_polar.first, DEG_2_RAD(s11_polar.second));
            s12 = polar_2_rect(s12_polar.first, DEG_2_RAD(s12_polar.second));
            s21 = polar_2_rect(s21_polar.first, DEG_2_RAD(s21_polar.second));
            s22 = polar_2_rect(s22_polar.first, DEG_2_RAD(s22_polar.second));


            // fill noise parameters if they are available
            if ( Vce == 6.0 && Ic == 5.0 && (f0 == 500.0 || f0 == 1000.0) ){
                // noise parameters are given by the datasheet, just do
                // ahead and retrieve them from `s_parameters_data.h`.
                // prevent the fields from being editable.
                ui->NFmindb_box_2->setReadOnly(true);
                ui->rn_box_2->setReadOnly(true);
                ui->gamma_s_on_box->setReadOnly(true);
                ui->gamma_s_on_box_2->setReadOnly(true);


                NFmin_db =   MRF_transistor_noise_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["NF_opt_db"];
                Rn =         MRF_transistor_noise_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["R_n"];
                gamma_s_on = polar_2_rect(
                            MRF_transistor_noise_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["Gamma_S_on_mag"],
                            DEG_2_RAD(MRF_transistor_noise_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["Gamma_S_on_arg"])
                        );

                

                // fill noise parameters
                ui->NFmindb_box_2->setText(QString::number(NFmin_db));
                ui->rn_box_2->setText(QString::number(Rn));
                ui->gamma_s_on_box->setText(QString::number(MAG(gamma_s_on)));
                ui->gamma_s_on_box_2->setText(QString::number(ARG_DEG(gamma_s_on)));

                WATCH(gamma_s_on);
                WATCH(MAG(gamma_s_on));
                WATCH(ARG_DEG(gamma_s_on));

            }
            else {
                // custom mode (i.e. data from combobox) but noise parameters missing from datasheet
                // not given from the datasheet hence make those fields editable.

                // clean the fields first
#if 0
                ui->NFmindb_box_2->setText("");
                ui->rn_box_2->setText("");
                ui->gamma_s_on_box->setText("");
                ui->gamma_s_on_box_2->setText("");
#endif

                ui->NFmindb_box_2->setReadOnly(false);
                ui->rn_box_2->setReadOnly(false);
                ui->gamma_s_on_box->setReadOnly(false);
                ui->gamma_s_on_box_2->setReadOnly(false);

                if (!ui->NFmindb_box_2->text().isEmpty()){
                    NFmin_db = ui->NFmindb_box_2->text().toFloat();
                } else {
                    NFmin_db = NAN;
                }
                if (!ui->rn_box_2->text().isEmpty()){
                    Rn = ui->rn_box_2->text().toFloat();
                } else {
                    Rn = NAN;
                }
                if (!ui->gamma_s_on_box->text().isEmpty() && !ui->gamma_s_on_box_2->text().isEmpty()){
                    gamma_s_on = polar_2_rect(ui->gamma_s_on_box->text().toFloat(),
                                              DEG_2_RAD(ui->gamma_s_on_box_2->text().toFloat())
                                              );
                    
                }else {
                    gamma_s_on = complex_t(NAN, NAN);

                }

            }


#if 0
            WATCH(s11.real() << " " << s11.imag() << " | " << s11_polar.first << " " << s11_polar.second);
            WATCH(s12.real() << " " << s12.imag() << " | " << s12_polar.first << " " << s12_polar.second);
            WATCH(s21.real() << " " << s21.imag() << " | " << s21_polar.first << " " << s21_polar.second);
            WATCH(s22.real() << " " << s22.imag() << " | " << s22_polar.first << " " << s22_polar.second);
#endif


            // fill boxes
            ui->s11_box->setText(QString::number(s11_polar.first));
            ui->s11_box_arg->setText(QString::number(s11_polar.second));

            ui->s12_box->setText(QString::number(s12_polar.first));
            ui->s12_box_arg->setText(QString::number(s12_polar.second));

            ui->s21_box->setText(QString::number(s21_polar.first));
            ui->s21_box_arg->setText(QString::number(s21_polar.second));

            ui->s22_box->setText(QString::number(s22_polar.first));
            ui->s22_box_arg->setText(QString::number(s22_polar.second));

        }
        else {
            // combo box entry is empty

            // clean the S and noise boxes.
            ui->s11_box->setText("");
            ui->s11_box_arg->setText("");

            ui->s12_box->setText("");
            ui->s12_box_arg->setText("");

            ui->s21_box->setText("");
            ui->s21_box_arg->setText("");

            ui->s22_box->setText("");
            ui->s22_box_arg->setText("");



            ui->NFmindb_box_2->setText("");
            ui->rn_box_2->setText("");
            ui->gamma_s_on_box->setText("");
            ui->gamma_s_on_box_2->setText("");
        }


    }
    else {
        // MRF transistor radio button is NOT checked, i.e. you are in MANUAL MODE

        // read from lineedit the S parameters.
        if (!ui->s11_box->text().isEmpty() && !ui->s11_box_arg->text().isEmpty()){
            s11_polar = std::make_pair( ui->s11_box->text().toFloat(),
                                        ui->s11_box_arg->text().toFloat());
        } else {
            s11_polar = std::make_pair(NAN, NAN);
        }
        if (!ui->s12_box->text().isEmpty() && !ui->s12_box_arg->text().isEmpty()){
            s12_polar = std::make_pair( ui->s12_box->text().toFloat(),
                                        ui->s12_box_arg->text().toFloat());
        } else {
            s12_polar = std::make_pair(NAN, NAN);
        }
        if (!ui->s21_box->text().isEmpty() && !ui->s21_box_arg->text().isEmpty()){
            s21_polar = std::make_pair( ui->s21_box->text().toFloat(),
                                        ui->s21_box_arg->text().toFloat());
        } else {
            s21_polar = std::make_pair(NAN, NAN);
        }
        if (!ui->s22_box->text().isEmpty() && !ui->s22_box_arg->text().isEmpty()){
            s22_polar = std::make_pair( ui->s22_box->text().toFloat(),
                                        ui->s22_box_arg->text().toFloat());
        } else {
            s22_polar = std::make_pair(NAN, NAN);
        }



        
        
    
        // read noise parameters
        ui->NFmindb_box_2->setReadOnly(false);
        ui->rn_box_2->setReadOnly(false);
        ui->gamma_s_on_box->setReadOnly(false);
        ui->gamma_s_on_box_2->setReadOnly(false);

        if (!ui->NFmindb_box_2->text().isEmpty()){
            NFmin_db = ui->NFmindb_box_2->text().toFloat();
        } else {
            NFmin_db = NAN;
        }
        if (!ui->rn_box_2->text().isEmpty()){
            Rn = ui->rn_box_2->text().toFloat();
        } else {
            Rn = NAN;
        }
        if (!ui->gamma_s_on_box->text().isEmpty() && !ui->gamma_s_on_box_2->text().isEmpty()){
            gamma_s_on = polar_2_rect(ui->gamma_s_on_box->text().toFloat(),
                                      DEG_2_RAD(ui->gamma_s_on_box_2->text().toFloat())
                                      );
            
        }else {
            gamma_s_on = complex_t(NAN, NAN);

        }



        // convert S parameters in polar form to std::complex<double> in order
        // for them to be easily processed by the functions.
        s11 = polar_2_rect(s11_polar.first, DEG_2_RAD(s11_polar.second));
        s12 = polar_2_rect(s12_polar.first, DEG_2_RAD(s12_polar.second));
        s21 = polar_2_rect(s21_polar.first, DEG_2_RAD(s21_polar.second));
        s22 = polar_2_rect(s22_polar.first, DEG_2_RAD(s22_polar.second));

        


    }



    /// read source and load now
    ///
    /// Z0 first..

    if (! ui->Z0_box->text().isEmpty()){
        z0 = ui->Z0_box->text().toFloat();

        ui->statusBar->showMessage("");
        ui->statusBar->setStyleSheet("background-color: auto;");
    } else {
        z0 = NAN;
        ui->statusBar->showMessage("Fill z0 before proceeding.");
        ui->statusBar->setStyleSheet("background-color: red; color: white;");
    }

    // now S and L
    if (ui->radioButton_input_as_Z->isChecked()){
        // source and load as IMPEDANCES
        if (! ui->ZL_box->text().isEmpty()){
            zl = complex_t (
                        ccomplex( ui->ZL_box->text().toStdString()).Re(),
                        ccomplex( ui->ZL_box->text().toStdString()).Im()
                        );
        } else {
            zl = complex_t (NAN, NAN);
        }
        if (! ui->ZS_box->text().isEmpty()){
            zs = complex_t (
                        ccomplex( ui->ZS_box->text().toStdString()).Re(),
                        ccomplex( ui->ZS_box->text().toStdString()).Im()
                        );
        } else {
            zs = complex_t (NAN, NAN);
        }

        // now i can compute it's equivalent gamma-value
        gamma_s = z2gamma(zs, complex_t(z0, 0));
        gamma_l = z2gamma(zl, complex_t(z0, 0));

    }
    else {
        // source and load as GAMMAS
        if (!ui->ZS_box_2->text().isEmpty() && !ui->ZS_box_5->text().isEmpty()){
            gamma_s = polar_2_rect(ui->ZS_box_2->text().toFloat(),
                                   DEG_2_RAD(ui->ZS_box_5->text().toFloat())
                                 );
        }else{
            gamma_s = complex_t(NAN, NAN);
        }

        if (!ui->ZS_box_4->text().isEmpty() && !ui->ZS_box_3->text().isEmpty()){
            gamma_l = polar_2_rect(ui->ZS_box_4->text().toFloat(),
                                   DEG_2_RAD(ui->ZS_box_3->text().toFloat())
                                   );
        }else{
            gamma_l = complex_t(NAN, NAN);
        }

        // now i can compute it's equivalent impedance:
        zs = gamma2z(gamma_s, complex_t(z0, 0));
        zl = gamma2z(gamma_l, complex_t(z0, 0));


    }


    // read values for computing constant circumferences:

    double NF_circle_dB;
    double Ga_circle_dB, Gp_circle_dB, Gt_circle_dB;


    if (!ui->NFdb_box_2->text().isEmpty()){
        NF_circle_dB = ui->NFdb_box_2->text().toFloat();
    }else{
        NF_circle_dB = NAN;
    }
    if (!ui->GAdb_box_2->text().isEmpty()){
        Ga_circle_dB = ui->GAdb_box_2->text().toFloat();
    }else{
        Ga_circle_dB = NAN;
    }
    if (!ui->GPdb_box_2->text().isEmpty()){
        Gp_circle_dB = ui->GPdb_box_2->text().toFloat();
    }else{
        Gp_circle_dB = NAN;
    }
    if (!ui->GTdb_box_2->text().isEmpty()){
        Gt_circle_dB = ui->GTdb_box_2->text().toFloat();
    }else{
        Gt_circle_dB = NAN;
    }




    //////////////////////////       variables declaration       /////////////
    complex_t determinant;
    double K;

    complex_t gamma_in;
    complex_t gamma_out;
    
    complex_t z_in;
    complex_t z_out;
        

    complex_t Cs;
    double rs;

    complex_t Cl;
    double rl;

    double GA,     GP,     GT;
    double GA_max, GP_max, GT_max;

    double NF;

    complex_t Cnf;
    double rnf;

    complex_t Ca;
    double ra;

    complex_t Cp;
    double rp;

    complex_t Ct;
    double rt;

    complex_t gamma_s_opt;
    complex_t gamma_l_opt;

    complex_t zs_opt;
    complex_t zl_opt;


    //////////////////////////   end  variables declaration       /////////////



    determinant = compute_D(s11, s12, s21, s22);
    K = calculate_K(s11, s12, s21, s22);
    
    gamma_in = calculate_gamma_in(s11, s12, s21, s22, zl, z0);
    gamma_out = calculate_gamma_out(s11,s12,s21,s22,zs,z0);

    z_in = gamma2z(gamma_in, z0);
    z_out = gamma2z(gamma_out, z0);


    GA = calculate_GA(s11,s12,s21,s22,zs,z0);
    GP = calculate_GP(s11,s12,s21,s22,zl,z0);
    GT = calculate_GT(s11,s12,s21,s22,zs,zl,z0);


    z_s_on = gamma2z(gamma_s_on, z0);
    NF = calculate_NF(NFmin_db,Rn,gamma_s_on,zs,z0);


    gamma_s_opt = calculate_gamma_S_opt(s11,s12,s21,s22);
    gamma_l_opt = calculate_gamma_L_opt(s11,s12,s21,s22);

    zs_opt = gamma2z(gamma_s_opt, complex_t(z0, 0));
    zl_opt = gamma2z(gamma_l_opt, complex_t(z0, 0));

    GA_max = calculate_GA(s11,s12,s21,s22,zs_opt,z0);
    GP_max = calculate_GP(s11,s12,s21,s22,zl_opt,z0);
    GT_max = calculate_GT(s11,s12,s21,s22,zs_opt,zl_opt,z0);


    // input and output stability circles:
    std::tie(Cs, rs) = calculate_ISC(s11,s12,s21,s22);
    std::tie(Cl, rl) = calculate_OSC(s11,s12,s21,s22);

    // constatnt circumferences (NF and gains)
    #define NF_opt_dB NFmin_db // alias

    std::tie(Cnf, rnf) = calculate_NF_circle(s11,s12,s21,s22,z0,NF_circle_dB,gamma_s_on,NF_opt_dB,Rn);
    std::tie(Ca, ra) = calculate_GA_circle(s11,s12,s21,s22,Ga_circle_dB);
    std::tie(Cp, rp) = calculate_GP_circle(s11,s12,s21,s22,Gp_circle_dB);
    std::tie(Ct, rt) = calculate_GT_circle(s11,s12,s21,s22,zs,zl,z0,Gt_circle_dB);



    /* displays output */

#define NUM_SIGNIFICANT_DIGITS 3
    ui->D_box_2->setText(
                QString::number(MAG(determinant),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(determinant), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
                );

    ui->k_box_4->setText(QString::number(K));

    
    ui->ZS_box2->setText(COMPLEX_REPR_RE_IM(zs));
    ui->gamma_S_box->setText(QString::number(MAG(gamma_s),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                             QString::number(ARG_DEG(gamma_s), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
                             );


    ui->gamma_out_box_2->setText(
                QString::number(MAG(gamma_out),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(gamma_out), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
                );


    ui->ZL_box2->setText(COMPLEX_REPR_RE_IM(zl));
    ui->gamma_L_box->setText(QString::number(MAG(gamma_l),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                             QString::number(ARG_DEG(gamma_l), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
                             );


    ui->gamma_in_box_2->setText(
                QString::number(MAG(gamma_in),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(gamma_in), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
                );

    ui->z_in_box->setText(COMPLEX_REPR_RE_IM(z_in));
    ui->z_out_box->setText(COMPLEX_REPR_RE_IM(z_out));


    ui->textBrowser_4->setText(QString::number(NF));
    ui->textBrowser_5->setText(QString::number(linear_2_dB(NF)));

    ui->GAdb_box2_7->setText(QString::number(GA));
    ui->GAdb_box2_8->setText(QString::number(linear_2_dB(GA)));
    ui->textBrowser_2->setText(QString::number(linear_2_dB(GA_max)));

    ui->GPdb_box2_8->setText(QString::number(GP));
    ui->GPdb_box2_7->setText(QString::number(linear_2_dB(GP)));
    ui->textBrowser->setText(QString::number(linear_2_dB(GP_max))); // GP max

    ui->GTdb_box2_7->setText(QString::number(GT));
    ui->GTdb_box2_8->setText(QString::number(linear_2_dB(GT)));
    ui->textBrowser_3->setText(QString::number(linear_2_dB(GT_max))); // GT max



    ui->textBrowser_8->setText(COMPLEX_REPR_RE_IM(zs_opt));
    ui->gamma_s_opt_box_5->setText(
            QString::number(MAG(gamma_s_opt),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
            QString::number(ARG_DEG(gamma_s_opt), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
    );


    ui->textBrowser_7->setText(COMPLEX_REPR_RE_IM(zl_opt));
    ui->gamma_L_opt_box_5->setText(
                QString::number(MAG(gamma_l_opt),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(gamma_l_opt), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
    );


    // circumferences:

    // ISC
    ui->C_box_13->setText(  
                QString::number(MAG(Cs),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(Cs), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
    );
    ui->C_box_19->setText(QString::number(rs));



    // OSC
    ui->C_box_16->setText(
                QString::number(MAG(Cl),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                QString::number(ARG_DEG(Cl), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
    );
    ui->C_box_32->setText(QString::number(rl));

    
    // Cnf
    if (!ui->NFdb_box_2->text().isEmpty()){    
        ui->C_box_37->setText(
                    QString::number(MAG(Cnf),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                    QString::number(ARG_DEG(Cnf), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
        );
        ui->C_box_36->setText(QString::number(rnf));
    }else{
        ui->C_box_37->setText(""); // Cnf
        ui->C_box_36->setText(""); // rnf
    }
    
    //Ca
    if (!ui->GAdb_box_2->text().isEmpty()){
        ui->C_box_43->setText(
                    QString::number(MAG(Ca),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                    QString::number(ARG_DEG(Ca), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
        );
        ui->C_box_42->setText(QString::number(ra));
    }else{
        ui->C_box_43->setText(""); // Ca
        ui->C_box_42->setText(""); // ra
    }
    
    //Cp
    if (!ui->GPdb_box_2->text().isEmpty()){    
        ui->C_box_39->setText(
                    QString::number(MAG(Cp),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                    QString::number(ARG_DEG(Cp), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
        );
        ui->C_box_38->setText(QString::number(rp));
    }else{
        ui->C_box_39->setText(""); // Cp
        ui->C_box_38->setText(""); // rp
    }
    
    //Ct
    if (!ui->GTdb_box_2->text().isEmpty()){
        ui->C_box_41->setText(
                    QString::number(MAG(Ct),'g', NUM_SIGNIFICANT_DIGITS) + "∠" +
                    QString::number(ARG_DEG(Ct), 'g', NUM_SIGNIFICANT_DIGITS) + " deg"
        );
        ui->C_box_40->setText(QString::number(rt));
    }else{
        ui->C_box_41->setText(""); // Ct
        ui->C_box_40->setText(""); // rt
    }

    /*
     *                 K
     *             <1     >1
     *          +--------------
     *       <1 | PU     US
     *   |D|    |
     *       >1 | PU     PU
     *          |
     *
     *               |Γout| 
     *             <1     >1
     *          +--------------
     *       <1 |  S      U
     * |Γin|    |
     *       >1 |  U      U
     *          |
     *
     */
    

    std::string stability_status;

    if (std::isnan(abs(determinant)) || std::isnan(K)){
        stability_status = "";
        ui->D_box_2->setStyleSheet(styleSheet()); // D
        ui->k_box_4->setStyleSheet(styleSheet()); // K
        ui->gamma_in_box_2->setStyleSheet(styleSheet()); // gamma in
        ui->gamma_out_box_2->setStyleSheet(styleSheet()); // gamma out
    } else {
        if (abs(determinant) < 1.0 && K > 1){
            stability_status = "<b><font color='green'>Unconditionally stable system</font></b>";
            ui->D_box_2->setStyleSheet("border: 0.1ex solid " GREEN); // D
            ui->k_box_4->setStyleSheet("border: 0.1ex solid " GREEN); // k
        } else {
            stability_status = "<i>Potentially unstable system</i>";
            ui->D_box_2->setStyleSheet("border: 0.1ex solid " ORANGE); // D
            ui->k_box_4->setStyleSheet("border: 0.1ex solid " ORANGE); // K
        }
    }

    if (std::isnan(gamma_out.real()) && std::isnan(gamma_in.real())){
        ui->gamma_in_box_2->setStyleSheet(styleSheet()); // gamma in
        ui->gamma_out_box_2->setStyleSheet(styleSheet()); // gamma out
    } else if (std::isnan(gamma_out.real())){
        ui->gamma_out_box_2->setStyleSheet(styleSheet()); // gamma out
    } else if (std::isnan(gamma_in.real())){
        ui->gamma_in_box_2->setStyleSheet(styleSheet()); // gamma in
    }
    else {
        if (abs(gamma_in) < 1.0 && abs(gamma_out) < 1.0){
            stability_status = "<b><font color='green'>Stable system</font></b>";
            ui->gamma_in_box_2->setStyleSheet("border: 0.1ex solid " GREEN); // gamma in
            ui->gamma_out_box_2->setStyleSheet("border: 0.1ex solid " GREEN); // gamma out
        } else {
            if (abs(gamma_out) < 1) {
                stability_status = "<b><font color='red'>Unstable system.</b> |Γ<sub>in</sub>| &gt; 1</font>";
                ui->gamma_in_box_2->setStyleSheet("border: 0.1ex solid " RED); // gamma in
                ui->gamma_out_box_2->setStyleSheet("border: 0.1ex solid " GREEN); // gamma out
            } else if (abs(gamma_in) < 1){
                stability_status = "<b><font color='red'>Unstable system.</b> |Γ<sub>out</sub>| &gt; 1</font>";
                ui->gamma_in_box_2->setStyleSheet("border: 0.1ex solid " GREEN); // gamma in
                ui->gamma_out_box_2->setStyleSheet("border: 0.1ex solid " RED); // gamma out
            } else {
                stability_status = "<b><font color='red'>Unstable system.</b> |Γ<sub>in</sub>| &gt; 1 and |Γ<sub>out</sub>| &gt; 1</font>";
                ui->gamma_in_box_2->setStyleSheet("border: 0.1ex solid " RED); // gamma in
                ui->gamma_out_box_2->setStyleSheet("border: 0.1ex solid " RED); // gamma out
            }
        }
    }

    ui->label_S_tab->setText(QString::fromStdString(stability_status));


   

#if PRINT_TO_CONSOLE
            std::cout << ANSI_BOLD << "S parameters " << ANSI_COLOR_RESET << '\n';
                            /*ANSI_BOLD << transistor_name << " @ Vce = " << Vce << "V; Ic = " << Ic << "mA; f = " << f0 << "MHz " << ANSI_COLOR_RESET << '\n';*/

            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "s11 = " << COMPLEX_REPR_RE_IM_console(s11) << "\t == " << MAG(s11) << "∠" << ARG_DEG(s11) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "s12 = " << COMPLEX_REPR_RE_IM_console(s12) << "\t == " << MAG(s12) << "∠" << ARG_DEG(s12) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "s21 = " << COMPLEX_REPR_RE_IM_console(s21) << "\t == " << MAG(s21) << "∠" << ARG_DEG(s21) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "s22 = " << COMPLEX_REPR_RE_IM_console(s22) << "\t == " << MAG(s22) << "∠" << ARG_DEG(s22) << " deg" << "\n";
            std::cout << '\n';

            std::cout << ANSI_BOLD << "Noise parameters:" << ANSI_COLOR_RESET <<'\n';
            WATCH(NFmin_db);
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "Rn = " << Rn << "ohm  -- rn = " << Rn/z0 << '\n';
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "gamma_s_on = " << COMPLEX_REPR_RE_IM_console(gamma_s_on) << "\t == " << MAG(gamma_s_on) << "∠" << ARG_DEG(gamma_s_on) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "z_s_on = " << COMPLEX_REPR_RE_IM_console(z_s_on) << "\t == " << MAG(z_s_on) << "∠" << ARG_DEG(z_s_on) << " deg" << "\n";
            std::cout << '\n';
                


            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "determinant = " << COMPLEX_REPR_RE_IM_console(determinant) << "\t == " << MAG(determinant) << "∠" << ARG_DEG(determinant) << " deg" << "\n";
            WATCH(K);

            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "gamma_in = " << COMPLEX_REPR_RE_IM_console(gamma_in) << "\t == " << MAG(gamma_in) << "∠" << ARG_DEG(gamma_in) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "gamma_out = " << COMPLEX_REPR_RE_IM_console(gamma_out) << "\t == " << MAG(gamma_out) << "∠" << ARG_DEG(gamma_out) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "z_in = " << COMPLEX_REPR_RE_IM_console(z_in) << "\t == " << MAG(z_in) << "∠" << ARG_DEG(z_in) << " deg" << "\n";
            std::cout << ANSI_COLOR_GREY << __FILE__ << " @ " << __LINE__ << ": " << ANSI_COLOR_RESET << "z_out = " << COMPLEX_REPR_RE_IM_console(z_out) << "\t == " << MAG(z_out) << "∠" << ARG_DEG(z_out) << " deg" << "\n";
            std::cout << '\n';



            WATCH(Cs);
            WATCH(rs);

            WATCH(Cl);
            WATCH(rl);

            WATCH(GP);
            WATCH(GT);
            WATCH(GA);
            
            WATCH(NF);

            
            WATCH(Cnf);
            WATCH(rnf);

            WATCH(Ca);
            WATCH(ra);

            WATCH(Cp);
            WATCH(rp);

            WATCH(Ct);
            WATCH(rt);

            WATCH(gamma_s_opt);
            WATCH(gamma_l_opt);

            WATCH(zs_opt);
            WATCH(zl_opt);

#endif


            Sdata.Cs =                      Cs;
            Sdata.rs =                      rs;
            Sdata.Cl =                      Cl;
            Sdata.rl =                      rl;
            Sdata.gamma_in =                gamma_in;
            Sdata.gamma_out =               gamma_out;
            Sdata.gamma_L =                 gamma_l;
            Sdata.gamma_S =                 gamma_s;
            Sdata.GA_dB =                   Ga_circle_dB;
            Sdata.Ca =                      Ca;
            Sdata.ra =                      ra;
            Sdata.NF_dB =                   NF_circle_dB;
            Sdata.Cnf =                     Cnf;
            Sdata.rnf =                     rnf;
            Sdata.GT_dB =                   Gt_circle_dB;
            Sdata.Ct =                      Ct;
            Sdata.rt =                      rt;
            Sdata.GP_dB =                   Gp_circle_dB;
            Sdata.Cp =                      Cp;
            Sdata.rp =                      rp;
            // Sdata.constant_gamma_circle =   constant_gamma_circle;
            Sdata.ZS =                      zs;
            Sdata.ZL =                      zl; 
            Sdata.Z0 =                      z0; 
            // Sdata.gamma_S_visualized =      gamma_S_visualized; 
            // Sdata.gamma_L_visualized =      gamma_L_visualized; 
            // Sdata.label_gamma_inout =       label_gamma_inout; 
            // Sdata.vce =                     vce; 
            // Sdata.ic =                      ic; 
            // Sdata.f =                       f; 
            // Sdata.bjt =                     bjt;




            this->setWindowTitle("syRF");
            this->setWindowModified(false);
}


void MainWindow::on_radioButton1_MRF571_clicked(){
    ui->s11_box->setReadOnly(true);
    ui->s11_box_arg->setReadOnly(true);
    ui->s12_box->setReadOnly(true);
    ui->s12_box_arg->setReadOnly(true);
    ui->s21_box->setReadOnly(true);
    ui->s21_box_arg->setReadOnly(true);
    ui->s22_box->setReadOnly(true);
    ui->s22_box_arg->setReadOnly(true);
    
    ui->open_datasheet_button->setEnabled(true);
    ui->comboBox_MRF_bias->setEnabled(true);

    ui->ZS_box->setFocus();

    on_Calculate_button_5_clicked();
}

void MainWindow::on_manual_input_s_radioButton_clicked(){
    ui->s11_box->setReadOnly(false);
    ui->s11_box_arg->setReadOnly(false);
    ui->s12_box->setReadOnly(false);
    ui->s12_box_arg->setReadOnly(false);
    ui->s21_box->setReadOnly(false);
    ui->s21_box_arg->setReadOnly(false);
    ui->s22_box->setReadOnly(false);
    ui->s22_box_arg->setReadOnly(false);

    ui->open_datasheet_button->setEnabled(false);
    ui->comboBox_MRF_bias->setEnabled(false);

    ui->s11_box->setFocus();

    on_Calculate_button_5_clicked();
}


void MainWindow::on_radioButton_input_as_Z_clicked(){
    ui->label_250->setEnabled(false);
    ui->ZS_box_2->setEnabled(false);
    ui->label_257->setEnabled(false);
    ui->ZS_box_5->setEnabled(false);
    ui->label_264->setEnabled(false);
    ui->ZS_box_4->setEnabled(false);
    ui->label_265->setEnabled(false);
    ui->ZS_box_3->setEnabled(false);

    ui->label_196->setEnabled(true);
    ui->ZS_box->setEnabled(true);
    ui->label_26->setEnabled(true);
    ui->label_197->setEnabled(true);
    ui->ZL_box->setEnabled(true);
    ui->label_25->setEnabled(true);

    ui->ZS_box->setFocus();
}

void MainWindow::on_radioButton_input_as_gamma_clicked(){
    
    ui->label_250->setEnabled(true);
    ui->ZS_box_2->setEnabled(true);
    ui->label_257->setEnabled(true);
    ui->ZS_box_5->setEnabled(true);
    ui->label_264->setEnabled(true);
    ui->ZS_box_4->setEnabled(true);
    ui->label_265->setEnabled(true);
    ui->ZS_box_3->setEnabled(true);

    ui->label_196->setEnabled(false);
    ui->ZS_box->setEnabled(false);
    ui->label_26->setEnabled(false);
    ui->label_197->setEnabled(false);
    ui->ZL_box->setEnabled(false);
    ui->label_25->setEnabled(false);

    ui->ZS_box_2->setFocus();
}


void MainWindow::on_comboBox_MRF_bias_currentTextChanged(const QString &arg1) {
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s11_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s11_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s11_box_arg_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s11_box_arg_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s12_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s12_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s12_box_arg_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s12_box_arg_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s21_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s21_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s21_box_arg_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s21_box_arg_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s22_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s22_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_s22_box_arg_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_s22_box_arg_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_NFmindb_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_NFmindb_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}
void MainWindow::on_rn_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_rn_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}
void MainWindow::on_gamma_s_on_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_gamma_s_on_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}
void MainWindow::on_gamma_s_on_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_gamma_s_on_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_Z0_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_Z0_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZS_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZS_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZL_box_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZL_box_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZS_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZS_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZS_box_5_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZS_box_5_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZS_box_4_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZS_box_4_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_ZS_box_3_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_ZS_box_3_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_NFdb_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_NFdb_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_GAdb_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_GAdb_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_GTdb_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_GTdb_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}

void MainWindow::on_GPdb_box_2_returnPressed(){
    on_Calculate_button_5_clicked();
}
void MainWindow::on_GPdb_box_2_textChanged(){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}





void MainWindow::on_plot_isc_button_2_clicked(){
    /* before running this make sure to alias smithplot in the right place:
    
        cd build-syRF-Desktop_x86_darwin_generic_mach_o_64bit-Debug
        ln -s ../../../syRF/src/main/python/twoport/ .

    */


    std::string command = "python3.8 -c \"import twoport.smithplot; twoport.smithplot.plot_Smith(";
    command += COMPLEX_REPR_RE_IM_console(Sdata.Cs);
    command += ", ";
    command += std::to_string(Sdata.rs);
    command += ", ";
    command += COMPLEX_REPR_RE_IM_console(Sdata.Cl);
    command += ", "; 
    command += std::to_string(Sdata.rl);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.gamma_in);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.gamma_out);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.gamma_L);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.gamma_S);
    command += ", "; 
    command += std::to_string(Sdata.GA_dB);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.Ca);
    command += ", "; 
    command += std::to_string(Sdata.ra);
    command += ", "; 
    command += std::to_string(Sdata.NF_dB);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.Cnf);
    command += ", "; 
    command += std::to_string(Sdata.rnf);
    command += ", "; 
    command += std::to_string(Sdata.GT_dB);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.Ct);
    command += ", "; 
    command += std::to_string(Sdata.rt);
    command += ", "; 
    command += std::to_string(Sdata.GP_dB);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.Cp);
    command += ", "; 
    command += std::to_string(Sdata.rp);
    
    // command += ", " + std::to_string(Sdata.constant_gamma_circle);
    
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.ZS);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.ZL);
    command += ", "; 
    command += COMPLEX_REPR_RE_IM_console(Sdata.Z0);
    command += ", "; 
    // command += std::to_string(Sdata.gamma_S_visualized);
    // command += ", "; 
    // command += std::to_string(Sdata.gamma_L_visualized);
    // command += ", "; 
    // command += std::to_string(Sdata.label_gamma_inout);
    command += ", "; 
    command += std::to_string(Sdata.vce);
    command += ", "; 
    command += std::to_string(Sdata.ic);
    command += ", "; 
    command += std::to_string(Sdata.f);
    // command += ", "; 
    // command += std::to_string(Sdata.bjt);

    command += ")\"";


#if PRINT_TO_CONSOLE
    std::cout << "command: \n";
    std::cout << command << '\n';
#endif


    //system("python3.8 -c \"import twoport.smithplot; twoport.smithplot.plot_Smith(Cs, rs, Cl, rl, gamma_in, gamma_out, gamma_L, gamma_S, GA_dB, Ca, ra, NF_dB, Cnf, rnf, GT_dB, Ct, rt, GP_dB, Cp, rp, constant_gamma_circle, ZS, ZL, Z0, gamma_S_visualized, gamma_L_visualized, label_gamma_inout, vce, ic, f, bjt)\" ");
    system(command.c_str());


}





void MainWindow::on_action_LumpedMatching_triggered() {
    LumpedMatching* lumpedmatching = new LumpedMatching();
    lumpedmatching->show();
}

void MainWindow::on_actionStub_triggered() {
    //StubMatching* stubmatching = new StubMatching();
    //stubmatching->show();
}






void MainWindow::on_action_About_2_triggered(){
    About about;
    about.setModal(true);
    about.exec();
}



void MainWindow::closeEvent (QCloseEvent *event){
#if 1
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "syRF",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    resBtn != QMessageBox::Yes ? event->ignore() : event->accept();

#endif
}


void MainWindow::on_open_datasheet_button_clicked(){
    QDesktopServices::openUrl(QUrl(URL_MRF571));
}
