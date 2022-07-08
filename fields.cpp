/*#include "fields.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

fields::fields()
{

}

using namespace std;


// welche Felder freigeschalten werden sollen
void enable(const char* a){
    for(int u = 0; u <= 23; u++){
        QPushButton *field = findChild<QPushButton*>("Feld_" +QString::number(u));
        if((a == "empty" && MainWindow::Status[u] == 0) || (a == "Spieler_1" && Status[u] == 1) || (a == "Spieler_2" && Status[u] == 2)){
            field->setEnabled(true);
        }else{
            field->setEnabled(false);
        }
    }
}



// Die passenden Züge nach bewegungsfreiheit ...
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
*/
