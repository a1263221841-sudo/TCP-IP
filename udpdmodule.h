#ifndef UDPDMODULE_H
#define UDPDMODULE_H

#include <QDialog>

namespace Ui {
class UDPDModule;
}

class UDPDModule : public QDialog
{
    Q_OBJECT

public:
    explicit UDPDModule(QWidget *parent = nullptr);
    ~UDPDModule();

private:
    Ui::UDPDModule *ui;
};

#endif // UDPDMODULE_H
