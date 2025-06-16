#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This sets up any elements defined in the .ui file

    Board* b = new Board(EASY, ui->boardParentWidget);

    QObject::connect(b, SIGNAL(gameStarted()), ui->stopwatchLcd, SLOT(startClock()));
    QObject::connect(b, SIGNAL(gameLost()), ui->stopwatchLcd, SLOT(stopClock()));
    QObject::connect(b, SIGNAL(gameWon()), ui->stopwatchLcd, SLOT(stopClock()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
