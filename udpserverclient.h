#ifndef UDPSERVERCLIENT_H
#define UDPSERVERCLIENT_H

#pragma execution_character_set("utf-8")

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>

class UDPServerClient : public QObject
{
    Q_OBJECT
public:
    explicit UDPServerClient(QObject *parent = nullptr);


public:
    QUdpSocket *udp_SocketObject; // UDP套接字指针
    QHostAddress udp_HostAddress; // 组播地址

};

#endif // UDPSERVERCLIENT_H
