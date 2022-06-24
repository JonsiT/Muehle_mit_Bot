#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QWindow>
#include <QThread>
#include <iostream>
#include <stdlib.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Mühle");

    // 24 ist ein Alibiwert
    Status[24] = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Beenden_clicked()
{
    QApplication::quit();
}

// keine Stages notwendig
void MainWindow::on_Resetten_clicked(){

    for (int e=0; e<=23; e++){
          // Felder werden auf schwarz zurückgesetzt
          QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(e));
          field->setStyleSheet("QPushButton { border: 1px solid black; background-color: black;}\n");
          field->setEnabled(true);
          // Werte der Felder werden auf 0 zurückgesetzt
          Status[e] = 0;
    }

    // Spieler 1 beginnt wieder
    ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1{border: 2px solid red;}");
    ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2{border: none;}");

    // zurücksetzen der Züge
    count = 0;

    // zurücksetzen der Stages
    stage = 0;

    auswahl = 0;
}

/* Programmfunktionen*/

bool MainWindow::bewegungsfreiheit_1(int a, int b, int c, int d){

    if(Status[a] == 0 || Status[b] == 0 || Status[c] == 0 || Status[d] == 0){
        return true;
    }else{
        return false;
    }
}

bool MainWindow::bewegungsfreiheit_2(int nummer){

    // Abfrage der Bewegungsfreiheit
       switch(nummer) {
          case 0:
            wort = bewegungsfreiheit_1(1, 9, 24, 24);
            break;
          case 1:
            wort = bewegungsfreiheit_1(0, 2, 4, 24);
            break;
          case 2:
            wort = bewegungsfreiheit_1(1, 14, 24, 24);
            break;
          case 3:
            wort = bewegungsfreiheit_1(4, 10, 24, 24);
            break;
          case 4:
            wort = bewegungsfreiheit_1(1, 3, 5, 7);
            break;
          case 5:
            wort = bewegungsfreiheit_1(4, 13, 24, 24);
            break;
          case 6:
            wort = bewegungsfreiheit_1(7, 11, 24, 24);
            break;
          case 7:
            wort = bewegungsfreiheit_1(4, 6, 8, 24);
            break;
          case 8:
            wort = bewegungsfreiheit_1(7, 12, 24, 24);
            break;
          case 9:
            wort = bewegungsfreiheit_1(0, 10, 21, 24);
            break;
          case 10:
            wort = bewegungsfreiheit_1(3, 9, 11, 18);
            break;
          case 11:
            wort = bewegungsfreiheit_1(6, 10, 15, 24);
            break;
          case 12:
            wort = bewegungsfreiheit_1(8, 13, 17, 24);
            break;
          case 13:
            wort = bewegungsfreiheit_1(5, 12, 14, 20);
            break;
          case 14:
            wort = bewegungsfreiheit_1(2, 13, 23, 24);
            break;
          case 15:
            wort = bewegungsfreiheit_1(11, 16, 24, 24);
            break;
          case 16:
            wort = bewegungsfreiheit_1(15, 17, 19, 24);
            break;
          case 17:
            wort = bewegungsfreiheit_1(12, 16, 24, 24);
            break;
          case 18:
            wort = bewegungsfreiheit_1(10, 19, 24, 24);
            break;
          case 19:
            wort = bewegungsfreiheit_1(16, 18, 20, 24);
            break;
          case 20:
            wort = bewegungsfreiheit_1(13, 19, 24, 24);
            break;
          case 21:
            wort = bewegungsfreiheit_1(9, 22, 24, 24);
            break;
          case 22:
            wort = bewegungsfreiheit_1(19, 21, 23, 24);
            break;
          case 23:
            wort = bewegungsfreiheit_1(14, 22, 24, 24);
            break;

          default:;

        }

       return wort;
}

void MainWindow::bewegung_empty_1_bot(int a, int b, int c, int d){
    anzahl_verfuegbar = 0;
    int arr[4] = {a,b,c,d};

    for(int p = 0; p <= 3; p++){
        if(arr[p] != 24){
            if(Status[arr[p]] == 0){
                bot_array_3[anzahl_verfuegbar] = arr[p];
                anzahl_verfuegbar++;
            }else{

            }
        }else{}
    }
}

