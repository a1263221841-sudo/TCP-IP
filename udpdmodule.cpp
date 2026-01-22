#include "udpdmodule.h"
#include "ui_udpdmodule.h"

UDPDModule::UDPDModule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDPDModule)
{
    ui->setupUi(this);
    //默认窗口大小
    setFixedSize(this->width(),this->height());

    //new一个UDP
    udpserverobject=new UDPServerClient(this);
    //默认测试数据信息
    ui->plainTextEdit_UdpSendMsg->setPlainText("Hello udp protocol test.");
}

UDPDModule::~UDPDModule()
{
    delete ui;
}
//启动监听读取数据--服务器
void UDPDModule::ReadDatagramInfoFunc(QString strIp,int iPort)
{
    //处理当前日期和时间
    QDateTime currentDateTime=QDateTime::currentDateTime();
    QString year= QString::number(currentDateTime.date().year());
    QString month =QString::number(currentDateTime.date().month());
    QString day =QString::number(currentDateTime.date().day());
    QString hour =QString::number(currentDateTime.time().hour());
    QString minute=QString::number(currentDateTime.time().minute());
    QString second= QString::number(currentDateTime.time().second());
    QString strtemp=year+"/"+month+"/"+day+" "+hour+":"+minute+":"+second;

    QByteArray qba_data;
    qba_data.resize(udpserverobject->udp_SocketObject->pendingDatagramSize());
    QHostAddress *hostipaddress=new QHostAddress(strIp);
    quint16 int_port=iPort;

    while(udpserverobject->udp_SocketObject)


}



 //连接服务器,读取服务器回复消息
void  UDPDModule::ReadServerDatagramFunc(QString strIP,int iPort)
{

}
void UDPDModule::on_pushButton_UdpStartListen_clicked()
{

}

void UDPDModule::on_pushButton_UdpCloseListen_clicked()
{

}

void UDPDModule::on_pushButton_UdpConnectServer_clicked()
{

}

void UDPDModule::on_pushButton_UdpDisconnectedServer_clicked()
{

}

void UDPDModule::on_pushButton_UdpExit_clicked()
{
    this->close();
}

void UDPDModule::on_pushButton_UdpSendMsg_clicked()
{

}
