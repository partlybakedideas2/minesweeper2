#include "tile.h"
#include "displaystatus.h"
#include <iostream>

Tile::Tile(const int& r, const int& c, QWidget* parent = nullptr)
    : QPushButton(parent)
{
    number = 0;
    status = HIDDEN;
    bomb = false;

    position.row = r;
    position.col = c;

    std::cout << "row: " << r << " col: " << c << "\n";
}

void Tile::incrNumber() {
    number++;
}
int Tile::getNumber() const{
    return number;
}

void Tile::makeBomb() {
    bomb = true;
    this->writeTile();
}
bool Tile::isBomb() const {
    return bomb;
}

void Tile::setStatus(const DisplayStatus& s) {
    status = s;
    this->writeTile();
}
DisplayStatus Tile::getStatus() const{
    return status;
}

void Tile::writeTile() {
    if(status == REVEALED) {
        this->setDisabled(true);
        if (number != 0) {
            this->setText(QString::number(number));
        }
    }
    else if(status == FLAGGED) {
        this->setText("F");
    }
    else if(status == HIDDEN) {
        this->setText("");
    }
}

void Tile::mousePressEvent(QMouseEvent* event) {
    std::cout << "signal sent from row: " << position.row << " col: " << position.col << "\n";

    if (event->button() == Qt::LeftButton) {
        emit tileClicked(position, false);
    }
    else if (event->button() == Qt::RightButton) {
        emit tileClicked(position, true);
    }
}

