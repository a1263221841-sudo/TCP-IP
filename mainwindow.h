#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//处理服务器
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkConfigurationManager>
#include <QNetworkInterface>

#include <QMessageBox>
#include <QDateTime>

#include <iostream>
#include <QString>
#include <string>



//处理客户端
#include <QThread>
//#include <QDialog>
#include "network.h"

//统计自动接收消息次数
static int iCountReciveMsg =0;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_StartListen_clicked();

    void on_pushButton_CloseListen_clicked();

    void on_pushButton_ConnectServer_clicked();

    void on_pushButton_DisconnectServer_clicked();

    void on_pushButton_SendMsg_clicked();

    void on_pushButton_Exit_clicked();

    void on_checkBox_ClientAutTest_clicked();

    void on_pushButton_UdpTest_clicked();

private:
    Ui::MainWindow *ui;
    //Network *network;
public:
    QTcpServer *tcpServer =nullptr;
    QTcpSocket *tcpSocket =nullptr;
    QList<QTcpSocket*> tcpSocketList;

    Network NetworkClient;


    //检测IP地址的合法性
    bool CheckIpAddressIsValid(QString strIpAdress);

    //控制客服端与服务器按钮之间的切换方法
    void ClientButtonStateFunc();
    void ServerButtonStateFunc();

private slots:
    void TcpServerConnected();
    void ClinetDisconnected();
    void ReadAllDate();





};
#endif // MAINWINDOW_H
