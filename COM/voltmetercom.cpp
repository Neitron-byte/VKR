#include "voltmetercom.h"
#include <QMessageBox>


bool VoltmeterCom::OpenSerial()
{
    qDebug()<<"Vol Com Open";
    qDebug()<<m_serial->thread();
    m_serial->setPortName(m_SettingsCom.m_name);
    m_serial->setBaudRate(m_SettingsCom.m_baudRate);
    m_serial->setDataBits(m_SettingsCom.m_dataBits);
    m_serial->setParity(m_SettingsCom.m_parity);
    m_serial->setStopBits(m_SettingsCom.m_stopBits);
    m_serial->setFlowControl(m_SettingsCom.m_flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {

        return true;
    } else {
        return false;

    }
}

bool VoltmeterCom::CloseSerial()
{
    if (m_serial->isOpen()){
        m_serial->close();
        return true;
    }
    return false;
}

void VoltmeterCom::CreatSerial()
{
    m_serial = new QSerialPort;
}

void VoltmeterCom::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {

        emit Error_(m_serial->errorString());

        this->CloseSerial();
    }
}
