#include "ComPort.h"

ComPort::ComPort()
{

}

void ComPort::setName(QString strName)
{
    m_SettingsCom.name = strName;
    qDebug()<<m_SettingsCom.name;
}

void ComPort::setBoudRate(qint32 BdRate)
{
    m_SettingsCom.baudRate = BdRate;
    qDebug()<<m_SettingsCom.baudRate;
}

void ComPort::setDataBits(qint32 Data)
{
    m_SettingsCom.dataBits = static_cast<QSerialPort::DataBits>(Data);
    qDebug()<<m_SettingsCom.dataBits;
}

void ComPort::setParity(qint32 parity)
{
    m_SettingsCom.parity = static_cast<QSerialPort::Parity>(parity);
    qDebug()<<m_SettingsCom.parity;
}

void ComPort::setStopBits(qint32 stop)
{
    m_SettingsCom.stopBits = static_cast<QSerialPort::StopBits>(stop);
    qDebug()<<m_SettingsCom.stopBits;
}

void ComPort::setFlowControl(qint32 flow)
{
    m_SettingsCom.flowControl = static_cast<QSerialPort::FlowControl>(flow);
    qDebug()<<m_SettingsCom.flowControl;
}

QString ComPort::getName()
{
    return m_SettingsCom.name;
}


