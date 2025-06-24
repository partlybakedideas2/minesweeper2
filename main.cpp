#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setStyleSheet("Tile {background-color: rgb(25, 178, 255); font: bold 20px}"
                    //"Tile:hover {background-color: rgb(0,0,255)}"
                    //"Tile:pressed {background-color: rgb(209, 209, 209)}" );
                    "Tile:disabled {background-color: rgb(209, 209, 209)}");

    w.show();
    return a.exec();
}
