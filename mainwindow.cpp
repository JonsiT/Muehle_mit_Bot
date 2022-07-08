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
#include <QTextBrowser>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Windowname festlegen
    MainWindow::setWindowTitle("Muehle");
    // Appicon
    QApplication::setWindowIcon(QIcon(":/images/Stein_braun.png"));
    // 24 ist ein Alibiwert
    Status[24] = 1;

    // Spielstand anzeigen
    QTextBrowser *textBrowser = findChild<QTextBrowser*>("Output");
    textBrowser->setHtml(
                         "<p style=font-size:22pt;>Spielstand:</p>"
                         "<p style=font-size:22pt;>Spieler 1: " + QString::number(Sieg_Spieler_1) + "</p>"
                         "<p style=font-size:22pt;>Spieler 2: " + QString::number(Sieg_Spieler_2) + "</p>"
                         );
}


MainWindow::~MainWindow()
{
    delete ui;
}

// Beendet das Programm sofort
void MainWindow::on_Beenden_clicked()
{
    QApplication::quit();

    // Spielstand wird in eine Datei abgespeichert
    QFile file("Spielergebnis.txt");
    if(!file.open(QIODevice::ReadWrite))
    {
        qCritical() << "Could not open file!";
        qCritical() << file.errorString();
        return;
    }

    qInfo() << "Writing file ...";
    file.write(QByteArray("Spielergebnis: \n"
                          "Spieler 1: " + QByteArray::number(Sieg_Spieler_1) + "\n"
                          "Spieler 2: " + QByteArray::number(Sieg_Spieler_2) + "\n"
               )
            );
    file.flush();

    qInfo() << "Reading file ...";
    file.seek(0);

    file.close();
}

// Resettet alle notwendigen Parameter
void MainWindow::on_Resetten_clicked(){

    for (int e=0; e<=23; e++){
          // Felder werden auf schwarz zurueckgesetzt
          QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(e));
          field->setStyleSheet("QPushButton { border: 1px solid black; background-color: black;}\n");
          field->setEnabled(true);
          // Werte der Felder werden auf 0 zurueckgesetzt
          Status[e] = 0;
    }

    // Spieler 1 beginnt wieder
    ui->background_Spieler_1->setStyleSheet("QFrame#background_Spieler_1{border: 2px solid red;}");
    ui->background_Spieler_2->setStyleSheet("QFrame#background_Spieler_2{border: none;}");

    // Variablen werden zurueckgesetzt

    // Zaehlvariablen
    i = 0;
    bot_anzahl = 0;
    anzahl_verfuegbar = 0;

    // zaehlt die Zuege
    count = 0;

    // gibt an welcher Spieler am Zug ist
    zuege = 0;

    // Weitergabe von Feldnummern
    number_1 = 0;
    number_2 = 0;

    // bringt zusaetzliche Ablaeufe ins Spiel
    auswahl = 0;

    // Wie viele Steine der aktuelle Spieler hat
    state = 0;

    // Wie viele Steine der Gegner hat
    state_gegner = 0;

    // Anzahl der Steine der Spieler
    brown_stones = 0;
    black_stones = 0;
}

/* Programmfunktionen */

bool MainWindow::bewegungsfreiheit(int a){

                // Abfrage, ob ein Stein vertikal oder horizontal um ein Feld bewegt werden kann

                if(Status[array_be[a][0]] == 0 || Status[array_be[a][1]] == 0 || Status[array_be[a][2]] == 0 || Status[array_be[a][3]] == 0){
                    return true;
                }else{
                    return false;
                }
}

void MainWindow::bewegung_empty(int a){

    // Durchlaeuft alle Felder
    for(int p = 0; p <= 23; p++){
        QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(p));
        // Setzt Feld false (Feld kann nicht mehr gecklickt werden), wenn Feld 1 oder 2 ist und Feld nicht erreichbar ist (mehr als ein Feld weg ist)
        // Setzt alle erreichbaren und leeren Felder im Ukreis frei
        field->setEnabled(Status[p] == 0 && (p == array_be[a][0] || p == array_be[a][1] || p == array_be[a][2] || p == array_be[a][3]));
    }
}

