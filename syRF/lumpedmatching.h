/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Sat May  2 19:51:32 CEST 2020                    **
**  File:           lumpedmatching.h                            **
**  Description:                                                **
******************************************************************/

#ifndef LUMPEDMATCHING_H
#define LUMPEDMATCHING_H


#include "utils.h"
#include "ccomplex.h"
#include "config.h"

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>


namespace Ui {
    class LumpedMatching;
}

class LumpedMatching : public QDialog {
    Q_OBJECT

public:
    explicit LumpedMatching(QWidget *parent = nullptr);
    ~LumpedMatching();



private slots:
    void on_Calculate_button_3_clicked();
    void closeEvent (QCloseEvent *event);


private:
    Ui::LumpedMatching *ui;
};

#endif // LUMPEDMATCHING_H
