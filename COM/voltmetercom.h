#ifndef VOLTMETERCOM_H
#define VOLTMETERCOM_H

#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include "devicecom.h"

class VoltmeterCom : DeviceCom
{

public:
    VoltmeterCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0)
        : DeviceCom(name,bR,dB,par,stB,fC)
    {
        qDebug()<<"Volt Const";
        m_serial = new QSerialPort();
    }

    ~VoltmeterCom(){
        delete m_serial;
    }

    virtual void OpenSerial() override;
    virtual void CloseSerial() override;
    virtual void CreatSerial() override;

private:
    QSerialPort* m_serial = nullptr;
};

#endif // VOLTMETERCOM_H
