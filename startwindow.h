#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>


namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:

    // Button für 1 Spieler
    void on_Spieler_1_clicked();

    // Button für 2 Spieler
    void on_Spieler_2_clicked();

    void Modi(int a);

private:
    Ui::StartWindow *ui;
    MainWindow *mainwindow;
};

#endif // STARTWINDOW_H