void MainWindow::bewegung_empty_2_bot(int a){
    switch(a){
          case 0:
            bewegung_empty_1_bot(1, 9, 24, 24);
            break;
          case 1:
            bewegung_empty_1_bot(0, 2, 4, 24);
            break;
          case 2:
            bewegung_empty_1_bot(1, 14, 24, 24);
            break;
          case 3:
            bewegung_empty_1_bot(4, 10, 24, 24);
            break;
          case 4:
            bewegung_empty_1_bot(1, 3, 5, 7);
            break;
          case 5:
            bewegung_empty_1_bot(4, 13, 24, 24);
            break;
          case 6:
            bewegung_empty_1_bot(7, 11, 24, 24);
            break;
          case 7:
            bewegung_empty_1_bot(4, 6, 8, 24);
            break;
          case 8:
            bewegung_empty_1_bot(7, 12, 24, 24);
            break;
          case 9:
            bewegung_empty_1_bot(0, 10, 21, 24);
            break;
          case 10:
            bewegung_empty_1_bot(3, 9, 11, 18);
            break;
          case 11:
            bewegung_empty_1_bot(6, 10, 15, 24);
            break;
          case 12:
            bewegung_empty_1_bot(8, 13, 17, 24);
            break;
          case 13:
            bewegung_empty_1_bot(5, 12, 14, 20);
            break;
          case 14:
            bewegung_empty_1_bot(2, 13, 23, 24);
            break;
          case 15:
            bewegung_empty_1_bot(11, 16, 24, 24);
            break;
          case 16:
            bewegung_empty_1_bot(15, 17, 19, 24);
            break;
          case 17:
            bewegung_empty_1_bot(12, 16, 24, 24);
            break;
          case 18:
            bewegung_empty_1_bot(10, 19, 24, 24);
            break;
          case 19:
            bewegung_empty_1_bot(16, 18, 20, 24);
            break;
          case 20:
            bewegung_empty_1_bot(13, 19, 24, 24);
            break;
          case 21:
            bewegung_empty_1_bot(9, 22, 24, 24);
            break;
          case 22:
            bewegung_empty_1_bot(19, 21, 23, 24);
            break;
          case 23:
            bewegung_empty_1_bot(14, 22, 24, 24);
            break;

          default:;

        }
}

void MainWindow::bewegung_empty_1(int a, int b, int c, int d){

    for(int p = 0; p <= 23; p++){
        QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(p));
        if(p == a || p == b || p == c || p == d){
            if(Status[p] == 0){
                field->setEnabled(true);
            }else{
                field->setEnabled(false);
            }
        }else{
            field->setEnabled(false);
        }
    }
}

void MainWindow::bewegung_empty_2(int a){
    switch(a){
          case 0:
            bewegung_empty_1(1, 9, 24, 24);
            break;
          case 1:
            bewegung_empty_1(0, 2, 4, 24);
            break;
          case 2:
            bewegung_empty_1(1, 14, 24, 24);
            break;
          case 3:
            bewegung_empty_1(4, 10, 24, 24);
            break;
          case 4:
            bewegung_empty_1(1, 3, 5, 7);
            break;
          case 5:
            bewegung_empty_1(4, 13, 24, 24);
            break;
          case 6:
            bewegung_empty_1(7, 11, 24, 24);
            break;
          case 7:
            bewegung_empty_1(4, 6, 8, 24);
            break;
          case 8:
            bewegung_empty_1(7, 12, 24, 24);
            break;
          case 9:
            bewegung_empty_1(0, 10, 21, 24);
            break;
          case 10:
            bewegung_empty_1(3, 9, 11, 18);
            break;
          case 11:
            bewegung_empty_1(6, 10, 15, 24);
            break;
          case 12:
            bewegung_empty_1(8, 13, 17, 24);
            break;
          case 13:
            bewegung_empty_1(5, 12, 14, 20);
            break;
          case 14:
            bewegung_empty_1(2, 13, 23, 24);
            break;
          case 15:
            bewegung_empty_1(11, 16, 24, 24);
            break;
          case 16:
            bewegung_empty_1(15, 17, 19, 24);
            break;
          case 17:
            bewegung_empty_1(12, 16, 24, 24);
            break;
          case 18:
            bewegung_empty_1(10, 19, 24, 24);
            break;
          case 19:
            bewegung_empty_1(16, 18, 20, 22);
            break;
          case 20:
            bewegung_empty_1(13, 19, 24, 24);
            break;
          case 21:
            bewegung_empty_1(9, 22, 24, 24);
            break;
          case 22:
            bewegung_empty_1(19, 21, 23, 24);
            break;
          case 23:
            bewegung_empty_1(14, 22, 24, 24);
            break;

          default:;

        }
}

