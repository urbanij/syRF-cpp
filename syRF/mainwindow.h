/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sat Dec  7 11:36:08 CET 2019                     **
**  File:           mainwindow.h                                **
**  Description:                                                **
******************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtEvents>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /// Y TAB ///
    void on_open_datasheet_Y_button_clicked();

    void on_Calculate_button_4_clicked();

    void on_f0_box_2_returnPressed();
    void on_f0_box_2_textEdited(const QString &arg1);

    void on_y_i_box_2_returnPressed();
    void on_y_i_box_2_textChanged(const QString &arg1);

    void on_y_f_box_2_returnPressed();
    void on_y_f_box_2_textChanged(const QString &arg1);

    void on_y_r_box_2_returnPressed();
    void on_y_r_box_2_textChanged(const QString &arg1);

    void on_y_o_box_2_returnPressed();
    void on_y_o_box_2_textChanged(const QString &arg1);

    void on_y_s_box_2_returnPressed();
    void on_y_s_box_2_textChanged(const QString &arg1);

    void on_y_L_box_2_returnPressed();
    void on_y_L_box_2_textChanged(const QString &arg1);



    void on_radioButton_CE_clicked();
    void on_radioButton_CB_clicked();
    void on_radiobutton_2n4957_clicked();
    void on_manual_input_y_radioButton_clicked();

    /// END Y TAB ///

    /// S TAB ///
    void on_Calculate_button_5_clicked();


    void on_radioButton1_MRF571_clicked();
    void on_manual_input_s_radioButton_clicked();
    void on_radioButton_input_as_Z_clicked();
    void on_radioButton_input_as_gamma_clicked();



    /// END S TAB ///


    void on_action_About_2_triggered();
    void on_action_LumpedMatching_triggered();


    void closeEvent (QCloseEvent *event);






    void on_s11_box_returnPressed();
    void on_s11_box_textChanged(const QString& arg1);

    void on_s11_box_arg_returnPressed();
    void on_s11_box_arg_textChanged(const QString& arg1);

    void on_s12_box_returnPressed();
    void on_s12_box_textChanged(const QString& arg1);

    void on_s12_box_arg_returnPressed();
    void on_s12_box_arg_textChanged(const QString& arg1);

    void on_s21_box_returnPressed();
    void on_s21_box_textChanged(const QString& arg1);

    void on_s21_box_arg_returnPressed();
    void on_s21_box_arg_textChanged(const QString& arg1);

    void on_s22_box_returnPressed();
    void on_s22_box_textChanged(const QString& arg1);

    void on_s22_box_arg_returnPressed();
    void on_s22_box_arg_textChanged(const QString& arg1);

    void on_Z0_box_returnPressed();
    void on_Z0_box_textChanged(const QString& arg1);

    void on_ZS_box_returnPressed();
    void on_ZS_box_textChanged(const QString& arg1);

    void on_ZL_box_returnPressed();
    void on_ZL_box_textChanged(const QString& arg1);

    void on_ZS_box_2_returnPressed();
    void on_ZS_box_2_textChanged(const QString& arg1);

    void on_ZS_box_5_returnPressed();
    void on_ZS_box_5_textChanged(const QString& arg1);

    void on_ZS_box_4_returnPressed();
    void on_ZS_box_4_textChanged(const QString& arg1);

    void on_ZS_box_3_returnPressed();
    void on_ZS_box_3_textChanged(const QString& arg1);

    void on_NFdb_box_2_returnPressed();
    void on_NFdb_box_2_textChanged(const QString& arg1);

    void on_GAdb_box_2_returnPressed();
    void on_GAdb_box_2_textChanged(const QString& arg1);

    void on_GTdb_box_2_returnPressed();
    void on_GTdb_box_2_textChanged(const QString& arg1);

    void on_GPdb_box_2_returnPressed();
    void on_GPdb_box_2_textChanged(const QString& arg1);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
