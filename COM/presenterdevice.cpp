#include "presenterdevice.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "QDebug"

PresenterDevice::PresenterDevice(QObject *parent) : QObject(parent)
{
    m_name_calibrator = "";
    m_name_voltmeter = "";


}

void PresenterDevice::SearchComPorts()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        m_ListComPorts .append(info.portName());
    }
    if (!m_ListComPorts.isEmpty()){
        emit signaListCom(m_ListComPorts);
        qDebug() << "SearchCom";
        for (const QString& com : m_ListComPorts) {
            qDebug() << com;
        }
    }

}

void PresenterDevice::slotSettingsSaveCal(QString name,quint32 bR,quint32 dB, quint32 par, quint32 stop, quint32 Control)
{
    m_SettingsComCal.m_name = name;
    m_SettingsComCal.m_baudRate = bR;
    m_SettingsComCal.m_dataBits = dB;
    m_SettingsComCal.m_parity = par;
    m_SettingsComCal.m_stopBits = stop;
    m_SettingsComCal.m_flowControl = Control;
}

void PresenterDevice::slotSettingsSaveVol(QString name,quint32 bR,quint32 dB, quint32 par, quint32 stop, quint32 Control)
{
    m_SettingsComVolt.m_name = name;
    m_SettingsComVolt.m_baudRate = bR;
    m_SettingsComVolt.m_dataBits = dB;
    m_SettingsComVolt.m_parity = par;
    m_SettingsComVolt.m_stopBits = stop;
    m_SettingsComVolt.m_flowControl = Control;
}
