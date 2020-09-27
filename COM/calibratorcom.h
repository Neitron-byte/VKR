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
Q_OBJECT
public:
     explicit CalibratorCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0,QObject *parent = nullptr)
        : DeviceCom(name,bR,dB,par,stB,fC,parent)
    {
        qDebug()<<"Cal Const";
        m_serial = new QSerialPort();
        connect(m_serial, &QSerialPort::errorOccurred, this, &CalibratorCom::handleError);

    }
    ~CalibratorCom(){
        delete m_serial;
    }

    virtual bool OpenSerial() override;
    virtual bool CloseSerial() override;
    virtual void CreatSerial() override;

    bool SendSerial(float);
    bool SendFreqSerial(float,uint);

public    slots:
    void handleError(QSerialPort::SerialPortError error);


signals:
    void Error_(const QString&);


private:
    QSerialPort* m_serial = nullptr;



};

#endif // CALIBRATORCOM_H
