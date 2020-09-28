#ifndef HP34420A_H
#define HP34420A_H

#include <QObject>
#include "voltmeter.h"
#include <QSerialPort>
#include <QDebug>

class HP34420A : public Voltmeter
{
    Q_OBJECT

public:

    explicit HP34420A(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stB = 0, quint32 fC = 0,QObject *parent = nullptr)
       : Voltmeter(name,bR,dB,par,stB,fC,parent)
   {
       qDebug()<<"HP34420A Construction";
       m_serial = new QSerialPort();

       connect(m_serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

   }

   ~HP34420A(){
       delete m_serial;
   }

   virtual bool OpenSerial() override;
   virtual bool CloseSerial() override;
   virtual QString Measurement(uint) override;



public slots:
   void handleError(QSerialPort::SerialPortError error);


signals:
   void Error_(const QString&);

private:
   QSerialPort* m_serial = nullptr;

};

#endif // HP34420A_H
