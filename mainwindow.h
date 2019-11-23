#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "about.h"

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
    void on_action_About_2_triggered();
    void on_actionAbout_syRF_triggered();

private:
    Ui::MainWindow *ui;
//    About *about;

};

#endif // MAINWINDOW_H
