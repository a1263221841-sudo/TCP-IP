#include "network.h"
#include <QObject>
Network::Network(QObject *parent) : QObject(parent)
{
    //初始化对象
    socket =new QTcpSocket;
    timer =new QTimer;

    //槽函数连接
    connect(socket,&QTcpSocket::connected,this,&Network::ClientConnectFunc);
    connect(socket,&QTcpSocket::disconnected,this,&Network::ClientDisconnectFunc);
    connect(socket,&QTcpSocket::readyRead,this,&Network::ReadServerMsg);
    connect(timer,&QTimer::timeout,this,&Network::StarTimerOutFunc);

}
Network::~Network(void)
{

}

//客户端连接服务器函数
bool Network:: ClientConnectToServer (QString ServeriIPAdress ,int ServerPort)
{
    socket->connectToHost(ServeriIPAdress,ServerPort);
    if(socket->waitForConnected())
    {
        iCountTestMsg =0;
        //iCountTestMsg++;
        return true;
    }else{
        return false;
    }

}
//客服端向服务器发送消息
void Network::ClientSendMsgToServer (QString StrDate)
{
    //将字符串转换成QByteArray类型
    socket->write(StrDate.toLatin1());
}
//客服端与服务器之间,断开服务器消息反馈
void Network::ClientConnectFunc(void)
{
    if(!socket)
        return;
    //如果当前是连接状态
    if(socket->state() ==QAbstractSocket::ConnectedState)
    {
        socket->disconnectFromHost();

    //如果是优雅的断开,等待真正的断开]
    if(socket->state() !=QAbstractSocket::ConnectedState)
    {
        socket->waitForDisconnected(3000);//最多等待3秒
    }
    emit signalDisconnected(QString("服务器已断开连接"));
    }else{
        emit signalDisconnected(QString("当前未连接服务器"));
    }
}
void Network::ClientDisconnectFunc(void)
{
    timer->stop();
}


//断开与服务器之间(远程主机)的连接
void Network::DisconnectFromHost()
{
    socket->disconnectFromHost();
}

//读取客服端发来的消息
void Network::ReadServerMsg()
{
    QByteArray data=socket->readAll();
}

//启动定时器向服务器自动发送消息
void Network::StarTimerOutFunc()
{
   timer->start(400);
   QString strTemp=QString("\n[Prompt:Client automatic testing(%1)]").arg(iCountTestMsg);
}


//停止定时器向服务器自动发送消息
void Network::StopTimerOutFunc()
{
    timer->stop();
}