bool MainWindow::muehle_1(int a, int b, int c, int d){

    // gerader Zug zeigt Spieler 1 und ungerader Zug Spieler 2 an
    if(zuege == 0){
        zoul = 1; // Ich
        woul = 2; // Gegner
    }else{
        zoul = 2;
        woul = 1;
    }

    if((Status[a] == zoul && Status[b] == zoul) || (Status[c] == zoul && Status[d] == zoul)){
        return true;
    }else{
        return false;
    }

}

bool MainWindow::muehle_2(int nummer){

    // Abfrage zu 3 in einer linie
    switch(nummer) {
       case 0:
         wort = muehle_1(1, 2, 9, 21);
         break;
       case 1:
         wort = muehle_1(0, 2, 4, 7);
         break;
       case 2:
         wort = muehle_1(0, 1, 14, 23);
         break;
       case 3:
         wort = muehle_1(4, 5, 10, 18);
         break;
       case 4:
         wort = muehle_1(1, 7, 3, 5);
         break;
       case 5:
         wort = muehle_1(3, 4, 13, 20);
         break;
       case 6:
         wort = muehle_1(7, 8, 11, 15);
         break;
       case 7:
         wort = muehle_1(1, 4, 6, 8);
         break;
       case 8:
         wort = muehle_1(6, 7, 12, 17);
         break;
       case 9:
         wort = muehle_1(0, 21, 10, 11);
         break;
       case 10:
         wort = muehle_1(3, 18, 9, 11);
         break;
       case 11:
         wort = muehle_1(6, 15, 9, 10);
         break;
       case 12:
         wort = muehle_1(8, 17, 13, 14);
         break;
       case 13:
         wort = muehle_1(5, 20, 12, 14);
         break;
       case 14:
         wort = muehle_1(2, 23, 12, 13);
         break;
       case 15:
         wort = muehle_1(6, 11, 16, 17);
         break;
       case 16:
         wort = muehle_1(15, 17, 19, 22);
         break;
       case 17:
         wort = muehle_1(8, 12, 15, 16);
         break;
       case 18:
         wort = muehle_1(3, 10, 19, 20);
         break;
       case 19:
         wort = muehle_1(16, 22, 18, 20);
         break;
       case 20:
         wort = muehle_1(5, 13, 18, 19);
         break;
       case 21:
         wort = muehle_1(0, 9, 22, 23);
         break;
       case 22:
         wort = muehle_1(6, 19, 21, 23);
         break;
       case 23:
         wort = muehle_1(2, 14, 21, 22);
         break;

       default:;

     }

    return wort;
}

void MainWindow::enable(int wow){
    for(int u = 0; u <= 23; u++){
        QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(u));
        if(Status[u] == wow){
            field->setEnabled(true);
        }else{
            field->setEnabled(false);
        }
    }
}

