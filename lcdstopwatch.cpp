#include "lcdstopwatch.h"

LcdStopwatch::LcdStopwatch(QWidget* parent)
    : QLCDNumber(parent)
{
    timer = new QTimer(this);
    elapsedSeconds = 0.0;

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->setSmallDecimalPoint(true);
    this->setDigitCount(5);
}

void LcdStopwatch::startClock()
{
    timer->start(100);
}

void LcdStopwatch::stopClock()
{
    timer->stop();
}

void LcdStopwatch::update()
{
    elapsedSeconds += 0.1;
    this->display(elapsedSeconds);
}


