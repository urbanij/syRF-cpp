/***************************************************************************
**                                                                        **
**  syRF                                                                  **
**  Copyright (C) 2019 Francesco Urbani                                   **
**                                                                        **
****************************************************************************
**  Author:         Francesco Urbani <https://urbanij.github.io/>         **
**  Date:           Sat Dec  7 11:36:08 CET 2019                          **
**  File:           mainwindow.h                                          **                     
**  Description:                                                          **
****************************************************************************/

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

    void on_open_datasheet_Y_button_clicked();

    void on_Calculate_button_4_clicked();
    void closeEvent (QCloseEvent *event);



    void on_y_i_box_2_returnPressed();
    void on_y_f_box_2_returnPressed();
    void on_y_r_box_2_returnPressed();
    void on_y_o_box_2_returnPressed();
    void on_y_s_box_2_returnPressed();
    void on_y_L_box_2_returnPressed();
    void on_action_About_2_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
