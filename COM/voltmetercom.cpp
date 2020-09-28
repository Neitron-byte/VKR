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

        QString SetRemote = "SYST:REM\r\n";
        QString SetCount = "SAMP:COUN 1\r\n";

        m_serial->write(SetRemote.toLocal8Bit());
        qDebug()<<"SYST:REM"<< SetRemote.toLocal8Bit();

        if(m_serial->waitForBytesWritten(100)){
            m_serial->write(SetCount.toLocal8Bit());
            qDebug()<<"SAMP:COUN"<< SetCount.toLocal8Bit();
            if(m_serial->waitForBytesWritten(100)){
                return true;
            }
        }
    }

    return false;

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

QString VoltmeterCom::Measurement(uint ch)
{
    //Отправка команды на подготовку канала к измерениям
    QString Request = "ROUT:TERM FRON"+QString::number(ch)+"\r\n";
    m_serial->write(Request.toLocal8Bit());
    if(m_serial->waitForBytesWritten(100)){
        Request = "READ?\r\n";
        m_serial->write(Request.toLocal8Bit());
        if(m_serial->waitForBytesWritten()) {

              //чтение из порта
                if (m_serial->waitForBytesWritten()) {
                    QByteArray responseData = m_serial->readAll();
                    while (m_serial->waitForReadyRead(10))
                        responseData += m_serial->readAll();

                    QString response = QString::fromLocal8Bit(responseData);


                    return response;

                }

            }
        }

    return QString("error");
}






void VoltmeterCom::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {

        emit Error_(m_serial->errorString());

        this->CloseSerial();
    }
}
