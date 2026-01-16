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

}
void MainWindow::ClinetDisconnected()
{

}
void MainWindow::ReadAllDate()
{

}
