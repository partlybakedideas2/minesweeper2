#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , gameBoard(nullptr)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    ui->setupUi(this); // This sets up any elements defined in the .ui file

    gameBoard = new Board(EASY, this);

    this->layout()->addWidget(gameBoard);

    QObject::connect(gameBoard, SIGNAL(gameStarted()), ui->stopwatchLcd, SLOT(startClock()));
    QObject::connect(gameBoard, SIGNAL(gameLost()), ui->stopwatchLcd, SLOT(stopClock()));
    QObject::connect(gameBoard, SIGNAL(gameWon()), ui->stopwatchLcd, SLOT(stopClock()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    this->layout()->removeWidget(gameBoard);

    if (gameBoard != nullptr) {
        gameBoard->disconnect(SIGNAL(gameStarted()));
        gameBoard->disconnect(SIGNAL(gameLost()));
        gameBoard->disconnect(SIGNAL(gameWon()));
        delete gameBoard;
        gameBoard = nullptr;
    }

    GameLevel newLevel;
    if (ui->levelSelectDial->value() < 10) {
        newLevel = EASY;
    }
    else if (ui->levelSelectDial->value() < 20) {
        newLevel = MEDIUM;
    }
    else {
        newLevel = HARD;
    }

    gameBoard = new Board(newLevel, this);
    this->layout()->addWidget(gameBoard);

    QObject::connect(gameBoard, SIGNAL(gameStarted()), ui->stopwatchLcd, SLOT(startClock()));
    QObject::connect(gameBoard, SIGNAL(gameLost()), ui->stopwatchLcd, SLOT(stopClock()));
    QObject::connect(gameBoard, SIGNAL(gameWon()), ui->stopwatchLcd, SLOT(stopClock()));

    currentUser = ui->usernameLineEdit->text();
}


void MainWindow::on_levelSelectDial_valueChanged(int value)
{
    if (ui->levelSelectDial->value() < 10) {
        ui->levelSelectLabel->setText("EASY");
    }
    else if (ui->levelSelectDial->value() < 20) {
        ui->levelSelectLabel->setText("MEDIUM");
    }
    else {
        ui->levelSelectLabel->setText("HARD");
    }

}

