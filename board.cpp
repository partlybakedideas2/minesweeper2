#include "board.h"
#include "tile.h"
#include "gamelevel.h"
#include "point.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>


Board::Board() {}
Board::Board(const GameLevel& l, QWidget* parent)
    : QWidget(parent)

{
    std::cout << "constructor called\n";
    level = l;

    QGridLayout* grid = new QGridLayout(this);

    switch(level) {
    case EASY: //Easy board: 8*8 grid
        board.resize(8, std::vector<Tile*>(8));
        break;
    case MEDIUM: //Medium board 16*16 grid
        board.resize(16, std::vector<Tile*>(16));
        break;
    case HARD: //Hard board 24*24 grid
        board.resize(24, std::vector<Tile*>(24));
        break;
    }

    this->setMaximumSize(50*level,50*level);
    this->setMinimumSize(50*level,50*level);

    grid->setSpacing(0);

    for (int r = 0; r < level; r++) {
        grid->setRowMinimumHeight(r, 60);
        for (int c = 0; c < level; c++) {
            board.at(r).at(c) = new Tile(r, c, this);
            QObject::connect(board.at(r).at(c), SIGNAL(tileClicked(Point,bool)), this, SLOT(clickTile(Point,bool)));
            QObject::connect(this, SIGNAL(gameWon()), board.at(r).at(c), SLOT(on_gameWon()));
            QObject::connect(this, SIGNAL(gameLost()), board.at(r).at(c), SLOT(on_gameLost()));
            grid->addWidget(board.at(r).at(c), r, c);
        }
    }
}

void Board::getGameStatus()
{
    if (tilesRevealed == -1) {
        emit gameLost();
    }
    else if (tilesRevealed == (level * level) - (10 * (level * level) / 64)) {
        emit gameWon();
    }
}

void Board::clickTile(const Point& p, bool rightClicked)
{
    if (tilesRevealed == 0) { //Emits gameStarted() to begin timer on 1st click
        emit gameStarted();
    }
    Tile& t = *board.at(p.row).at(p.col);
    // normal (left) click actions:
    if (!rightClicked) {
        // left-clicking a flagged tile does nothing
        if (t.getStatus() != FLAGGED) {
            // left clicking a bomb is immediate game over:
            if (t.isBomb()) {
                tilesRevealed = -1;
            }
            // otherwise the clicked tile is revealed:
            else {
                t.setStatus(REVEALED);
                // after the first click, bombs are placed on the board:
                if (tilesRevealed == 0) {
                    placeBombs(p);
                }
                tilesRevealed++; // Increment this to track game progress
                // if the tile has 0 surrounding bombs, all surrounding
                // hidden tiles are automatically opened:
                if (t.getNumber() == 0) {
                    std::vector<Point> neighbours = getNeighbours(p);
                    for (Point &n : neighbours) {
                        if (board.at(n.row).at(n.col)->getStatus() != REVEALED) {
                            clickTile(n, false);
                        }
                    }
                }
            }
        }
    }
    // right clicking a tile places a new flag or removes an existing one:
    else {
        if (t.getStatus() != FLAGGED) {
            t.setStatus(FLAGGED);
            //t.setIcon(flagIcon);
            //t.setIconSize(QSize(50, 50));
        } else {
            t.setStatus(HIDDEN);
            //t.setIcon(QIcon());
        }
    }
    this->getGameStatus();//checks if game has been won or lost; emits signal accordingly.
}

void Board::placeBombs(const Point& p)
{
    std::cout << "placebombs called\n";
    srand(time(NULL));

    for (int i = 0; i < 10 * (level * level) / 64;
         i++) { // places 10 bombs per 8x8 section.

        Point b;

        b.row = rand() % level;
        b.col = rand() % level;
        std::vector<Point> exclusionNeighbours = getNeighbours(p);
        // ensure no bombs are placed near the first click or
        // on top of previously placed bombs
        if (board.at(b.row).at(b.col)->isBomb() || b == p ||
            count(exclusionNeighbours.begin(), exclusionNeighbours.end(), b) !=
                0) {
            i--;
            continue;
        }
        board.at(b.row).at(b.col)->makeBomb();
        // Increment the surrounding tiles' numbers by 1
        std::vector<Point> bombNeighbours = getNeighbours(b);
        for (Point &j : bombNeighbours) {
            board.at(j.row).at(j.col)->incrNumber();
        }
    }
}
std::vector<Point> Board::getNeighbours(const Point& p) const
{
    std::vector<Point> neighbours;
    neighbours.reserve(8);
    for (int i = p.row - 1; i <= p.row + 1; i++) {
        for (int j = p.col - 1; j <= p.col + 1; j++) {
            if (i == p.row && j == p.col) {
                continue;
            }
            if (i >= 0 && i < level && j >= 0 && j < level) {
                neighbours.emplace_back(i, j);
            }
        }
    }
    return neighbours;
}