void MainWindow::bewegung_empty_bot(int a){

        anzahl_verfuegbar = 0;

        for(int p = 0; p <= 3; p++){
            if(array_be[a][p] != 24){ // 24 ist nur eine Pufferzahl, damit es mim Array funktioniert
                if(Status[array_be[a][p]] == 0){ // freies Feld in der Umgebung
                    bot_array_3[anzahl_verfuegbar] = array_be[a][p]; // Werte werden gespeichert, wo der Bot sich hinbewegen kann
                    anzahl_verfuegbar++;
                }
            }
        }

}

bool MainWindow::muehle(int a){

    // Abfrage zu 3 in einer linie
    // gerader Zug zeigt Spieler 1 und ungerader Zug Spieler 2 an
    if(zuege == 0){
        Spieler_1 = 1; // Ich
        Spieler_2 = 2; // Gegner
    }else{
        Spieler_2 = 1; // Gegner
        Spieler_1 = 2; // Ich
    }

    if((Status[array_m[a][0]] == Spieler_1 && Status[array_m[a][1]] == Spieler_1) || (Status[array_m[a][2]] == Spieler_1 && Status[array_m[a][3]] == Spieler_1)){
        return true;
    }else{
        return false;
    }
}

void MainWindow::enable(int a){
    // a legt die Felder fest, die enabled werden sollen, der Rest wird disabled
    for(int u = 0; u <= 23; u++){
        QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(u));
        if(Status[u] == a){
            field->setEnabled(true);
        }else{
            field->setEnabled(false);
        }
    }
}

void MainWindow::freischalten(){

    // Solange die Zuege groeßer als 18 sind (die Anfangsphase uebersprungen worden ist) und der Gegner mehr als 3 Steine besitzt
    if(count >=18 && state_gegner > 3){

        // Es werden die Steine des Gegners, also fuer den naechsten Zug, freigeschalten die bewegt werden koennen
        // Es wird geschaut, ob auf dem Feld der Stein des Gegners liegt und, ob dieser in seiner Range sich bewegen koennte
    for(int o = 0; o <= 23; o++){
        QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
        if(zuege != 0){
            if(Status[o] == 1 && bewegungsfreiheit(o) == true){
                field_1->setEnabled(true);
                // Gruen werden die Steine bewegt, die sich bewegen koennten
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
            }else{
                if(Status[o] == 2){
                    // Der Rest bleibt
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                }

                field_1->setEnabled(false);
            }
        }else{
            if(Status[o] == 2 && bewegungsfreiheit(o) == true){
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
    // kommt zum Einsatz, wenn der Gegner == 3 Steine hat
    else{
        // Es werden die Steine des Gegners, also fuer den naechsten Zug, freigeschalten die bewegt werden koennen
        // Hierbei spielt, auf Grund der Sprungphase, die bewegungsfreiheit keine Rolle
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
                    }
                    field_1->setEnabled(false);
                }

             }
        }
    }
}

