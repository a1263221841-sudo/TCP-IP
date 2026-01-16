#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QHostAddress>
//统计自动发送消息次数
static int iCountTestMsg =0;
class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);

    ~Network(void);
public:
    bool ClientConnectToServer (QString ServeriIPAdress ,int ServerPort);//客户端连接服务器函数

    //客服端向服务器发送消息
    void ClientSendMsgToServer (QString StrDate);


signals:
private:
    QTcpSocket *socket;//TCP套接字
    QTimer *timer;//定时器
private slots:
    //void

public slots:
    //客服端与服务器之间,断开服务器消息反馈
    void ClientConnectFunc(void);
    void ClientDisconnectFunc(void);

    //断开与服务器之间(远程主机)的连接
    void DisconnectFromHost();

    //读取客服端发来的消息
    void ReadServerMsg();

    //启动定时器向服务器自动发送消息
    void StarTimerOutFunc();


    //停止定时器向服务器自动发送消息
    void StopTimerOutFunc();

signals:
    void signalDisconnected(const QString &msg);

};

#endif // NETWORK_H
