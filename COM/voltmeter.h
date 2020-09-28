#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>

class Voltmeter : public QObject
{
    Q_OBJECT
public:

    explicit Voltmeter(QString name = "", uint bR = 0, uint dB = 0, uint par = 0, uint stop = 0, uint fC = 0,QObject *parent = nullptr)
        : QObject(parent)
    {
        m_SettingsCom.m_name = name;
        qDebug() << m_SettingsCom.m_name;
        m_SettingsCom.m_baudRate = static_cast<QSerialPort::BaudRate>(bR),
        qDebug() << m_SettingsCom.m_baudRate;
        m_SettingsCom.m_dataBits = static_cast<QSerialPort::DataBits>(dB);
        qDebug() << m_SettingsCom.m_dataBits;
        m_SettingsCom.m_parity = static_cast<QSerialPort::Parity>(par);
        qDebug() << m_SettingsCom.m_parity;
        m_SettingsCom.m_stopBits = static_cast<QSerialPort::StopBits>(stop);
        qDebug() << m_SettingsCom.m_stopBits;
        m_SettingsCom.m_flowControl = static_cast<QSerialPort::FlowControl>(fC);
        qDebug() << m_SettingsCom.m_flowControl;


    }
    virtual ~Voltmeter(){

    }

    virtual bool OpenSerial() = 0;
    virtual bool CloseSerial() = 0;
    virtual QString Measurement(uint) = 0;

protected:

    //настройки COM
    struct SettingsComPort {
        QString m_name;
        uint m_baudRate;
        QSerialPort::DataBits m_dataBits;
        QSerialPort::Parity m_parity;
        QSerialPort::StopBits m_stopBits;
        QSerialPort::FlowControl m_flowControl;
    };
    //текущие настройки порта
    SettingsComPort m_SettingsCom;

    //cтатус подключения
    bool is_Connect = false;

    //таймаут
    int m_waitTimeout = 100;

};

#endif // VOLTMETER_H