void MainWindow::freischalten_bot(){

    // aus der Setzphase draußen und Gegner mehr als 3 Steine
    // gleiche Funktion wie freischalten, nur dass es sich ausschließlich auf Spieler 1 bezieht
    // Der Bot erfaehrt andere Auswahlkriterien, wie welcher Stein ausgewaehlt wird
    if(count >= 17 && state_gegner > 3){
    for(int o = 0; o <= 23; o++){
        QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
            if(Status[o] == 1){
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                if(bewegungsfreiheit(o) == true){
                    field_1->setEnabled(true);
                    field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                }
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

void MainWindow::Spielstand(int c){
    // Wenn weniger als 3 Steine eines Spielers auf dem Feld sind ist das Spiel vorbei
       for(int o = 0; o <= 23; o++){
           QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
           // Alle Felder werden gesperrt
           field_1->setEnabled(false);
       }

       if(c == 0){
           Sieg_Spieler_1++;
       }else{
           Sieg_Spieler_2++;
       }

       // Spielstand wird aktualisiert
       QTextBrowser *textBrowser = findChild<QTextBrowser*>("Output");
       textBrowser->setHtml(
                            "<p style=font-size:22pt;>Spielstand:</p>"
                            "<p style=font-size:22pt;>Spieler 1: " + QString::number(Sieg_Spieler_1) + "</p>"
                            "<p style=font-size:22pt;>Spieler 2: " + QString::number(Sieg_Spieler_2) + "</p>"
                            );
}
/* Programm */

void MainWindow::Programm_2_Spieler(){

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

        // Das ausgewaehlte Feld brown_stonesd mit einer Nummer versehen und vorerst fuer weitere Eingaben gesperrt
        if(zuege == 0){
            Status[number_1] = 1;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
        }else{
            Status[number_1] = 2;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
        }

        // button vorerst außer Kraft setzen
        buttonSender_1->setEnabled(false);

        // Setzt die Felder frei, die als naechstes angeclickt werden koennen
        if(count == 17){
            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                    if(Status[o] == 1 && bewegungsfreiheit(o) == true){
                        field_1->setEnabled(true);
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                    }else{
                        field_1->setEnabled(false);
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

        brown_stones = 0;
        black_stones = 0;

        // zaehlt wie viele Felder von uns und dem Gegner noch auf dem Feld sind
        for(int a = 0; a <= 23; a++){
            if(Status[a] == 1){
                brown_stones++;
            }else if(Status[a] == 2){
                black_stones++;
            }
        }

        if(zuege == 0){
            state = brown_stones;
            state_gegner = black_stones;
        }else{
            state = black_stones;
            state_gegner = brown_stones;
        }


     // Solange die Felder des Spielers groeßer als 3 sind, dann sind brown_stones in Stage 1
     if(state > 3){

        if(auswahl == 0){

            // Der gecklickte Stein bekommt einen roten Rand und dieser muss auch bewegt werden
            if(zuege == 0){
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
            }else{
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
            }

            /*
             * Button ausgewaehlt, nun alle sperren, die nicht fuer die Bewegung infrage kommen
             */

            bewegung_empty(number_1);

            // Fuer den Wechsel von Buttons muss die erste Buttonnummer weitergegeben werden
            number_2 = number_1;
            auswahl++;

        }else if(auswahl == 1){
            /*
             * Wechselbutton auswaehlen
             */

            // number_2 ist der vorherige Button
            // Status des vorherigen Buttons wird 0 gesetzt
            Status[number_2] = 0;
            QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));

            if(zuege == 0){
                Status[number_1] = 1;
                // vorheriger Button wird wieder zu einem leeren Feld
                vorherigerButton->setStyleSheet("QPushButton { image: none}");

                // jetziger Button wird vom leeren Feld zum beestzten Feld
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
            }else{
                Status[number_1] = 2;
                vorherigerButton->setStyleSheet("QPushButton { image: none}");
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");
            }

            // es wird geschaut, ob sich durch das Bewegen eine Muehle gebildet hat
            if(muehle(number_1) == true){
                enable(Spieler_2);
                auswahl++;
            }else{
                auswahl = 0;
                freischalten();
            }


        // Auswahl 2 ist die Eliminationsphase
        }else if(auswahl == 2){
            buttonSender_1->setStyleSheet("QPushButton { image: none}");
            Status[number_1] = 0;
            auswahl = 0;
            freischalten();

            if(state_gegner == 3){
                Spielstand(zuege);
            }
        }

}


        /*
         * Stage 2 Start
         */

     // Wenn nur noch 3 Steine des Spielers uebrig sind kommt dieser in die 2 Stage (Endphase)
        else if(state == 3){
            if(auswahl == 0){

                if(zuege == 0){
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }else{
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }

                /*
                 * Button ausgewaehlt, nun alle sperren, die nicht fuer die Bewegung infrage kommen
                 */

                // Alle freimachen außer die leeren Felder
                enable(0);

                number_2 = number_1;
                auswahl++;

            }else if(auswahl == 1){
                /*
                 * Wechselbutton auswaehlen
                 */

                // number_2 ist der vorherige Button
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

                if(muehle(number_1) == true){
                    enable(Spieler_2);
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
                if(state_gegner == 3){
                    Spielstand(zuege);
                }
            }

        }else {

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
}else{/* ueberspringen, da zwei clicks vom Spieler notwendig ist */}
}

void MainWindow::Programm_1_Spieler(){

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

        // Das ausgewaehlte Feld brown_stonesd mit einer Nummer versehen und vorerst fuer weitere Eingaben gesperrt

            Status[number_1] = 1;
            buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");


        // button vorerst außer Kraft setzen
        buttonSender_1->setEnabled(false);

        if(count == 16){
            for(int o = 0; o <= 23; o++){
                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(o));
                if(zuege == 0){
                    if(Status[o] == 1 && bewegungsfreiheit(o) == true){
                        field_1->setEnabled(true);
                        field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid green}");
                    }else{
                        field_1->setEnabled(false);
                    }
                    brown_stones = 0;
                    black_stones = 0;

                    for(int a = 0; a <= 23; a++){
                        if(Status[a] == 1){
                            brown_stones++;
                        }else if(Status[a] == 2){
                            black_stones++;
                        }else{}
                    }

                    if(zuege == 0){
                        state = brown_stones;
                        state_gegner = black_stones;
                    }else{
                        state = black_stones;
                        state_gegner = brown_stones;
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

        brown_stones = 0;
        black_stones = 0;

        for(int a = 0; a <= 23; a++){
            if(Status[a] == 1){
                brown_stones++;
            }else if(Status[a] == 2){
                black_stones++;
            }else{}
        }

        if(zuege == 0){
            state = brown_stones;
            state_gegner = black_stones;
        }else{
            state = black_stones;
            state_gegner = brown_stones;
        }


        if(state > 3){
            if(auswahl == 0){

                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");

               /*
                * Button ausgewaehlt, nun alle sperren, die nicht fuer die Bewegung infrage kommen
                */
                bewegung_empty(number_1);

                number_2 = number_1;
                auswahl++;

            }else if(auswahl == 1){

            /*
             * Wechselbutton auswaehlen
             */

            // number_2 ist der vorherige Button
            Status[number_2] = 0;
            QPushButton *vorherigerButton = findChild<QPushButton*>("Feld_" +QString::number(number_2));


                Status[number_1] = 1;
                //vorheriger Button wird zu einem leeren Feld
                vorherigerButton->setStyleSheet("QPushButton { image: none}");

                // jetziger Button wird mit dem vorherigen Button getauscht
                buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px;}");

                // hat sich eine Muehle gebildet
            if(muehle(number_1) == true){
                // bei Muehle darf der Spieler einen beliebigen Stein des Gegners entfernen
                enable(Spieler_2); // Nur die Steine des Gegners freischalten
                auswahl++;
            }else{
                auswahl = 0;
            }



        }else if(auswahl == 2){
            // Den gegnersichen Stein ausgewaehlt und auf null gesetzt (geloescht)
            buttonSender_1->setStyleSheet("QPushButton { image: none}");
            Status[number_1] = 0;
            auswahl = 0;

            if(state_gegner == 3){
                Spielstand(zuege);
            }
        }

}


        /*
         * Stage 2 Start
         */

        // Wenn nur noch 3 Steine des Spielers uebrig sind (Endphase)
        else if(state == 3){

            if(auswahl == 0){

                if(zuege == 0){
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_braun.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }else{
                    buttonSender_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px; border: 2px solid red}");
                }

                /*
                 * Button ausgewaehlt, nun alle sperren, die nicht fuer die Bewegung infrage kommen
                 */

                enable(0); // Der Stein kann in der Endphase auf jedes leere Feld springen

                number_2 = number_1;
                auswahl++;

            }else if(auswahl == 1){

                /*
                 * Wechselbutton auswaehlen
                 */

                // number_2 ist der vorherige Button
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

                if(muehle(number_1) == true){
                    enable(Spieler_2);
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
                if(state_gegner == 3){
                    Spielstand(zuege);
                }
            }

        }else{}
}
        /*
         * Stage 1 Ende
         */


// Bot
    if(auswahl == 0){
        //Wenn Bot am Zug ist
        // Zaehler weiterfuehren, fuer fortlaufendes Programm und uebersicht relevant
        count ++;

        zuege = count%2;

        // Anzahl der braunen und schwarzen Steine auf dem Spielfeld
        brown_stones = 0;
        black_stones = 0;

        for(int a = 0; a <= 23; a++){
            if(Status[a] == 1){
                brown_stones++;
            }else if(Status[a] == 2){
                black_stones++;
            }else{}
        }

        if(zuege == 0){
            state = brown_stones;
            state_gegner = black_stones;
        }else{
            state = black_stones;
            state_gegner = brown_stones;
        }


        // Wenn weniger als 17 Zuege gespielt wurden befinden wir uns noch in Stage 1
            if(count <= 17){
                bot_anzahl = 0;
                int bot_array[23]{0};

                // Abfragen, welche Felder frei sind
                for(int o = 0; o <= 23; o++){
                    if(Status[o] == 0){
                        bot_array[bot_anzahl] = o;
                        bot_anzahl++;
                    }
                }

                // Zufaellig ein Feld auswaehlen
                int random_wert;
                int wi = bot_anzahl;
                random_wert = rand() % wi;

                // Feld mit Wert 2 und schwarzem Stein belegen
                Status[bot_array[random_wert]] = 2;

                QPushButton *field_1 = findChild<QPushButton*>("Feld_" + QString::number(bot_array[random_wert]));
                field_1->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");

                if(count==17){
                    freischalten_bot();
                }else{
                    enable(0);
                }

            }


            // Wenn mehr als 17 Zuege gespielt worden sind befinden wir uns unweigerlich in Stage 2
           else if(count > 17){
                bot_anzahl = 0;
                int bot_array[23]{0};

                if(state > 3){
                    // Abfragen, welche Steine zum Bot gehoert

                    for(int o = 0; o <= 23; o++){
                        if(Status[o] == 2){
                            bot_array[bot_anzahl] = o;
                            bot_anzahl++;
                        }
                    }

                    i = 0;
                    int bot_array_2[23]{0};

                    for(int o = 0; o < bot_anzahl; o++){
                    // Welche Steine koennen bewegt werden
                        if(bewegungsfreiheit(bot_array[o]) == true){
                                bot_array_2[i] = bot_array[o];
                                i++;
                        }else{}
                    }


                    // Stein auswaehlen

                    int random_wert_2;
                    random_wert_2 = rand() % i;

                    // der vom Bot ausgewaehlte Stein wird daraufhin resettet
                    QPushButton *field_2 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_2[random_wert_2]));
                    field_2->setStyleSheet("QPushButton { image: none}");
                    Status[bot_array_2[random_wert_2]] = 0;

                    // Abfragen, wohin der Stein bewegt werden koennen

                    bewegung_empty_bot(bot_array_2[random_wert_2]);


                    // Stein an eine random Stelle hinbewegen

                    int random_wert_3;
                    random_wert_3 = rand() % anzahl_verfuegbar;

                    // Bewegung des Steins und der Parametern an die gewuenschte Stelle
                    QPushButton *field_3 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_3[random_wert_3]));
                    field_3->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                    Status[bot_array_3[random_wert_3]] = 2;

                    // Wenn sich zufaellig eine Muehle ergibt
                    if(muehle(bot_array_3[random_wert_3]) == true){
                        // moegliche Steine des Gegners werden lokalisiert
                        int bot_array_5[23] {0};
                        i = 0;
                        for(int o = 0; o <= 23; o++){
                            if(Status[o] == 1){
                                bot_array_5[i] = o;
                                i++;
                            }
                        }

                        // Random Stein des Gegners wird ausgewaehlt
                        int random_wert_speil;
                        random_wert_speil = rand() % i;

                        // Stein des Gegners wird resettet
                        QPushButton *field_5 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_5[random_wert_speil]));
                        field_5->setStyleSheet("QPushButton { image: : none}");
                        Status[bot_array_5[random_wert_speil]] = 0;

                        // Spielstand wird aktualisiert und alle Felder werden blockiert
                        if(state_gegner == 3){
                            Spielstand(zuege);
                        }

                    }

                    freischalten_bot();
                }

                else if(state == 3){
                        // Abfragen, welche Steine bewegt werden koennen
                        i = 0;
                        int bot_array_4[23]{0};

                        for(int o = 0; o <= 23; o++){
                            // Welche Steine gehoeren dem Bot
                            if(Status[o] == 2){
                                bot_array_4[i] = o;
                                i++;
                            }
                        }


                        // Stein auswaehlen

                        int random_wert_2;
                        random_wert_2 = rand() % i;

                        // Abfragen, wohin der Stein bewegt werden koennen
                        i=0;
                        int bot_array_3[23]{0};
                        for(int o = 0; o <= 23; o++){
                            // Beliebiges leeres Feld wird gesucht
                            if(Status[o] == 0){
                                bot_array_3[i] = o;
                                i++;
                            }
                        }

                        // Alte Position loeschen

                        QPushButton *field_2 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_4[random_wert_2]));
                        field_2->setStyleSheet("QPushButton { image: none}");
                        Status[bot_array_4[random_wert_2]] = 0;

                        // Stein an eine Stelle hinbewegen

                        int random_wert_3;
                        random_wert_3 = rand() % i;

                        // Neue Position beziehen

                        QPushButton *field_3 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_3[random_wert_3]));
                        field_3->setStyleSheet("QPushButton { image: url(:/images/Stein_schwarz.png);background-color:none;min-height: 60px;max-height: 60px;min-width: 60px;max-width: 60px}");
                        Status[bot_array_3[random_wert_3]] = 2;

                        // Wenn sich zufaellig eine Muehle ergibt
                        if(muehle(bot_array_3[random_wert_3]) == true){
                            // moegliche Steine des Gegners werden lokalisiert
                            int bot_array_5[23] {0};
                            i = 0;
                            for(int o = 0; o <= 23; o++){
                                if(Status[o] == 1){
                                    bot_array_5[i] = o;
                                    i++;
                                }
                            }

                            // Random Stein des Gegners wird ausgewaehlt
                            int random_wert_speil;
                            random_wert_speil = rand() % i;

                            // Stein des Gegners wird resettet
                            QPushButton *field_5 = findChild<QPushButton*>("Feld_" + QString::number(bot_array_5[random_wert_speil]));
                            field_5->setStyleSheet("QPushButton { image: : none}");
                            Status[bot_array_5[random_wert_speil]] = 0;

                            // Spielstand wird aktualisiert und alle Felder werden blockiert
                            if(state_gegner == 3){
                                Spielstand(zuege);
                            }

                        }

                        freischalten_bot();


                }else{
                    // Bei weniger als 3 Steine ist das SPiel vorbei und alle Felder werden geblockt
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

    count++;

}else{/* ueberspringen, da zwei clicks vom Spieler notwendig ist */ }



}

void MainWindow::Modus(int a){
    if(a == 0){
        Programm_2_Spieler();
    }else{
        Programm_1_Spieler();
    }
}

/* Felder */

void MainWindow::on_Feld_0_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_1_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_2_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_3_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_4_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_5_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_6_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_7_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_8_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_9_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_10_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_11_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_12_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_13_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_14_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_15_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_16_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_17_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_18_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_19_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_20_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_21_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_22_clicked(){
    Modus(bot);
}
void MainWindow::on_Feld_23_clicked(){
    Modus(bot);
}
