#include "udpdmodule.h"
#include "ui_udpdmodule.h"

UDPDModule::UDPDModule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UDPDModule)
{
    ui->setupUi(this);
}

UDPDModule::~UDPDModule()
{
    delete ui;
}
