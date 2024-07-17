#include "udphandler.h"

UdpHandler::UdpHandler(QObject *parent)
    : QObject(parent), udpSocket(new QUdpSocket(this)) {
    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpHandler::readPendingDatagrams);
}

void UdpHandler::bindSocket(quint16 port) {
    udpSocket->bind(port);
}

void UdpHandler::sendDatagram(const QByteArray &data, const QHostAddress &address, quint16 port) {
    udpSocket->writeDatagram(data, address, port);
}

void UdpHandler::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        emit datagramReceived(datagram, sender, senderPort);
    }
}

bool UdpHandler::hasPendingDatagrams(){
    return (udpSocket->hasPendingDatagrams());
}

qint64 UdpHandler::pendingDatagramSize(){
    return(udpSocket->pendingDatagramSize());
}

qint64 UdpHandler::readDatagram(char *data, qint64 maxSize, QHostAddress &address, quint16 &port){
    return (udpSocket->readDatagram(data,maxSize,&address,&port));
}
