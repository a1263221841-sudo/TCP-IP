#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->radioButton_Server->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

