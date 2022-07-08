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

    // Gibt den Spielstand der Spieler an
    int Sieg_Spieler_1 = 0;
    int Sieg_Spieler_2 = 0;

    // Entscheidet ob mit Bot oder ohne Bot gespielt werden soll
    int bot = 0;

    // Zählvariablen
    int i;
    int bot_anzahl = 0;
    int anzahl_verfuegbar = 0;

    // Gibt den Status der Felder an + Alibifeld/Füllfeld
    int Status[25] {0};

    // zählt die Züge
    int count = 0;

    // gibt an welcher Spieler am Zug ist
    int zuege = 0;

    // Weitergabe von Feldnummern
    int number_1 = 0;
    int number_2 = 0;

    // bringt zusätzliche Abläufe ins Spiel
    int auswahl = 0;

    // Wie viele Steine der aktuelle Spieler hat
    int state = 0;

    // Wie viele Steine der Gegner hat
    int state_gegner = 0;

    // Anzahl der Steine der Spieler
    int brown_stones = 0;
    int black_stones = 0;

    // Array für bewegungsfreiheit und bewegung_empty
    int array_be[24][4] = {
            { 1, 9, 24, 24 },
            { 0, 2, 4, 24 },
            { 1, 14, 24, 24 },
            { 4, 10, 24, 24 },

            { 1, 3, 5, 7 },
            { 4, 13, 24, 24 },
            { 7, 11, 24, 24 },
            { 4, 6, 8, 24 },

            { 7, 12, 24, 24 },
            { 0, 10, 21, 24 },
            { 3, 9, 11, 18 },
            { 6, 10, 15, 24 },

            { 8, 13, 17, 24 },
            { 5, 12, 14, 20 },
            { 2, 13, 23, 24 },
            { 11, 16, 24, 24 },

            { 15, 17, 19, 24 },
            { 12, 16, 24, 24 },
            { 10, 19, 24, 24 },
            { 16, 18, 20, 22 },

            { 13, 19, 24, 24 },
            { 9, 22, 24, 24 },
            { 19, 21, 23, 24 },
            { 14, 22, 24, 24 }
          };

    // Array für Mühle
    int array_m[24][4] = {
        { 1, 2, 9, 21 },
        { 0, 2, 4, 7 },
        { 0, 1, 14, 23 },
        { 4, 5, 10, 18 },

        { 1, 7, 3, 5 },
        { 3, 4, 13, 20 },
        { 7, 8, 11, 15 },
        { 1, 4, 6, 8 },

        { 6, 7, 12, 17 },
        { 0, 21, 10, 11 },
        { 3, 18, 9, 11 },
        { 6, 15, 9, 10 },

        { 8, 17, 13, 14 },
        { 5, 20, 12, 14 },
        { 2, 23, 12, 13 },
        { 6, 11, 16, 17 },

        { 15, 17, 19, 22 },
        { 8, 12, 15, 16 },
        { 3, 10, 19, 20 },
        { 16, 22, 18, 20 },

        { 5, 13, 18, 19 },
        { 0, 9, 22, 23 },
        { 16, 19, 21, 23 },
        { 2, 14, 21, 22 }
      };

    // Array für Bewegung des STeins
    int bot_array_3[4]{0};

    // Welcher Spieler dran ist
    int Spieler_1 = 0;
    int Spieler_2 = 0;


    /* Programmfunktionen */

    // Gibt die Bewegungsfreiheit einer Zahl an
    bool bewegungsfreiheit(int a);

    // schaut, ob für ein Feld eine Möglichkeit besteht sich zu bewegen und enabled die
    void bewegung_empty(int a);
    void bewegung_empty_bot(int a);

    // schaut ob eine Mühle möglich ist
    bool muehle(int a);

    // enabled alle Felder die einen bestimmten Status besitzen und der Rest wird gesperrt
    void enable(int a);

    // dort wird entschieden ob 2 Spieler oder 1 Spieler aufgerufen wird
    void Modus(int a);

    // schaltet die Felder frei, die beim nächsten Zug des Gegners verschiebbar sind (sind grün umrandet)
    void freischalten();
    void freischalten_bot();

    // gibt den Spielstand aus und sperrt die restlichen Felder
    void Spielstand(int c);

    // Programm für einen Spieler, also mit Bot
    void Programm_1_Spieler();

    // Programm für 2 Spieler
    void Programm_2_Spieler();

private slots:

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
