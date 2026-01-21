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

    //初始化操作
    tcpServer=new QTcpServer(this);
    connect(tcpServer,&QTcpServer::newConnection,this,&MainWindow::TcpServerConnected);

    QList<QHostAddress> addrList=QNetworkInterface::allAddresses();
    foreach(const QHostAddress &address,addrList)
    {
        if(address.protocol()==QAbstractSocket::IPv4Protocol)
        {
            ui->comboBox_IPAddrees->addItem(address.toString());
        }
    }


    //客服端与服务器端单选按扭:选择之间的切换实现
    connect(ui->radioButton_Clinet,&QRadioButton::toggled,this,&MainWindow::ClientButtonStateFunc);
    connect(ui->radioButton_Server,&QRadioButton::toggled,this,&MainWindow::ServerButtonStateFunc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//监听服务
void MainWindow::on_pushButton_StartListen_clicked()
{
    QHostAddress address=QHostAddress(ui->comboBox_IPAddrees->currentText());
    int port= ui->spinBox_Port->text().toInt();

    //检测ip地址合法性
    QString strIpAdrs=ui->comboBox_IPAddrees->currentText();// 获取当前IP地址
    if(CheckIpAddressIsValid(strIpAdrs)==false)
    {
        QMessageBox::critical(this,"Error","Error Prompt:"+strIpAdrs+"\n"+"Illegal IP address,please recheck?",QMessageBox::Yes);
        ui->comboBox_IPAddrees->setFocus();
        return;
    }

    if(tcpServer->isListening())
    {
        tcpServer->close();
        for(auto client:tcpSocketList)
            client->close();

        tcpSocketList.clear();
        ui->plainTextEdit_MsgList->appendPlainText(QString("[Prompt:Successfully monitored%1:%2]").arg(address.toString()).arg(port));
    }else
    {
        if(!tcpServer->listen(address,port))
        {
            ui->plainTextEdit_MsgList->clear();
            ui->plainTextEdit_MsgList->appendPlainText(QString("[Prompt:listening failed,Please check the IP and port.]"));
        }else {
            ui->plainTextEdit_MsgList->clear();
            ui->plainTextEdit_MsgList->appendPlainText(QString("[Prompt:Serve listening succeeded (%1:%2)]"));

            ui->pushButton_StartListen->setEnabled(false);
            ui->pushButton_CloseListen->setEnabled(true);
        }
    }
}

//关闭监听
void MainWindow::on_pushButton_CloseListen_clicked()
{
    tcpServer->close();
    for(auto client:tcpSocketList)
        client->close();

    tcpSocketList.clear();

    ui->plainTextEdit_MsgList->appendPlainText("[Prompt:Disconnect all client connections.");
    ui->pushButton_StartListen->setEnabled(true);
    ui->pushButton_CloseListen->setEnabled(false);
}

//连接服务器
void MainWindow::on_pushButton_ConnectServer_clicked()
{
    ui->plainTextEdit_MsgList->clear();//连接服务器之前数据信息要全部清除

    ui->pushButton_ConnectServer->setEnabled(false);
    ui->pushButton_DisconnectServer->setEnabled(true);

    //获取IP及端口
    QString IpAddress=ui->comboBox_IPAddrees->currentText();
    int iPort=ui->spinBox_Port->text().toInt();

    //检测ip地址的合法性
    QString strIPAdrs=ui->comboBox_IPAddrees->currentText();
    if(CheckIpAddressIsValid(strIPAdrs)==false)
    {
        QMessageBox::critical(this,"Error","Error Prompt:"+strIPAdrs+"\n"+"Illegal IP address,please recheck?",QMessageBox::Yes);
        ui->comboBox_IPAddrees->setFocus();
        return;
    }

    //连接服务器端
    bool isBools=NetworkClient.ClientConnectToServer(IpAddress,iPort);
    if(isBools==true)
     {
        ui->plainTextEdit_MsgList->clear();
        ui->plainTextEdit_MsgList->appendPlainText("[Prompt:Successfully connected to the Server.]");
        ui->checkBox_ClientAutTest->setEnabled(true);//服务器连接成功,客户端自动测试复选按扭可以使用
        ui->pushButton_SendMsg->setEnabled(true);
        ui->plainTextEdit_SendMsg->setEnabled(true);
    }
    else
    {
        ui->plainTextEdit_MsgList->appendPlainText("[Prompt:Failed connected to the Server.]");
        ui->pushButton_ConnectServer->setEnabled(true);
        ui->pushButton_DisconnectServer->setEnabled(false);

    }

}

//断开服务器(远程主机)
void MainWindow::on_pushButton_DisconnectServer_clicked()
{
    ui->pushButton_ConnectServer->setEnabled(true);
    ui->pushButton_DisconnectServer->setEnabled(false);
    NetworkClient.DisconnectFromHost();

    //断开服务器用户可以输出数据信息
    ui->plainTextEdit_SendMsg->setEnabled(true);
    ui->plainTextEdit_SendMsg->setFocus();

    bool isInitSate=ui->checkBox_ClientAutTest->isChecked();//获取初始化选中状态
    ui->checkBox_ClientAutTest->setChecked(true);//恢复启用
    ui->checkBox_ClientAutTest->setChecked(isInitSate);//设置回到初始选中状态
    ui->checkBox_ClientAutTest->setChecked(false);//取消选中勾
    ui->checkBox_ClientAutTest->setEnabled(false);

    //断开服务器连接,禁止plainTexTEdit控件输入
    ui->plainTextEdit_SendMsg->setEnabled(false);
    //断开服务器,发送消息按扭也要禁用
    ui->pushButton_SendMsg->setEnabled(false);
    ui->plainTextEdit_MsgList->appendPlainText("[Prompt:Disconect from Serve");

}

//发送消息
void MainWindow::on_pushButton_SendMsg_clicked()
{
    QString strSendMsg=ui->plainTextEdit_SendMsg->toPlainText();

    if(strSendMsg.isEmpty())
    {
        QMessageBox::critical(this,"Error","Error Prompt:Sending test data cannot be empty.");
        ui->plainTextEdit_SendMsg->setFocus();
        return;
    }

    NetworkClient.ClientSendMsgToServer(strSendMsg);

    //处理当前时间
    QDateTime currentDataTime =QDateTime::currentDateTime();
    QString year =QString::number(currentDataTime.date().year());
    QString month =QString::number(currentDataTime.date().month());
    QString day = QString::number(currentDataTime.date().day());
    QString hour = QString::number(currentDataTime.time().hour());
    QString minute= QString::number(currentDataTime.time().minute());
    QString second=QString::number(currentDataTime.time().second ());
    QString strtemp=year+"/"+month+"/"+day+" "+hour+":"+minute+":"+second;

    QString strTemps;
    strTemps=("\n["+strtemp+"/nRecevied customer message:"+strSendMsg);
    ui->plainTextEdit_MsgList->appendPlainText(strTemps);

    ui->plainTextEdit_MsgList->setFocus();
}

//退出程序
void MainWindow::on_pushButton_Exit_clicked()
{
    this->close();
}

void MainWindow::on_checkBox_ClientAutTest_clicked()
{
    bool cbxStatus=ui->checkBox_ClientAutTest->isChecked();
    //用户选择[客户端自动化测试控件]
    if(cbxStatus==true)
    {
        NetworkClient.StarTimerOutFunc();//启动定时器自动向服务器发送消息
        ui->plainTextEdit_SendMsg->setEnabled(false);
        ui->pushButton_SendMsg->setEnabled(false);

    }else
    {
        NetworkClient.StopTimerOutFunc();
    }
}

//调用UDP窗口模块
#include "udpdmodule.h"
void MainWindow::on_pushButton_UdpTest_clicked()
{
    UDPDModule *udpwOjbect = new UDPDModule(this);

    //.exex() 是在主循环中执行模态对话框,这样会阻塞用户对后面的窗口的操作,直到前面的窗口关闭
    udpwOjbect->exec();
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
    QDateTime currentDataTime =QDateTime::currentDateTime();
    QString year =QString::number(currentDataTime.date().year());
    QString month =QString::number(currentDataTime.date().month());
    QString day = QString::number(currentDataTime.date().day());
    QString hour = QString::number(currentDataTime.time().hour());
    QString minute= QString::number(currentDataTime.time().minute());
    QString second=QString::number(currentDataTime.time().second ());
    QString strtemp=year+"/"+month+"/"+day+" "+hour+":"+minute+":"+second;

    QString strTemps;
    strTemps=("\n["+strtemp+"/nRecevied customer message:"+buff);
    ui->plainTextEdit_MsgList->appendPlainText(strTemps);

    //读取客户端套接字的数据信息,并且直接回复
    QString strReturnBackTemp="Server reply massage:" +buff;
    QByteArray qbtReturnBankTemp=QByteArray::fromStdString(strReturnBackTemp.toStdString());
    client->write(qbtReturnBankTemp);

}
//检测IP地址的合法性
bool MainWindow::CheckIpAddressIsValid(QString strIpAdress)
{
    if(strIpAdress.isEmpty())
    {
        return false;

    }
    QStringList list=strIpAdress.split('.');
    if(list.size()!=4){
        return false;
    }
    for (const auto& num:list) {
        bool ok=false;
        int temp=num.toInt(&ok);
        if(!ok || temp<0 ||temp>255)
        {
            return false;
        }
    }
    return true;
}

//控制客服端与服务器按钮之间的切换方法
void MainWindow::ClientButtonStateFunc()
{
    ui->plainTextEdit_MsgList->clear();

    ui->pushButton_ConnectServer->setEnabled(true);
    ui->plainTextEdit_SendMsg->setEnabled(true);

    ui->pushButton_DisconnectServer->setEnabled(false);
    ui->pushButton_StartListen->setEnabled(false);
    ui->pushButton_CloseListen->setEnabled(false);
    ui->plainTextEdit_SendMsg->setEnabled(false);//当用户选择客户端单选按钮时,禁止plainTextEdit控件输入

    // 防止服务器启动监听之后,用户点击客服端单选按钮
    ui->plainTextEdit_MsgList->clear();

    //关闭TCP套接字,及每一个客户端
    tcpServer->close();
    for(auto client:tcpSocketList)
        client->close();
}
void MainWindow::ServerButtonStateFunc()
{
    ui->plainTextEdit_MsgList->clear();

    ui->pushButton_ConnectServer->setEnabled(false);
    ui->pushButton_DisconnectServer->setEnabled(false);
    ui->plainTextEdit_SendMsg->setEnabled(false);
    ui->pushButton_SendMsg->setEnabled(false);

    ui->pushButton_StartListen->setEnabled(true);
    ui->pushButton_CloseListen->setEnabled(false);

    NetworkClient.disconnect();
    ui->checkBox_ClientAutTest->setChecked(false);

    //断开服务器连接,开启用户可输入数据信息
    ui->plainTextEdit_SendMsg->setEnabled(true);
    ui->plainTextEdit_SendMsg->setFocus();

    ui->checkBox_ClientAutTest->setChecked(false);
    ui->plainTextEdit_SendMsg->setEnabled(false);//当用户选择客服端,再次切换到服务器单选按钮时,禁止用户输入消息

    NetworkClient.StopTimerOutFunc();




}


