#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This sets up any elements defined in the .ui file

    QTimer* timer = new QTimer(this);
    Board* b = new Board(EASY, ui->boardParentWidget);

    QObject::connect()

}

MainWindow::~MainWindow()
{
    delete ui;
}
