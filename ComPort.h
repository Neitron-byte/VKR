#ifndef COMPORT
#define COMPORT
#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class ComPort
{
    struct SettingsComPort {
        QString name;
        qint32 baudRate;
        //QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        //QString stringDataBits;
        QSerialPort::Parity parity;
        //QString stringParity;
        QSerialPort::StopBits stopBits;
        //QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        //QString stringFlowControl;
        //bool localEchoEnabled;
    };

    SettingsComPort m_SettingsCom;


public:
    ComPort();
    void setName(QString);
    void setBoudRate(qint32);
    void setDataBits(qint32);
    void setParity(qint32);
    void setStopBits(qint32);
    void setFlowControl(qint32);

};

#endif // COMPORT
