#include "tile.h"
#include "displaystatus.h"

Tile::Tile(const int& r, const int& c, QWidget* parent = nullptr)
    : QPushButton(parent)
{
    number = 0;
    status = HIDDEN;
    bomb = false;

    position.row = r;
    position.col = c;
}

void Tile::incrNumber() {
    number++;
    this->writeTile();
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

void Tile::writeTile() const{
    if(status == REVEALED) {
        this->setDisabled(true);
        this->setText("number");
    }
    else if(status == FLAGGED) {
        this->setText("F");
    }
    else if(bomb) {
        this->setText("B");
    }
}

void Tile::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit tileClicked(position, false);
    }
    else if (event->button() == Qt::RightButton) {
        emit tileClicked(position, true);
    }
}

