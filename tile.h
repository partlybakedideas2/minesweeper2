#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QMouseEvent>
#include "displaystatus.h"
#include "point.h"

class Tile : public QPushButton
{
        Q_OBJECT
public:
    Tile(const int& r, const int& c, QWidget* parent);

    void incrNumber();
    int getNumber() const;

    void makeBomb();
    bool isBomb() const;

    void setStatus(const DisplayStatus& s);
    DisplayStatus getStatus() const;

    void writeTile();

signals:
    void tileClicked(const Point& p, bool rightClicked);

private:
    int number; //0-8, representing the number of bombs surrounding a tile
    DisplayStatus status;
    bool bomb;

    Point position;

    void mousePressEvent(QMouseEvent* event) override;
};

#endif // TILE_H
