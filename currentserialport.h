#ifndef CURRENTSERIALPORT_H
#define CONNECTSERIALPORT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QtCore/QtGlobal>

class CurrentSerialPort : public QMainWindow , public QSerialPort
{

public:
    explicit CurrentSerialPort(QWidget *parent = 0);
     bool CheckSerialPort();

signals:

public slots:
};

#endif // CURRENTSERIALPORT_H
