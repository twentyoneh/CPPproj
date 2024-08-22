#ifndef TIMERPROTOTIPE_H
#define TIMERPROTOTIPE_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>

class TimerPrototipe : public QObject
{
    QTimer *timer;
    Q_OBJECT
public:
    explicit TimerPrototipe(int interval,QObject *parent = nullptr);
    void start(int);
    void stop();

signals:
    void timeout();

private slots:
    void onTimeout();

};

#endif // TIMERPROTOTIPE_H
