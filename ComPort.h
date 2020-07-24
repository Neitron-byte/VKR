#ifndef COMPORT
#define COMPORT
#include <QString>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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

};

#endif // COMPORT
