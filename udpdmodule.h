#ifndef UDPDMODULE_H
#define UDPDMODULE_H

#include <QDialog>

#include <QUdpSocket>
#include <QDateTime>
#include <QMessageBox>

#include "udpserverclient.h"
namespace Ui {
class UDPDModule;
}

class UDPDModule : public QDialog
{
    Q_OBJECT

public:
    explicit UDPDModule(QWidget *parent = nullptr);
    ~UDPDModule();

private slots:
    void on_pushButton_UdpStartListen_clicked();

    void on_pushButton_UdpCloseListen_clicked();

    void on_pushButton_UdpConnectServer_clicked();

    void on_pushButton_UdpDisconnectedServer_clicked();

    void on_pushButton_UdpExit_clicked();

    void on_pushButton_UdpSendMsg_clicked();

private:
    Ui::UDPDModule *ui;
public:
    //UDP服务器
    UDPServerClient *udpserverobject;

public: slots
    //启动监听读取数据--服务器
    void ReadDatagramInfoFunc(QString strIp,int iPort);

     //连接服务器,读取服务器回复消息
    void  ReadServerDatagramFunc(QString strIP,int iPort);
};

#endif // UDPDMODULE_H