void MainWindow::freischalten(){
    if(count >=18 && state_gegner > 3){
    for(int o = 0; o <= 23; o++){
        QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
        if(zuege != 0){
            if(Status[o] == 1 && bewegungsfreiheit_2(o) == true){
                field_1->setEnabled(true);
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
            }else{
                if(Status[o] == 2){
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                }

                field_1->setEnabled(false);
            }
        }else{
            if(Status[o] == 2 && bewegungsfreiheit_2(o) == true){
                field_1->setEnabled(true);
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
            }else{
                if(Status[o] == 1){
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                }
                field_1->setEnabled(false);
             }
          }
       }
    }
    else{

        for(int o = 0; o <= 23; o++){
            QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
            if(zuege != 0){
                if(Status[o] == 1){
                    field_1->setEnabled(true);
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                }else{
                    if(Status[o] == 2){
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                    }

                    field_1->setEnabled(false);
                }
            }else{
                if(Status[o] == 2){
                    field_1->setEnabled(true);
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                }else{
                    if(Status[o] == 1){
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                        field_1->setEnabled(false);
                    }
                    field_1->setEnabled(false);
                }

             }
        }
    }
}

void MainWindow::freischalten_bot(){


    if(count >= 17 && state_gegner > 3){
    for(int o = 0; o <= 23; o++){
        QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
            if(Status[o] == 1 && bewegungsfreiheit_2(o) == true){
                field_1->setEnabled(true);
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
            }else{
                field_1->setEnabled(false);
            }

       }
    }else{

        for(int o = 0; o <= 23; o++){
            QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
            if(zuege != 0){
                if(Status[o] == 1){
                    field_1->setEnabled(true);
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                }else{

                    field_1->setEnabled(false);
                }
            }else{

             }
        }
    }
}

/* Programm */

void MainWindow::Programm(){

    // Um herauszufinden welcher Spieler dran ist
    zuege = count%2;

    // retrieve the button you have clicked
    QPushButton* buttonSender_1 = qobject_cast<QPushButton*>(sender());

    // Zahl aus dem Namen ausfindig machen
    QString zahl_1 = buttonSender_1->objectName();
    QByteArray ba_1 = zahl_1.toLocal8Bit();
    string c_zahl_1 = ba_1.data();

    // erase Feld_
    c_zahl_1.erase(0,5);

    //gibt die Feldnummer aus
    number_1 = stoi(c_zahl_1);

    /*
     * Stage 0 Start
     */

    if(count <= 17){

        // Das ausgewählte Feld wird mit einer Nummer versehen und vorerst für weitere Eingaben gesperrt
        if(zuege == 0){
            Status[number_1] = 1;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
        }else{
            Status[number_1] = 2;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
        }

        // button vorerst außer Kraft setzen
        buttonSender_1->setEnabled(false);

        if(count == 17){
            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                if(zuege != 0){
                    if(Status[o] == 1 && bewegungsfreiheit_2(o) == true){
                        field_1->setEnabled(true);
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                    }else{
                        field_1->setEnabled(false);
                    }
                }else{
                    if(Status[o] == 2 && bewegungsfreiheit_2(o) == true){
                        field_1->setEnabled(true);
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                    }else{
                        field_1->setEnabled(false);
                    }
                }
            }
        }
    }

    /*
     * Stage 0 Ende
     */

    /*
     * Stage 1 Start
     */
    else if(count > 17){

        wir = 0;
        ihr = 0;

        for(int a = 0; a <= 23; a++){
            if(Status[a] == 1){
                wir++;
            }else if(Status[a] == 2){
                ihr++;
            }else{}
        }

        if(zuege == 0){
            state = wir;
            state_gegner = ihr;
        }else{
            state = ihr;
            state_gegner = wir;
        }


        if(state > 3){

        if(auswahl == 0){



            if(zuege == 0){
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
            }else{
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
            }

            /*
             * Button ausgewählt, nun alle sperren, die nicht für die Bewegung infrage kommen
             */
            bewegung_empty_2(number_1);

            number_2 = number_1;
            auswahl++;

        }else if(auswahl == 1){
            /*
             * Wechselbutton auswählen
             */

            // nuber_2 ist der vorherige Button
            Status[number_2] = 0;
            QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));

            if(zuege == 0){
                Status[number_1] = 1;
                //vorheriger Button
                vorherigerButton->setStyleSheet("QPushButton { image: none}");

                // jetziger Button
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
            }else{
                Status[number_1] = 2;
                vorherigerButton->setStyleSheet("QPushButton { image: none}");
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
            }

            if(muehle_2(number_1) == true){
                enable(woul);
                auswahl++;
            }else{
                auswahl = 0;
                freischalten();
            }



        }else if(auswahl == 2){
            buttonSender_1->setStyleSheet("QPushButton { image: none}");
            Status[number_1] = 0;
            auswahl = 0;
            freischalten();
        }

}


        /*
         * Stage 2 Start
         */

        else if(state == 3){
            if(auswahl == 0){



                if(zuege == 0){
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }else{
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }

                /*
                 * Button ausgewählt, nun alle sperren, die nicht für die Bewegung infrage kommen
                 */

                enable(0);

                number_2 = number_1;
                auswahl++;

            }else if(auswahl == 1){
                /*
                 * Wechselbutton auswählen
                 */

                // nuber_2 ist der vorherige Button
                Status[number_2] = 0;
                QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));

                if(zuege == 0){
                    Status[number_1] = 1;
                    //vorheriger Button
                    vorherigerButton->setStyleSheet("QPushButton { image: none}");

                    // jetziger Button
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
                }else{
                    Status[number_1] = 2;
                    vorherigerButton->setStyleSheet("QPushButton { image: none}");
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
                }

                if(muehle_2(number_1) == true){
                    enable(woul);
                    auswahl++;
                }else{
                    auswahl = 0;
                    freischalten();
                }



            }else if(auswahl == 2){
                buttonSender_1->setStyleSheet("QPushButton { image: none}");
                Status[number_1] = 0;
                auswahl = 0;
                freischalten();
            }

        }else{

            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                field_1->setEnabled(false);
            }
        }






        /*
         * Stage 2 Ende
         */

    }

    /*
     * Stage 1 Ende
     */

