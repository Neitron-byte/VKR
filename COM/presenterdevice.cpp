#include "presenterdevice.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


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
}
