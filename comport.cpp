#include "ComPort.h"

ComPort::ComPort(QObject *parent) :
    QObject(parent)
{
    m_SettingsCom.name = "";
    m_SettingsCom.baudRate =  QSerialPort::Baud9600;
    m_SettingsCom.dataBits = QSerialPort::Data8;
    m_SettingsCom.parity = QSerialPort::NoParity;
    m_SettingsCom.stopBits = QSerialPort::OneStop;
    m_SettingsCom.flowControl = QSerialPort::NoFlowControl;


}

ComPort::~ComPort()
{
    //delete m_SettingsCom;
    qDebug()<<"DelCom";
}

void ComPort::SetSettingCom(QString Name, qint32 BdRate, qint32 Data, qint32 Par, qint32 Stop, qint32 Flow)
{
    m_SettingsCom.name = Name;
    m_SettingsCom.baudRate = BdRate;
    m_SettingsCom.dataBits = static_cast<QSerialPort::DataBits>(Data);
    m_SettingsCom.parity = static_cast<QSerialPort::Parity>(Par);
    m_SettingsCom.stopBits = static_cast<QSerialPort::StopBits>(Stop);
    m_SettingsCom.flowControl = static_cast<QSerialPort::FlowControl>(Flow);
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
    qDebug()<<m_SettingsCom.name;
    return m_SettingsCom.name;
}

ComPort::SettingsComPort ComPort::setting()
{
    return m_SettingsCom;
}


