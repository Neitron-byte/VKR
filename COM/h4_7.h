#ifndef H4_7_H
#define H4_7_H

#include <QObject>
#include "calibrator.h"
#include <QSerialPort>

class H4_7 : public Calibrator
{
    Q_OBJECT


public:
    explicit H4_7(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0,QObject *parent = nullptr)
        : Calibrator(name,bR,dB,par,stB,fC,parent) {
        qDebug()<<"Cal Const";
        m_serial = new QSerialPort();
        connect(m_serial, &QSerialPort::errorOccurred, this, &H4_7::handleError);
    }


    ~H4_7(){
        if(m_serial != nullptr){
            delete m_serial;
        }
    }

    //открытие порта
    virtual bool OpenSerial() override;
    //закрыть порт
    virtual bool CloseSerial() override;
    //отправить в порт V DC
    virtual bool SendSerial(float) override;
    //отправить в порт V + F
    virtual bool SendFreqSerial(float,uint)override;

public    slots:
    void handleError(QSerialPort::SerialPortError error);


signals:
    void Error_(const QString&);

private:
    QSerialPort* m_serial = nullptr;

};

#endif // H4_7_H