if(auswahl == 0){
    // gerader Zug zeigt Spieler 1 und ungerader Zug Spieler 2 an
    if(zuege == 0){
        ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1 { border: none;}\n");
        ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2 { border: 2px solid red;}\n");
    }else{
        ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1 { border: 2px solid red;}\n");
        ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2 { border: none;}\n");
    }

    count ++;
}else{/* Überspringen, da zwei clicks vom Spieler notwendig ist */}
}

void MainWindow::Programm_bot(){

    // Um herauszufinden wer dran ist
    zuege = count%2;

    // retrieve the button you have clicked
    QPushButton* buttonSender_1 = qobject_cast<QPushButton*>(sender());

    // Zahl aus dem Namen ausfindig machen
    QString zahl_1 = buttonSender_1->objectName();
    QByteArray ba_1 = zahl_1.toLocal8Bit();
    string c_zahl_1 = ba_1.data();

    // erase Feld_
    c_zahl_1.erase(0,5);

    //gibt die Feldnummer aus
    number_1 = stoi(c_zahl_1);

    /*
     * Stage 0 Start
     */

    if(count <= 16){

        // Das ausgewählte Feld wird mit einer Nummer versehen und vorerst für weitere Eingaben gesperrt

            Status[number_1] = 1;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");


        // button vorerst außer Kraft setzen
        buttonSender_1->setEnabled(false);

        if(count == 16){
            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                if(zuege == 0){
                    if(Status[o] == 1 && bewegungsfreiheit_2(o) == true){
                        field_1->setEnabled(true);
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                    }else{
                        field_1->setEnabled(false);
                    }
                    wir = 0;
                    ihr = 0;

                    for(int a = 0; a <= 23; a++){
                        if(Status[a] == 1){
                            wir++;
                        }else if(Status[a] == 2){
                            ihr++;
                        }else{}
                    }

                    if(zuege == 0){
                        state = wir;
                        state_gegner = ihr;
                    }else{
                        state = ihr;
                        state_gegner = wir;
                    }
                }
            }
        }

    }

    /*
     * Stage 0 Ende
     */

    /*
     * Stage 1 Start
     */

    else if(count >= 17){

        wir = 0;
        ihr = 0;

        for(int a = 0; a <= 23; a++){
            if(Status[a] == 1){
                wir++;
            }else if(Status[a] == 2){
                ihr++;
            }else{}
        }

        if(zuege == 0){
            state = wir;
            state_gegner = ihr;
        }else{
            state = ihr;
            state_gegner = wir;
        }


        if(state > 3){

        if(auswahl == 0){




            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");


            /*
             * Button ausgewählt, nun alle sperren, die nicht für die Bewegung infrage kommen
             */
            bewegung_empty_2(number_1);

            number_2 = number_1;
            auswahl++;

        }else if(auswahl == 1){
            /*
             * Wechselbutton auswählen
             */

            // nuber_2 ist der vorherige Button
            Status[number_2] = 0;
            QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));


                Status[number_1] = 1;
                //vorheriger Button
                vorherigerButton->setStyleSheet("QPushButton { image: none}");

                // jetziger Button
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");

            if(muehle_2(number_1) == true){
                enable(woul);
                auswahl++;
            }else{
                auswahl = 0;
            }



        }else if(auswahl == 2){
            buttonSender_1->setStyleSheet("QPushButton { image: none}");
            Status[number_1] = 0;
            auswahl = 0;
        }

}


        /*
         * Stage 2 Start
         */

        else if(state == 3){
            if(auswahl == 0){



                if(zuege == 0){
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }else{
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }

                /*
                 * Button ausgewählt, nun alle sperren, die nicht für die Bewegung infrage kommen
                 */

                enable(0);

                number_2 = number_1;
                auswahl++;

            }else if(auswahl == 1){
                /*
                 * Wechselbutton auswählen
                 */

                // nuber_2 ist der vorherige Button
                Status[number_2] = 0;
                QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));

                if(zuege == 0){
                    Status[number_1] = 1;
                    //vorheriger Button
                    vorherigerButton->setStyleSheet("QPushButton { image: none}");

                    // jetziger Button
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
                }else{
                    Status[number_1] = 2;
                    vorherigerButton->setStyleSheet("QPushButton { image: none}");
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
                }

                if(muehle_2(number_1) == true){
                    enable(woul);
                    auswahl++;
                }else{
                    auswahl = 0;
                    freischalten();
                }



            }else if(auswahl == 2){
                buttonSender_1->setStyleSheet("QPushButton { image: none}");
                Status[number_1] = 0;
                auswahl = 0;
                freischalten();
            }

        }else{

            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                field_1->setEnabled(false);
            }
        }
}
        /*
         * Stage 1 Ende
         */





