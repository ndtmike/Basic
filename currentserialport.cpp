#include "currentserialport.h"

CurrentSerialPort::CurrentSerialPort(QWidget *parent) : QMainWindow(parent), QSerialPort()
{
    setBaudRate(9600);
    setDataBits(QSerialPort::Data8);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);
/*    if (open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Serial Port", "Connected!"); //translate function an issue
    } else {
        QMessageBox::critical(this, "Error", errorString());
    }
*/
}

bool CurrentSerialPort::CheckSerialPort()
{
    QString description;
    QString manufacturer;
    QString portname;
    const QString portmanufacturer = "FTDI";
    const QString noport = "No Available Ports\nCheck instrument is plugged in\nor serial port installed properly\n then restart Reboundlinx";
    const QString messageTitle = "checkSerialPort";
    const QString connected = "Connected to ";
    QList <QSerialPortInfo> availablePorts;
    bool r = false;

    availablePorts = QSerialPortInfo::availablePorts();

    if(!availablePorts.isEmpty()){
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            portname = info.portName();
            description = info.description();
            manufacturer = info.manufacturer();
            if(manufacturer == portmanufacturer){
                setPortName(portname);
                r = true;
            }
        if( r == true )break;
        }
    }
    if(r == false){
        QMessageBox::information(this,messageTitle,noport);
    }else{
        QMessageBox::information(this ,messageTitle , connected + portname );
}
    return(r);
}
