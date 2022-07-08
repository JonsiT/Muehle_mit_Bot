#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    // Windowname festlegen
    StartWindow::setWindowTitle("Mühle");
    // Appicon
    QApplication::setWindowIcon(QIcon(":/images/Stein_braun.png"));
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::Modi(int a){
    close();
    mainwindow = new MainWindow(this);
    mainwindow->bot = a;
    mainwindow->show();
}

void StartWindow::on_Spieler_1_clicked()
{
    Modi(1);

}

void StartWindow::on_Spieler_2_clicked()
{
    Modi(0);
}
