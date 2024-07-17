#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include <QObject>
#include <QUdpSocket>

class UdpHandler : public QObject
{
    Q_OBJECT
public:
    QUdpSocket *udpSocket;
    explicit UdpHandler(QObject *parent = nullptr);
    void bindSocket(quint16 port);
    void sendDatagram(const QByteArray &data, const QHostAddress &address, quint16 port);
    bool hasPendingDatagrams();
    qint64 pendingDatagramSize();
    qint64 readDatagram(char *data, qint64 maxSize, QHostAddress &address, quint16 &port);

signals:
 void datagramReceived(const QByteArray &data, const QHostAddress &address, quint16 port);

private slots:
    void readPendingDatagrams();
private:
};

#endif // UDPHANDLER_H
