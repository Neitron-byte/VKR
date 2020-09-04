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

    m_serial = new QSerialPort(this);

}

ComPort::~ComPort()
{
    qDebug()<<"DelCom";
}

void ComPort::SetSettingCom(QString Name, qint32 BdRate, qint32 Data, qint32 Par, qint32 Stop, qint32 Flow)
{
    m_SettingsCom.name = Name;
    qDebug()<<m_SettingsCom.name;
    m_SettingsCom.baudRate = BdRate;
    qDebug()<<m_SettingsCom.baudRate;
    m_SettingsCom.dataBits = static_cast<QSerialPort::DataBits>(Data);
    qDebug()<<m_SettingsCom.baudRate;
    m_SettingsCom.parity = static_cast<QSerialPort::Parity>(Par);
    qDebug()<<m_SettingsCom.parity;
    m_SettingsCom.stopBits = static_cast<QSerialPort::StopBits>(Stop);
    qDebug()<<m_SettingsCom.stopBits;
    m_SettingsCom.flowControl = static_cast<QSerialPort::FlowControl>(Flow);
    qDebug()<<m_SettingsCom.flowControl;
}

void ComPort::OpenSerial1()
{
    m_serial->setPortName(m_SettingsCom.name);
    m_serial->setBaudRate(m_SettingsCom.baudRate);
    m_serial->setDataBits(m_SettingsCom.dataBits);
    m_serial->setParity(m_SettingsCom.parity);
    m_serial->setStopBits(m_SettingsCom.stopBits);
    m_serial->setFlowControl(m_SettingsCom.flowControl);
    if(m_serial->open(QIODevice::ReadWrite)) {

        SignalStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(m_SettingsCom.name).arg(m_SettingsCom.baudRate).arg(m_SettingsCom.dataBits)
                          .arg(m_SettingsCom.parity).arg(m_SettingsCom.stopBits).arg(m_SettingsCom.flowControl));
    } else {
        //QMessageBox::critical(tr("Error"), m_serial->errorString(),QMessageBox::Ok);
        SignalStatusMessage(tr("Open error"));
    }

}

void ComPort::CloseSerial()
{
    if (m_serial->isOpen())
        m_serial->close();
        SignalStatusMessage(tr("Disconnected"));
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