// Bot
    if(auswahl == 0){
    //Wenn Bot am Zug ist
count ++;

zuege = count%2;

wir = 0;
ihr = 0;

for(int a = 0; a <= 23; a++){
    if(Status[a] == 1){
        wir++;
    }else if(Status[a] == 2){
        ihr++;
    }else{}
}

if(zuege == 0){
    state = wir;
    state_gegner = ihr;
}else{
    state = ihr;
    state_gegner = wir;
}

qDebug()<< "daten";
qDebug()<< state;
qDebug()<< count;

            if(count <= 17){
                bot_anzahl = 0;
                int bot_array[23]{0};

                int i = 0;

                // Abfragen, welche Felder frei sind
                for(int o = 0; o <= 23; o++){
                    if(Status[o] == 0){
                        bot_anzahl++;
                        bot_array[i] = o;
                        i++;
                    }
                }

                int random_wert;
                int wi = bot_anzahl;
                random_wert = rand() % wi;

                Status[bot_array[random_wert]] = 2;

                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(bot_array[random_wert]));
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");

                if(count==17){
                    freischalten_bot();
                }else{
                    enable(0);
                }

            }



           else if(count > 17){
                bot_anzahl = 0;
                int bot_array[23]{0};

                int i = 0;

                if(state > 3){
                    // Abfragen, welche Steine bewegt werden können

                    for(int o = 0; o <= 23; o++){
                        if(Status[o] == 2){
                            bot_anzahl++;
                            bot_array[i] = o;
                            i++;
                        }
                    }

                    i = 0;
                    int bot_array_2[23]{0};

                    for(int o = 0; o < bot_anzahl; o++){

                        if(bewegungsfreiheit_2(bot_array[o]) == true){
                                bot_array_2[i] = bot_array[o];
                                i++;
                        }else{}
                    }


                    // Stein auswählen

                    int random_wert_2;
                    random_wert_2 = rand() % i;


                    QPushButton *field_2 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_2[random_wert_2]));
                    field_2->setStyleSheet("QPushButton { image: none}");
                    Status[bot_array_2[random_wert_2]] = 0;

                    // Abfragen, wohin der Stein bewegt werden können


                    bewegung_empty_2_bot(bot_array_2[random_wert_2]);


                    // Stein an eine Stelle hinbewegen

                    int random_wert_3;
                    random_wert_3 = rand() % anzahl_verfuegbar;


                    QPushButton *field_3 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_3[random_wert_3]));
                    field_3->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                    Status[bot_array_3[random_wert_3]] = 2;

                    if(muehle_2(bot_array_3[random_wert_3]) == true){
                        int bot_array_5[23] {0};
                        i = 0;
                        for(int o = 0; o <= 23; o++){
                            if(Status[o] == 1){
                                bot_array_5[i] = o;
                                i++;
                            }
                        }

                        int random_wert_speil;
                        random_wert_speil = rand() % i;

                        QPushButton *field_5 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_5[random_wert_speil]));
                        field_5->setStyleSheet("QPushButton { image: : none}");
                        Status[bot_array_5[random_wert_speil]] = 0;

                    }

                    freischalten_bot();
                }

                else if(state == 3){
                    qDebug()<< "next lvl";
                        // Abfragen, welche Steine bewegt werden können
                        i = 0;
                        int bot_array_4[23]{0};

                        for(int o = 0; o <= 23; o++){
                            if(Status[o] == 2){
                                bot_array_4[i] = o;
                                i++;
                            }
                        }


                        // Stein auswählen

                        int random_wert_2;
                        random_wert_2 = rand() % i;

                        //QThread::msleep(500);



                        // Abfragen, wohin der Stein bewegt werden können
                        i=0;
                        int bot_array_3[23]{0};
                        for(int o = 0; o <= 23; o++){
                            if(Status[o] == 0){
                                bot_array_3[i] = o;
                                i++;
                            }
                        }

                        QPushButton *field_2 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_4[random_wert_2]));
                        field_2->setStyleSheet("QPushButton { image: none}");
                        Status[bot_array_4[random_wert_2]] = 0;

                        // Stein an eine Stelle hinbewegen

                        int random_wert_3;
                        random_wert_3 = rand() % i;

                        qDebug()<< "Felder wechseln";
                        qDebug()<< bot_array_4[random_wert_2];
                        qDebug()<< bot_array_3[random_wert_3];

                        //QThread::msleep(500);

                        QPushButton *field_3 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_3[random_wert_3]));
                        field_3->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                        Status[bot_array_3[random_wert_3]] = 2;

                        freischalten_bot();


                }else{
                    for(int o = 0; o <= 23; o++){
                        QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                        field_1->setEnabled(false);
                    }
                }



            }

}









if(auswahl == 0){
    // gerader Zug zeigt Spieler 1 und ungerader Zug Spieler 2 an
    if(zuege == 0){
        ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1 { border: none;}\n");
        ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2 { border: 2px solid red;}\n");
    }else{
        ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1 { border: 2px solid red;}\n");
        ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2 { border: none;}\n");
    }

    qDebug()<< "Feld 22";
    qDebug()<< Status[22];
    qDebug()<< "Ende";

    count++;

}else{/* Überspringen, da zwei clicks vom Spieler notwendig ist */ }



}




/* Felder */

void MainWindow::on_Feld_0_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_1_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_2_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_3_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_4_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_5_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_6_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_7_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_8_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_9_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_10_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_11_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_12_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_13_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_14_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_15_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_16_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_17_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_18_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_19_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_20_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_21_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_22_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
void MainWindow::on_Feld_23_clicked(){
    if(bot == 0){
        Programm();
    }else{
        Programm_bot();
    }
}
