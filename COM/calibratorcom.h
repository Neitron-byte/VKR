#ifndef CALIBRATORCOM_H
#define CALIBRATORCOM_H

#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include "devicecom.h"

class CalibratorCom : public DeviceCom
{

public:
    CalibratorCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0): DeviceCom(name,bR,dB,par,stB,fC)
    {
        qDebug()<<"Volt Const";
        m_serial = new QSerialPort();
    }
    ~CalibratorCom(){
        delete m_serial;
    }

    void OpenSerial() override;
    void CloseSerial() override;


private:
    QSerialPort* m_serial = nullptr;
};

#endif // CALIBRATORCOM_H
