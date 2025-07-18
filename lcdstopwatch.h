#ifndef LCDSTOPWATCH_H
#define LCDSTOPWATCH_H

#include <QLCDNumber>
#include <QTimer>
#include <string>

class LcdStopwatch : public QLCDNumber
{
    Q_OBJECT
public:
    LcdStopwatch(QWidget* parent);
public slots:
    void startClock(); //Resets stopwatch to 00:00.0 and starts time.
    void stopClock(); //stops clock
private slots:
    void update(); //overloaded method
private:
    double elapsedSeconds;
    QTimer* timer;
};

#endif // LCDSTOPWATCH_H
