#include "minesweeper2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minesweeper2 w;
    w.show();
    return a.exec();
}
