/*****************************************************************
**                                                              **
**  syRF-Stub                                                   **
**  Copyright (C) 2020 Francesco Urbani                         **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Fri Nov 13 2020 09:50:02 am CET                  **
**  File:           stub_matching.h                             **
**  Description:                                                **
******************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StubMatching; }
QT_END_NAMESPACE

class StubMatching : public QMainWindow {
    
    Q_OBJECT

public:
    StubMatching(QWidget *parent = nullptr);
    ~StubMatching();

private slots:
    void on_Calculate_button_clicked();
    void on_parallel_stub_radioButton_clicked();
    void on_series_stub_radioButton_clicked();
    void on_ZL_lineedit_returnPressed();
    void on_Z0_stub_lineedit_returnPressed();
    void on_OC_radioButton_clicked();
    void on_SC_radioButton_clicked();
    void on_distance_horizontalScrollBar_valueChanged(int value);
    void on_length_horizontalScrollBar_valueChanged(int value);
private:
    Ui::StubMatching *ui;
};

#endif // MAINWINDOW_H
