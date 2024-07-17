#include "timerprototipe.h"

TimerPrototipe::TimerPrototipe(int interval,QObject *parent)
    : QObject{parent}, timer(new QTimer(this))
{
    timer->setTimerType(Qt::PreciseTimer);
    timer->setInterval(interval);
}

void TimerPrototipe::onTimeout(){
    emit timeout();
}

void TimerPrototipe::start(int value){
    timer->start(value);
}
void TimerPrototipe::stop(){
    timer->stop();
}

