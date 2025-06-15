#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This sets up any elements defined in the .ui file

    Board* b = new Board(EASY, this); // Create the board object on the heap

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(b); // Add the board to the layout
    setLayout(layout); // Set the layout for the Minesweeper2 window
}

MainWindow::~MainWindow()
{
    delete ui;
}
