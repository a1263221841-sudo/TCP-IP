#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "network.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //network =new Network(this);

//    connet(network,&Network::signalDisconnected,this,[](const QString &msg){
//        QDebug() <<msg;});
//    }
    //窗口大小尺寸设计
    setFixedSize(width(),height());

    //多行文本编辑控件设置
    ui->plainTextEdit_MsgList->setReadOnly(true);
    ui->plainTextEdit_SendMsg->setFocus();

    //默认发送文本测试文件
    ui->plainTextEdit_SendMsg->setPlainText("Hello TCP Server/Client");

    //UI命令按扭设置
    ui->pushButton_SendMsg->setEnabled(false);
    ui->pushButton_UdpTest->setEnabled(false);
    ui->pushButton_ConnectServer->setEnabled(false);
    ui->pushButton_DisconnectServer->setEnabled(false);
    ui->pushButton_CloseListen->setEnabled(false);
    ui->plainTextEdit_SendMsg->setEnabled(false);
    ui->checkBox_ClientAutTest->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_StartListen_clicked()
{

}

void MainWindow::on_pushButton_CloseListen_clicked()
{

}

void MainWindow::on_pushButton_ConnectServer_clicked()
{

}

void MainWindow::on_pushButton_DisconnectServer_clicked()
{

}

void MainWindow::on_pushButton_SendMsg_clicked()
{

}

void MainWindow::on_pushButton_Exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_UdpTest_clicked()
{

}
void MainWindow::TcpServerConnected()
{
    tcpSocket = tcpServer->nextPendingConnection();
    if(!tcpSocketList.contains(tcpSocket))
        tcpSocketList.append(tcpSocket);

    connect(tcpSocket,&QTcpSocket::readyRead,this,
            &MainWindow::ReadAllDate);
    connect(tcpSocket,&QTcpSocket::disconnected,this,
            &MainWindow::ClinetDisconnected);
    QString strPort=QString::number((tcpSocket->peerPort()));

    ui->plainTextEdit_MsgList->appendPlainText
            ("\n[Prompt:New clinet connection:("+tcpSocket
            ->peerAddress().toString()+":"+strPort+")]");
    iCountReciveMsg=0;//证明有新的客服端连接进来了


   // QDebug() << "Clinet connected:"
           //  <<tcpSocket->peerAddress().toString();
            //  <<tcpSocket->peerPort();

}
void MainWindow::ClinetDisconnected()
{
    QTcpSocket *client=dynamic_cast<QTcpSocket*>(sender());

    QString strMsg=QString("\n[Prompt:Client disconnected:(%1:%2)]").arg(client->peerAddress().toString())
            .arg(client->peerPort());
    ui->plainTextEdit_MsgList->appendPlainText(strMsg);
}
void MainWindow::ReadAllDate()
{
    QTcpSocket *client=dynamic_cast<QTcpSocket*>(sender());
    QByteArray buff =client->readAll();

    //处理当前时间

}
