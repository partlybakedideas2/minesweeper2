#ifndef MINESWEEPER2_H
#define MINESWEEPER2_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Minesweeper2;
}
QT_END_NAMESPACE

class Minesweeper2 : public QWidget
{
    Q_OBJECT

public:
    Minesweeper2(QWidget *parent = nullptr);
    ~Minesweeper2();

private:
    Ui::Minesweeper2 *ui;
};
#endif // MINESWEEPER2_H
