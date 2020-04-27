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


#include "s_parameters.h"
#include "s_parameters_data.h"


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



    this->setWindowModified(false);

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

        float f0 = ui->f0_box_2->text().toFloat();
        #if PRINT_TO_CONSOLE
            WATCH(f0);
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

                y_i = complex_t(get_value_from_dictionary(&g_ie, f0),
                                get_value_from_dictionary(&b_ie, f0));
                y_f = complex_t(get_value_from_dictionary(&g_fe, f0),
                                get_value_from_dictionary(&b_fe, f0));
                y_r = complex_t(get_value_from_dictionary(&g_re, f0),
                                get_value_from_dictionary(&b_re, f0));
                y_o = complex_t(get_value_from_dictionary(&g_oe, f0),
                                get_value_from_dictionary(&b_oe, f0));
            }

            else if (ui->radioButton_CB->isChecked()){

                y_i = complex_t(get_value_from_dictionary(&g_ib, f0),
                                get_value_from_dictionary(&b_ib, f0));
                y_f = complex_t(get_value_from_dictionary(&g_fb, f0),
                                get_value_from_dictionary(&b_fb, f0));
                y_r = complex_t(get_value_from_dictionary(&g_rb, f0),
                                get_value_from_dictionary(&b_rb, f0));
                y_o = complex_t(get_value_from_dictionary(&g_ob, f0),
                                get_value_from_dictionary(&b_ob, f0));
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
                        ccomplex( ui->y_i_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_i_box_2->text().toStdString()).Im()
                        );
        } else {
            y_i = complex_t(NAN, NAN); // complex_t (0,0);  // INFINITY is the max value a float can hold
        }

        if (! ui->y_f_box_2->text().isEmpty()){
            y_f = complex_t (
                        ccomplex( ui->y_f_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_f_box_2->text().toStdString()).Im()
                        );
        } else {
            y_f = complex_t(NAN, NAN); // complex_t (0,0);
        }

        if (! ui->y_r_box_2->text().isEmpty()){
            y_r = complex_t (
                        ccomplex( ui->y_r_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_r_box_2->text().toStdString()).Im()
                        );
        } else {
            y_r = complex_t(NAN, NAN); // complex_t (0,0);
        }

        if (! ui->y_o_box_2->text().isEmpty()){
            y_o = complex_t (
                        ccomplex( ui->y_o_box_2->text().toStdString()).Re(),
                        ccomplex( ui->y_o_box_2->text().toStdString()).Im()
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
        WATCH(y_i);
        WATCH(y_f);
        WATCH(y_r);
        WATCH(y_o);
        WATCH(y_s);
        WATCH(y_l);
    #endif


    // compute actual stuff

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



#if PRINT_TO_CONSOLE
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

    this->setWindowModified(false);
}



void MainWindow::on_f0_box_2_textEdited(const QString &arg1){
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
void MainWindow::on_y_i_box_2_textChanged(const QString &arg1){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_f_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_f_box_2_textChanged(const QString &arg1){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_r_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_r_box_2_textChanged(const QString &arg1){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_o_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_o_box_2_textChanged(const QString &arg1){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_s_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_s_box_2_textChanged(const QString &arg1){
    this->setWindowTitle("syRF[*]");
    this->setWindowModified(true);
}


void MainWindow::on_y_L_box_2_returnPressed(){
    on_Calculate_button_4_clicked();
}
void MainWindow::on_y_L_box_2_textChanged(const QString &arg1){
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


void MainWindow::on_Calculate_button_5_clicked(){
    
#if PRINT_TO_CONSOLE
        PRINT("===================================");
        system("clear");
#endif

    // these variables will hold the value of the s parameters
    std::complex<float>     s11,        // complex_t is an alias for std::complex<float>        
                            s12,
                            s21,
                            s22;
    
    std::pair<float,float>  s11_polar,  // could have used its alias S_parameter_t
                            s12_polar,
                            s21_polar,
                            s22_polar;

    complex_t zs, zl;
    float z0;


    float NFmin_db;
    float Rn;
    complex_t gamma_s_on;


//// CHANGE POSTION OF THIS //////////////////////////////////////
    if (! ui->Z0_box->text().isEmpty()){
        z0 = ui->Z0_box->text().toFloat();

        ui->statusBar->showMessage("");
        ui->statusBar->setStyleSheet("background-color: auto;");
    } else {
        ui->statusBar->showMessage("Fill z0 before proceeding.");
        ui->statusBar->setStyleSheet("background-color: red; color: white;");
    }
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
////////////////////////////////////////////////////////////////////////////




    if (ui->radioButton1_MRF571->isChecked()){

        std::string combobox_entry = ui->comboBox_MRF_bias->currentText().toStdString();

        WATCH(combobox_entry);

        if (combobox_entry != ""){

            std::string transistor_name;
            int         Vce;
            int         Ic;
            int         f0;
            filter_S_transistor_bias_settings(combobox_entry, transistor_name, Vce, Ic, f0);

#if 0
            WATCH(transistor_name);
            WATCH(Vce);
            WATCH(Ic);
            WATCH(f0);
#endif

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


                ui->NFmindb_box_2->setText(QString::number(NFmin_db));
                ui->rn_box_2->setText(QString::number(Rn));
                ui->gamma_s_on_box->setText(QString::number(MAG(gamma_s_on)));
                ui->gamma_s_on_box_2->setText(QString::number(ARG_DEG(gamma_s_on)));

                WATCH(gamma_s_on);
                WATCH(MAG(gamma_s_on));
                WATCH(ARG_DEG(gamma_s_on));

            }
            else {

                // not given from the datasheet hence make those fields editable.

                // clean the fields first
                ui->NFmindb_box_2->setText("");
                ui->rn_box_2->setText("");
                ui->gamma_s_on_box->setText("");
                ui->gamma_s_on_box_2->setText("");

                ui->NFmindb_box_2->setReadOnly(false);
                ui->rn_box_2->setReadOnly(false);
                ui->gamma_s_on_box->setReadOnly(false);
                ui->gamma_s_on_box_2->setReadOnly(false);

                NFmin_db = ui->NFmindb_box_2->text().toFloat();
                Rn = ui->rn_box_2->text().toFloat();
                gamma_s_on = polar_2_rect(ui->gamma_s_on_box->text().toFloat(),
                                          DEG_2_RAD(ui->gamma_s_on_box_2->text().toFloat())
                                          );
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
        // MRF transistor radio button is NOT checked, i.e. you are in manual

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

        NFmin_db = ui->NFmindb_box_2->text().toFloat();
        Rn = ui->rn_box_2->text().toFloat();
        gamma_s_on = polar_2_rect(ui->gamma_s_on_box->text().toFloat(),
                                  DEG_2_RAD(ui->gamma_s_on_box_2->text().toFloat())
                                );



        // convert S parameters in polar form to std::complex<float> in order
        // for them to be easily processed by the functions.
        s11 = polar_2_rect(s11_polar.first, DEG_2_RAD(s11_polar.second));
        s12 = polar_2_rect(s12_polar.first, DEG_2_RAD(s12_polar.second));
        s21 = polar_2_rect(s21_polar.first, DEG_2_RAD(s21_polar.second));
        s22 = polar_2_rect(s22_polar.first, DEG_2_RAD(s22_polar.second));

        


    }


#if 1
            WATCH(s11.real());
            WATCH(s11.imag());
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s11"].first);
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s11"].second);
            // WATCH(DEG_2_RAD(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s11"].second));
            WATCH(s11_polar.first);
            WATCH(s11_polar.second);


            WATCH(s12.real());
            WATCH(s12.imag());
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s12"].first);
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s12"].second);
            // WATCH(DEG_2_RAD(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s12"].second));
            WATCH(s12_polar.first);
            WATCH(s12_polar.second);

            WATCH(s21.real());
            WATCH(s21.imag());
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s21"].first);
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s21"].second);
            // WATCH(DEG_2_RAD(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s21"].second));
            WATCH(MAG(s21));
            WATCH(ARG_DEG(s21));
            WATCH(s21_polar.first);
            WATCH(s21_polar.second);

            WATCH(s22.real());
            WATCH(s22.imag());
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s22"].first);
            // WATCH(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s22"].second);
            // WATCH(DEG_2_RAD(MRF_transistor_S_parameters[std::make_tuple(transistor_name, Vce, Ic, f0)]["s22"].second));
            WATCH(MAG(s22));
            WATCH(ARG_DEG(s22));
            WATCH(s22_polar.first);
            WATCH(s22_polar.second);
#endif


    //////////////////////////       variables declaration       /////////////
    complex_t determinant;
    float K;
    complex_t gamma_in;
    complex_t gamma_out;
    
    complex_t Cs;
    float rs;

    complex_t Cl;
    float rl;

    float GP;
    float GT;
    float GA;
    float NF;

    complex_t Cnf;
    float rnf;

    complex_t Ca;
    float ra;

    complex_t Cp;
    float rp;

    complex_t Ct;
    float rt;

    complex_t gamma_s_opt;
    complex_t gamma_l_opt;

    complex_t zs_opt;
    complex_t zl_opt;
    //////////////////////////   end  variables declaration       /////////////



    determinant = compute_D(s11, s12, s21, s22);
    K = calculate_K(s11, s12, s21, s22);
    
    gamma_in = calculate_gamma_in(s11, s12, s21, s22, zl, z0);
    gamma_out = calculate_gamma_out(s11,s12,s21,s22,zs,z0);

    std::tie(Cs, rs) = calculate_ISC(s11,s12,s21,s22);
    std::tie(Cl, rl) = calculate_OSC(s11,s12,s21,s22);

    GP = calculate_GP(s11,s12,s21,s22,zl,z0);
    GT = calculate_GT(s11,s12,s21,s22,zs,zl,z0);
    GA = calculate_GA(s11,s12,s21,s22,zs,z0);

    NF = calculate_NF(NFmin_db,Rn,gamma_s_on,zs,z0);

#if 0
    std::tie(Cnf, rnf) = calculate_NF_circle(s11,s12,s21,s22,z0,NF_circle_dB,gamma_s_on,NF_opt_dB,Rn);
    std::tie(Ca, ra) = calculate_GA_circle(s11,s12,s21,s22,Ga_circle_dB);
    std::tie(Cp, rp) = calculate_GP_circle(s11,s12,s21,s22,Gp_circle_dB);
    std::tie(Ct, rt) = calculate_GT_circle(s11,s12,s21,s22,zs,zl,z0,Gt_circle_dB);
#endif

    gamma_s_opt = calculate_gamma_S_opt(s11,s12,s21,s22);
    gamma_l_opt = calculate_gamma_L_opt(s11,s12,s21,s22);






    /* displays output */
    ui->D_box_2->setText(
                QString::number(MAG(determinant),'g', 3) + "∠" +
                QString::number(ARG_DEG(determinant), 'g', 3) + " deg"
                );

    ui->k_box_4->setText(QString::number(MAG(K)));

    ui->gamma_in_box_2->setText(
                QString::number(MAG(gamma_in),'g', 3) + "∠" +
                QString::number(ARG_DEG(gamma_in), 'g', 3) + " deg"
                );




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














void MainWindow::on_action_LumpedMatching_triggered(){
    // LumpedMatching lumpedmatching;
    // lumpedmatching.setModal(true);
    // lumpedmatching.exec();
}




void MainWindow::on_action_About_2_triggered(){
    About about;
    about.setModal(true);
    about.exec();
}



void MainWindow::closeEvent (QCloseEvent *event){
#if 0
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "syRF",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    resBtn != QMessageBox::Yes ? event->ignore() : event->accept();

#endif
}


