#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QSerialPort>

class DeviceCom: public QObject
{
    Q_OBJECT

public:


    explicit DeviceCom(QString name = "", uint bR = 0, uint dB = 0, uint par = 0, uint stop = 0, uint fC = 0,QObject *parent = nullptr)
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
    virtual ~DeviceCom() = 0;

    //гетер имени COM
    QString getName() const { return m_SettingsCom.m_name; }

    //метод для установки параметров COM
    void SetParamCom(QString name,quint32 bR,quint32 dB, quint32 par, quint32 stop, quint32 Control)
    {
        m_SettingsCom.m_name;
        qDebug() << m_SettingsCom.m_name;
        m_SettingsCom.m_baudRate = static_cast<QSerialPort::BaudRate>(bR),
        qDebug() << m_SettingsCom.m_baudRate;
        m_SettingsCom.m_dataBits = static_cast<QSerialPort::DataBits>(dB);
        qDebug() << m_SettingsCom.m_dataBits;
        m_SettingsCom.m_parity = static_cast<QSerialPort::Parity>(par);
        qDebug() << m_SettingsCom.m_parity;
        m_SettingsCom.m_stopBits = static_cast<QSerialPort::StopBits>(stop);
        qDebug() << m_SettingsCom.m_stopBits;
        m_SettingsCom.m_flowControl = static_cast<QSerialPort::FlowControl>(Control);
        qDebug() << m_SettingsCom.m_flowControl;

    }

    virtual bool OpenSerial() = 0;
    virtual bool CloseSerial() = 0;
    virtual void CreatSerial() = 0;


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



};



#endif // DEVICECOM_H

