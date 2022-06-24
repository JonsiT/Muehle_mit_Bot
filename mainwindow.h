#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int bot = 1;
    int bot_anzahl = 0;

    int Status[25] {0};
    int count = 0;
    int stage = 0;
    int zuege = 0;

    int number_1 = 0;
    int number_2 = 0;

    int auswahl = 0;

    int wir = 0;
    int ihr = 0;

    int state = 0;

    int state_gegner = 0;

    int anzahl_verfuegbar = 0;



    /* Programmfunktionen */

    bool wort;
    int zoul = 0;
    int woul = 0;
    int number_clean;

    int bot_array_3[4]{0};

    bool bewegungsfreiheit_1(int a, int b, int c, int d);
    bool bewegungsfreiheit_2(int zahl);
    void bewegung_empty_1(int a, int b, int c, int d);
    void bewegung_empty_2(int a);

    void bewegung_empty_1_bot(int a, int b, int c, int d);
    void bewegung_empty_2_bot(int a);

    bool muehle_1(int a, int b, int c, int d);
    bool muehle_2(int nummer);

    void enable(int wow);

    void entfernen();


    void freischalten();
    void freischalten_bot();
private slots:

    void Programm();

    void Programm_bot();

    /* Felder */
    void on_Feld_0_clicked();
    void on_Feld_1_clicked();
    void on_Feld_2_clicked();
    void on_Feld_3_clicked();
    void on_Feld_4_clicked();
    void on_Feld_5_clicked();
    void on_Feld_6_clicked();
    void on_Feld_7_clicked();
    void on_Feld_8_clicked();
    void on_Feld_9_clicked();
    void on_Feld_10_clicked();
    void on_Feld_11_clicked();
    void on_Feld_12_clicked();
    void on_Feld_13_clicked();
    void on_Feld_14_clicked();
    void on_Feld_15_clicked();
    void on_Feld_16_clicked();
    void on_Feld_17_clicked();
    void on_Feld_18_clicked();
    void on_Feld_19_clicked();
    void on_Feld_20_clicked();
    void on_Feld_21_clicked();
    void on_Feld_22_clicked();
    void on_Feld_23_clicked();

    void on_Beenden_clicked();
    void on_Resetten_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
