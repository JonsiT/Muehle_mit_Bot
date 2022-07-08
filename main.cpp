#include "mainwindow.h"
#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Welches Window soll als erstes geöffnet werden
    StartWindow w;
    w.show();
    return a.exec();
}
