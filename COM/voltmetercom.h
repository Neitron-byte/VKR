#ifndef VOLTMETERCOM_H
#define VOLTMETERCOM_H

#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include "devicecom.h"

class VoltmeterCom : public DeviceCom
{
Q_OBJECT
public:
     explicit VoltmeterCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0,QObject *parent = nullptr)
        : DeviceCom(name,bR,dB,par,stB,fC,parent)
    {
        qDebug()<<"Volt Const";
        m_serial = new QSerialPort();

        connect(m_serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    }

    ~VoltmeterCom(){
        delete m_serial;
    }

    virtual bool OpenSerial() override;
    virtual bool CloseSerial() override;
    virtual void CreatSerial() override;
            void Measurement(uint);



public slots:
    void handleError(QSerialPort::SerialPortError error);


signals:
    void Error_(const QString&);

private:
    QSerialPort* m_serial = nullptr;


};

#endif // VOLTMETERCOM_H
