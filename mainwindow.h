#ifndef MINESWEEPER2_H
#define MINESWEEPER2_H

#include <QWidget>
#include <QString>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();

    void on_levelSelectDial_valueChanged(int value);

private:
    void generateNewGame();

    Ui::MainWindow *ui;
    QString currentUser;
    Board* gameBoard;

};
#endif // MINESWEEPER2_H
