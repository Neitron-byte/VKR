#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QString>
#include <QList>
#include <QDebug>

class DeviceCom // абстрактный класс
{
public:
    DeviceCom(QString name = "", quint32 bR = 0, quint32 dB = 0, quint32 par = 0, quint32 stop = 0, quint32 fC = 0)
    {
        m_SettingsCom.m_name = name;
        m_SettingsCom.m_baudRate = bR,
        m_SettingsCom.m_dataBits = dB;
        m_SettingsCom.m_parity = par;
        m_SettingsCom.m_stopBits = stop;
        m_SettingsCom.m_flowControl = fC;

    }
    virtual ~DeviceCom() = 0;

    //гетер имени COM
    QString getName() const { return m_SettingsCom.m_name; }

    //метод для установки параметров COM
    void SetParamCom(QString name,quint32 bR,quint32 dB, quint32 par, quint32 stop, quint32 Control)
    {
        m_SettingsCom.m_name = name;
        qDebug() << m_SettingsCom.m_name;
        m_SettingsCom.m_baudRate = bR,
        qDebug() << m_SettingsCom.m_baudRate;
        m_SettingsCom.m_dataBits = dB;
        qDebug() << m_SettingsCom.m_dataBits;
        m_SettingsCom.m_parity = par;
        qDebug() << m_SettingsCom.m_parity;
        m_SettingsCom.m_stopBits = stop;
        qDebug() << m_SettingsCom.m_stopBits;
        m_SettingsCom.m_flowControl = Control;
        qDebug() << m_SettingsCom.m_flowControl;

    }

    virtual void OpenSerial() = 0;
    virtual void CloseSerial() = 0;
    virtual void CreatSerial() = 0;
    //

protected:
    //настройки COM
    struct SettingsComPort {
        QString m_name;
        quint32 m_baudRate;
        quint32 m_dataBits;
        quint32 m_parity;
        quint32 m_stopBits;
        quint32 m_flowControl;
    };
    //текущие настройки порта
    SettingsComPort m_SettingsCom;


};



#endif // DEVICECOM_H

