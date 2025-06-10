#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "tile.h"
#include "gamestatus.h"
#include "gamelevel.h"
#include "point.h"
#include <QGridLayout>
#include <QWidget>
#include <memory>

class Board : public QWidget
{
    Q_OBJECT
public:
    Board();
    Board(const GameLevel& l, QWidget* parent);

    GameStatus getGameStatus() const;

public slots:
    void clickTile(const Point& p, bool rightClicked);

private:
    std::vector<std::vector<Tile*>> board;
    GameLevel level;
    int tilesRevealed = 0; //-1 means a bomb has been clicked; game is over

    void placeBombs(const Point& p);
    std::vector<Point> getNeighbours(const Point& p) const;
};

#endif // BOARD_H
