#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
 #include "about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_About_2_triggered()
{
}

void MainWindow::on_actionAbout_syRF_triggered()
{
//    QMessageBox::warning(this,"Info", "Info");

      About about;
      about.setModal(true);
      about.exec();

    // about = new About(this);
    // about->show();
}
